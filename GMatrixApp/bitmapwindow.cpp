#include "bitmapwindow.h"
#include "ui_bitmapwindow.h"

BitmapWindow::BitmapWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BitmapWindow),
    baseImage(nullptr),
    transImage(nullptr),
    transList(),
    statusBar(new QStatusBar)
{
    ui->setupUi(this);
    ui->fileNameLabel->setText("Ningnuna.");
    ui->statusBarLayout->addWidget(statusBar);
    setInputFile();
    ui->listView->setModel(&transList);
}

BitmapWindow::~BitmapWindow()
{
    if (baseImage)
        delete baseImage;
    if (transImage)
        delete transImage;
    delete statusBar;
    delete ui;
}

bool BitmapWindow::setInputFile()
{
    // Choose file
    QString pathName = QFileDialog::getOpenFileName(this, tr("Seleccione la imagen por transformar"),
                                                    "/home/", tr("Archivos de bitmap (*.bmp *.gif *.jpg *.jpeg *.PNG *.XBM)"));

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

        this->baseImage = new BitmapViewer(&pathName);


        // Show the filename in the label for it.
        ui->fileNameLabel->setText(pathName);
        enableAllInteractions();
        return true;
    }
    else
        return false;
}

void BitmapWindow::disableAllInteractions()
{
    this->enabledInteractions = false;

    ui->addButton->setEnabled(false);
    ui->applyButton_2->setEnabled(false);
    ui->changeFileButton->setEnabled(false);
    ui->cleanListButton->setEnabled(false);
    ui->cleanParamButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->viewBaseButton->setEnabled(false);
    ui->viewTransButtom->setEnabled(false);

    ui->brightSelect->setEnabled(false);
    ui->negativeSelect->setEnabled(false);
    ui->redSelect->setEnabled(false);

    ui->brightLineEdit->setEnabled(false);
    ui->negativeSelect->setEnabled(false);
}

void BitmapWindow::enableAllInteractions()
{
    this->enabledInteractions = true;

    ui->addButton->setEnabled(true);
    ui->applyButton_2->setEnabled(true);
    ui->changeFileButton->setEnabled(true);
    ui->cleanListButton->setEnabled(true);
    ui->cleanParamButton->setEnabled(true);
    if (0) ui->saveButton->setEnabled(true);
    if (this->baseImage) ui->viewBaseButton->setEnabled(true);
    if (this->transImage) ui->viewTransButtom->setEnabled(true);

    ui->brightSelect->setEnabled(true);
    ui->negativeSelect->setEnabled(true);
    ui->redSelect->setEnabled(true);

    ui->brightLineEdit->setEnabled(true);
    ui->negativeSelect->setEnabled(true);
}

void BitmapWindow::sendTransformations()
{
    bool success = false;

    char * colorsWithPadding = nullptr;
    unsigned cWPSize = 0;
    int * transformations = nullptr;
    int noOfTransformations = 0;

    this->transImage = this->baseImage->newClone();
    this->transImage->getDataForTransformation(colorsWithPadding, cWPSize);
    this->transList.getDataForTransformation(transformations, noOfTransformations);

    //Send and receive data to and from kernel
    int ret = 0, fd = open("/dev/ebbchar", O_RDWR); // Opens the device with read/write access

    if (fd >= 0)
    {
        ret = write(fd, (char*)colorsWithPadding, cWPSize); // Send the string to the LKM
        if (ret >= 0)
        {
            ret = write(fd, (char*)transformations, noOfTransformations*4); // Send the string to the LKM
            if (ret >= 0)
            {
                ret = read(fd, (char*)colorsWithPadding, cWPSize); // Read the response from the LKM

                if (ret < 0) {
                    perror("Failed to read the message from the device.");
                }
                else
                {
                    success = true;
                    this->transImage->applyTransformations(colorsWithPadding);
                    this->transList.clear();
                }
            }
        }
    }

    if (!success)
        statusBar->showMessage(tr("Error al comunicarse con el dispositivo."), 5000);

    delete [] colorsWithPadding;
    delete [] transformations;
}

void BitmapWindow::on_changeFileButton_clicked()
{
    if (setInputFile())
        statusBar->showMessage(tr("Imagen cambiada."), 8000);
}

void BitmapWindow::on_viewBaseButton_clicked()
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

void BitmapWindow::on_addButton_clicked()
{
    this->disableAllInteractions();

    if (ui->brightSelect->isChecked())
    {
        Transformation trans;
        trans.id = matBrightness;

        const QString & brText = ui->brightLineEdit->text();
        bool valid = true;
        trans.dataOf.mBrightness.brightnessChange = brText.toFloat(&valid);
        if (!valid)
        {
            statusBar->showMessage(tr("Factor de cambio de brillo no reconocido. Por favor ingresa un número entero."), 5000);
        }
        else
        {
            ui->brightLineEdit->clear();
            this->transList.append(trans);
            statusBar->showMessage(tr("Cambio de brillo agregado a la cola de transformaciones"), 3000);
        }
        this->enableAllInteractions();
        return;
    }

    if (ui->negativeSelect->isChecked())
    {
        Transformation trans;
        trans.id = matNegative;
        this->transList.append(trans);
        statusBar->showMessage(tr("Cambio de color a negativo agregado a la cola de transformaciones"), 3000);
        this->enableAllInteractions();
        return;
    }

    if (ui->redSelect->isChecked())
    {
        Transformation trans;
        trans.id = matRedSat;

        const QString & rsText = ui->redLineEdit->text();
        bool valid = true;
        trans.dataOf.mRedSat.redSatChange = rsText.toFloat(&valid);
        if (!valid)
        {
            statusBar->showMessage(tr("Factor de cambio de saturación roja no reconocido. Por favor ingresa un número entero."), 5000);
        }
        else
        {
            ui->redLineEdit->clear();
            this->transList.append(trans);
            statusBar->showMessage(tr("Cambio de saturación roja agregado a la cola de transformaciones"), 3000);
        }
        this->enableAllInteractions();
        return;
    }

    statusBar->showMessage(tr("Por favor, selecciona alguna transformación para agregar."), 5000);
    this->enableAllInteractions();
}

void BitmapWindow::on_cleanParamButton_clicked()
{
    this->disableAllInteractions();
    statusBar->showMessage(tr("Parámetros limpiados."), 3000);
    ui->brightLineEdit->clear();
    ui->redLineEdit->clear();
    this->enableAllInteractions();
}

void BitmapWindow::on_cleanListButton_clicked()
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

void BitmapWindow::on_applyButton_2_clicked()
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

void BitmapWindow::on_viewTransButtom_clicked()
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

void BitmapWindow::on_saveButton_clicked()
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
