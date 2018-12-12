#include "sitvgwindow.h"
#include "ui_mainwindow.h"

SITVGWindow::SITVGWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SITVGWindow),
    baseImage(nullptr),
    transImage(nullptr),
    transList()
{
    ui->setupUi(this);
    ui->fileNameLabel->setText("Ninguna.");
    setInputFile();
    ui->listView->setModel(&transList);
}

SITVGWindow::~SITVGWindow()
{
    if (baseImage)
        delete baseImage;
    if (transImage)
        delete transImage;
    delete ui;
}

bool SITVGWindow::setInputFile()
{
    // Choose file
    QString pathName = QFileDialog::getOpenFileName(this, tr("Seleccione la imagen por transformar"),
                                                    "/home/", tr("Archivos de tipo SITVG (*.sitvg)"));

    // If its a valid path
    if (pathName.length() > 0)
    {
        disableAllInteractions();

        if (this->baseImage)
        {
            this->baseImage->hide();
            delete this->baseImage;
        }
        if (this->transImage)
        {
            this->transImage->hide();
            delete this->transImage;
            this->transImage = nullptr;
        }

        SITVGData data = std::move( SITVGLoader::readSitvgFile(pathName.toUtf8().constData()) );

        this->baseImage = new SITVGViewer( std::move(data), QString("Imagen inicial"), nullptr );

        // Show the filename in the label for it.
        ui->fileNameLabel->setText(pathName);
        enableAllInteractions();
        //this->baseImage->show();
        return true;
    }
    else
        return false;
}

void SITVGWindow::disableAllInteractions()
{
    this->enabledInteractions = false;

    ui->addButton->setEnabled(false);
    ui->applyButton->setEnabled(false);
    ui->changeFileButton->setEnabled(false);
    ui->cleanListButton->setEnabled(false);
    ui->cleanParamButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->viewBaseButton->setEnabled(false);
    ui->viewTransButtom->setEnabled(false);

    ui->reflectionSelect->setEnabled(false);
    ui->scalingSelect->setEnabled(false);
    ui->translationSelect->setEnabled(false);

    ui->factorLineEdit->setEnabled(false);
    ui->xLineEdit->setEnabled(false);
    ui->yLineEdit->setEnabled(false);
}

void SITVGWindow::enableAllInteractions()
{
    this->enabledInteractions = true;

    ui->addButton->setEnabled(true);
    ui->applyButton->setEnabled(true);
    ui->changeFileButton->setEnabled(true);
    ui->cleanListButton->setEnabled(true);
    ui->cleanParamButton->setEnabled(true);
    if (0) ui->saveButton->setEnabled(true);
    if (this->baseImage) ui->viewBaseButton->setEnabled(true);
    if (this->transImage) ui->viewTransButtom->setEnabled(true);

    ui->reflectionSelect->setEnabled(true);
    ui->scalingSelect->setEnabled(true);
    ui->translationSelect->setEnabled(true);

    ui->factorLineEdit->setEnabled(true);
    ui->xLineEdit->setEnabled(true);
    ui->yLineEdit->setEnabled(true);
}

void SITVGWindow::sendTransformations()
{
    bool success = false;

    float * coordsWithPadding = nullptr;
    unsigned noOfCoordinates = 0;
    int * transformations = nullptr;
    int noOfTransformations = 0;

    this->transImage = this->baseImage->newClone();
    this->transImage->getDataForTransformation(coordsWithPadding, noOfCoordinates);
    this->transList.getDataForTransformation(transformations, noOfTransformations);

    noOfCoordinates += noOfCoordinates % 16;

    //Send and receive data to and from kernel
    int ret = 0, fd = open("/dev/ebbchar", O_RDWR); // Opens the device with read/write access

    if (fd >= 0)
    {
        ret = write(fd, (char*)coordsWithPadding, 2*(noOfCoordinates*4) ); // Send the string to the LKM
        if (ret >= 0)
        {
            ret = write(fd, (char*)transformations, noOfTransformations*4 ); // Send the string to the LKM
            if (ret >= 0)
            {
                ret = read(fd, (char*)coordsWithPadding, noOfCoordinates*4); // Read the response from the LKM

                if (ret < 0) {
                    perror("Failed to read the message from the device.");
                }
                else
                {
                    success = true;
                    this->transImage->applyTransformations(coordsWithPadding);
                    this->transList.clear();
                }
            }
        }
    }

    if (!success)
        ui->statusBar->showMessage(tr("Error al comunicarse con el dispositivo."), 5000);

    delete [] coordsWithPadding;
    delete [] transformations;
}

void SITVGWindow::on_changeFileButton_clicked()
{
    if (setInputFile())
        ui->statusBar->showMessage(tr("Imagen cambiada."), 8000);
}

void SITVGWindow::on_viewBaseButton_clicked()
{
    if (baseImage)
    {
        baseImage->show();
    }
    else
    {
        ui->statusBar->showMessage(tr("Aún no se ha cargado una imagen para transformar."), 5000);
    }
}

void SITVGWindow::on_addButton_clicked()
{
    this->disableAllInteractions();
    if (ui->reflectionSelect->isChecked())
    {
        Transformation trans;
        trans.id = vectReflexion;

        this->transList.append(trans);
        this->enableAllInteractions();
        ui->statusBar->showMessage(tr("Reflexión agregada a la cola de transformaciones."), 3000);
        return;
    }

    if (ui->scalingSelect->isChecked())
    {
        Transformation trans;
        trans.id = vectScaling;

        const QString& factorText = this->ui->factorLineEdit->text();
        bool valid = true;
        trans.dataOf.vScaling.scalePercent = factorText.toFloat(&valid);
        if (!valid)
        {
            ui->statusBar->showMessage(tr("Factor de escalamiento no reconocido. Por favor ingresa un número real."), 5000);
        }
        else
        {
            ui->factorLineEdit->clear();
            this->transList.append(trans);
            ui->statusBar->showMessage(tr("Escalación agregada a la cola de transformaciones."), 3000);
        }
        this->enableAllInteractions();
        return;
    }

    if (ui->translationSelect->isChecked())
    {
        Transformation trans;
        trans.id = vectTranslation;

        const QString& xText = this->ui->xLineEdit->text();
        const QString& yText = this->ui->yLineEdit->text();
        bool valid1 = true, valid2 = true;
        trans.dataOf.vTranslation.xTranslating = xText.toFloat(&valid1);
        trans.dataOf.vTranslation.yTranslating = yText.toFloat(&valid2);

        if (!valid1 || !valid2)
        {
            ui->statusBar->showMessage(tr("Distancias de traslación no reconocidas. Por favor ingresa números reales."), 5000);
        }
        else
        {
            ui->xLineEdit->clear();
            ui->yLineEdit->clear();
            this->transList.append(trans);
            ui->statusBar->showMessage(tr("Traslación agregada a la cola de transformaciones."), 3000);
        }
        this->enableAllInteractions();
        return;
    }

    ui->statusBar->showMessage(tr("Por favor, selecciona alguna transformación para agregar."), 5000);
    this->enableAllInteractions();
}

void SITVGWindow::on_cleanParamButton_clicked()
{
    this->disableAllInteractions();
    ui->statusBar->showMessage(tr("Parámetros limpiados."), 3000);
    ui->factorLineEdit->clear();
    ui->xLineEdit->clear();
    ui->yLineEdit->clear();
    this->enableAllInteractions();
}

void SITVGWindow::on_cleanListButton_clicked()
{
    if (transList.size() > 0)
    {
        this->disableAllInteractions();
        ui->statusBar->showMessage(tr("La cola de transformaciones ha sido vaciada."), 3000);
        transList.clear();
        this->enableAllInteractions();
    }
    else
    {
        ui->statusBar->showMessage(tr("La lista ya está vacía."), 5000);
    }
}

void SITVGWindow::on_applyButton_clicked()
{
    ui->statusBar->showMessage(tr("Funcionalidad implementada en un futuro próximo."), 8000);

    if (transList.size())
    {
        if (this->baseImage)
        {
            this->disableAllInteractions();
            ui->statusBar->showMessage(tr("Aplicando transformaciones. Por favor espera, esto podría tardar un poco."));
            this->sendTransformations();
            this->enableAllInteractions();
        }
        else
        {
            ui->statusBar->showMessage(tr("Todavía no se ha cargado una imagen para transformar."), 5000);
        }
    }
    else
    {
        ui->statusBar->showMessage(tr("Primero agrega las transformaciones por aplicar a la cola de transformaciones."), 5000);
    }
}

void SITVGWindow::on_viewTransButtom_clicked()
{
    if (transImage)
    {
        transImage->show();
    }
    else
    {
        ui->statusBar->showMessage(tr("Aún no se ha transformado la imagen."), 5000);
    }
}

void SITVGWindow::on_saveButton_clicked()
{
    ui->statusBar->showMessage(tr("Funcionalidaddisponible en una actualización futura."), 5000);

    /*// If a transformed image is available:
    if (transImage)
    {
        saveTransImage();
    }
    else
    {
        ui->statusBar->showMessage(tr("No hay una imagen transformada disponible para salvar."), 5000);
    }*/
}
