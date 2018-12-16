#include "sitvgwindow.h"
#include "ui_sitvgwindow.h"

SITVGWindow::SITVGWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SITVGWindow),
    baseImage(nullptr),
    transImage(nullptr),
    transList(),
    statusBar(new QStatusBar)
{
    ui->setupUi(this);
    ui->fileNameLabel->setText("Ninguna.");
    ui->statusBarLayout->addWidget(statusBar);
    setInputFile();
    ui->listView->setModel(&transList);
}

SITVGWindow::~SITVGWindow()
{
    if (baseImage)
        delete baseImage;
    if (transImage)
        delete transImage;
    delete statusBar;
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
    if (this->transImage) delete this->transImage;
    bool success = false;

    float * coordsWithPadding = nullptr;
    unsigned noOfCoordinates = 0;
    int * transformations = nullptr;
    int noOfTransformations = 0;

    this->transImage = this->baseImage->newClone();
    this->transImage->getDataForTransformation(coordsWithPadding, noOfCoordinates);
    this->transList.getDataForTransformation(transformations, noOfTransformations);

    noOfCoordinates += (16 - noOfCoordinates % 16);
    //Send and receive data to and from kernel
    int ret = 0, fd = open("/dev/ebbchar", O_RDWR); // Opens the device with read/write access
    if (fd >= 0)
    {
        printf("matriz (floats):\n");
        for(int i =0;i<noOfCoordinates*2;i++){
            printf("%f ",coordsWithPadding[i]);
        }
        printf("\n");
        printf("transformations:\n");
        for(int i =0;i<noOfTransformations*3;i++){
            printf("%d ",transformations[i]);
        }
        printf("\n");
        // Send the string to the LKM
        ret = write(fd, (char*)coordsWithPadding, 2*noOfCoordinates*sizeof(float) ); // 2, because there is an X and a Y.
        printf("Importante : %d\n",ret);
        if (ret >= 0)
        {
            // Send the string to the LKM
            int transformationsA [3];
            transformationsA[0] = 2;
            float * transformationsAFloat = (float *) transformationsA;
            transformationsAFloat[1] = -15;
            transformationsAFloat[2] = 100;
            printf("%f %f\n",transformationsA[1],transformationsA[2]);
            //ret = write(fd, (char*)transformations, noOfTransformations*sizeof(int)*3);
            ret = write(fd, (char*)transformationsAFloat, 12);
            //printf("Importante2 : %d\n",ret);

            if (ret >= 0)
            {
                // Read the response from the LKM
                ret = read(fd, (char*)coordsWithPadding, 2*(noOfCoordinates*sizeof(float)) ); // 2, because there is an X and a Y.

                if (ret < 0) {
                    printf("Failed to read the message from the device.\n");
                }
                else
                {
                    success = true;
                    this->transImage->applyTransformations(coordsWithPadding);
                    this->transList.clear();

                }
            }
        }
        for(int i =0;i<noOfCoordinates*2;i++){
            printf("%f ",coordsWithPadding[i]);
        }
        ::close(fd);
    }

    if (!success)
        statusBar->showMessage(tr("Error al comunicarse con el dispositivo."), 5000);

    delete [] coordsWithPadding;
    delete [] transformations;
}

void SITVGWindow::on_changeFileButton_clicked()
{
    if (setInputFile())
        statusBar->showMessage(tr("Imagen cambiada."), 8000);
}

void SITVGWindow::on_viewBaseButton_clicked()
{
    if (baseImage)
    {
        baseImage->show();
    }
    else
    {
        statusBar->showMessage(tr("Aún no se ha cargado una imagen para transformar."), 5000);
    }
}

void SITVGWindow::on_addButton_clicked()
{
    this->disableAllInteractions();

    if (ui->reflectionSelect->isChecked())
    {
        const Transformation trans = Transformation (vectReflexion);
        /*
        trans.id = vectReflexion;
        trans.floatParam(0) = 0;
        trans.floatParam(1) = 0;*/

        this->transList.append(trans);
        this->enableAllInteractions();
        statusBar->showMessage(tr("Reflexión agregada a la cola de transformaciones."), 3000);
        return;
    }

    if (ui->scalingSelect->isChecked())
    {
        const QString& factorText = this->ui->factorLineEdit->text();
        bool valid = true;
        float scalingFactor = factorText.toFloat(&valid);

        if (!valid)
        {
            statusBar->showMessage(tr("Factor de escalamiento no reconocido. Por favor ingresa un número real."), 5000);
        }
        else
        {
            const Transformation trans = Transformation(vectScaling, scalingFactor);
            ui->factorLineEdit->clear();
            this->transList.append(trans);
            statusBar->showMessage(tr("Escalación agregada a la cola de transformaciones."), 3000);
        }
        this->enableAllInteractions();
        return;
    }

    if (ui->translationSelect->isChecked())
    {
        const QString& xText = this->ui->xLineEdit->text(), yText = this->ui->yLineEdit->text();
        bool valid1 = true, valid2 = true;
        float xFactor = xText.toFloat(&valid1), yFactor = yText.toFloat(&valid2);

        if (!valid1 || !valid2)
        {
            statusBar->showMessage(tr("Distancias de traslación no reconocidas. Por favor ingresa números reales."), 5000);
        }
        else
        {
            const Transformation trans (vectTranslation, xFactor, yFactor);
            ui->xLineEdit->clear();
            ui->yLineEdit->clear();
            this->transList.append(trans);
            statusBar->showMessage(tr("Traslación agregada a la cola de transformaciones."), 3000);
        }
        this->enableAllInteractions();
        return;
    }

    statusBar->showMessage(tr("Por favor, selecciona alguna transformación para agregar."), 5000);
    this->enableAllInteractions();
}

void SITVGWindow::on_cleanParamButton_clicked()
{
    this->disableAllInteractions();
    statusBar->showMessage(tr("Parámetros limpiados."), 3000);
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
        statusBar->showMessage(tr("La cola de transformaciones ha sido vaciada."), 3000);
        transList.clear();
        this->enableAllInteractions();
    }
    else
    {
        statusBar->showMessage(tr("La cola ya está vacía."), 5000);
    }
}

void SITVGWindow::on_applyButton_clicked()
{
    if (transList.size())
    {
        if (this->baseImage)
        {
            this->disableAllInteractions();
            statusBar->showMessage(tr("Aplicando transformaciones. Por favor espera, esto podría tardar un poco."));
            this->sendTransformations();
            this->enableAllInteractions();
        }
        else
        {
            statusBar->showMessage(tr("Todavía no se ha cargado una imagen para transformar."), 5000);
        }
    }
    else
    {
        statusBar->showMessage(tr("Primero agrega las transformaciones por aplicar a la cola de transformaciones."), 5000);
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
        statusBar->showMessage(tr("Aún no se ha transformado la imagen."), 5000);
    }
}

void SITVGWindow::on_saveButton_clicked()
{
    statusBar->showMessage(tr("Funcionalidad disponible en una actualización futura."), 5000);

    /*// If a transformed image is available:
    if (transImage)
    {
        saveTransImage();
    }
    else
    {
        statusBar->showMessage(tr("No hay una imagen transformada disponible para salvar."), 5000);
    }*/
}
