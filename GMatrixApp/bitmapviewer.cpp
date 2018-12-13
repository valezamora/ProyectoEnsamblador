#include "bitmapviewer.h"
#include "ui_bitmapviewer.h"

BitmapViewer::BitmapViewer(QString * filePath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BitmapViewer),
    scene(new QGraphicsScene(this)),
    bitmap()
{
    ui->setupUi(this);
    if (filePath)
    {
        bitmap = readImage(*filePath);
        paintBitmap();
    }
    ui->graphicsView->setScene(scene);
    setWindowTitle("Imagen base");
}

BitmapViewer::~BitmapViewer()
{
    delete colorsArray;
    delete scene;
    delete ui;
}

BitmapViewer *BitmapViewer::newClone() const
{
    BitmapViewer * clone = new BitmapViewer(nullptr);
    clone->bitmap = this->bitmap;
    clone->colorsArraySize = this->colorsArraySize;
    clone->colorsArray = new char [colorsArraySize];

    for (int i = 0; i < colorsArraySize; ++i)
        clone->colorsArray[i] = this->colorsArray[i];

    return clone;
}

void BitmapViewer::getDataForTransformation(char *&colors, unsigned &noOfBytes) const
{
    colors = new char [colorsArraySize];
    for (int i = 0; i < colorsArraySize; ++i)
        colors[i] = this->colorsArray[i];
    noOfBytes = this->colorsArraySize;
}

QPixmap BitmapViewer::readImage(QString filePath){
    QPixmap pixmap;
    pixmap.QPixmap::load(filePath);
    QImage image = pixmap.toImage();

    QVector<QVector<int>> reds(image.height());
    QVector<QVector<int>> greens(image.height());
    QVector<QVector<int>> blues(image.height());

    for(int i = 0; i < image.height(); ++i) // to get each line
    {
        QRgb * rgb = (QRgb*)image.scanLine(i); // get line at i
        for(int j = 0; j < image.width(); ++j) // iterate over each pixel in each line
        {
            reds[i]<<qRed(*rgb);
            greens[i]<<qGreen(*rgb);
            blues[i]<<qBlue(*rgb);

            ++rgb; // increment rgb to go to the next pixel
        }
    }

    int size = image.width()*image.height()*3;

    this->colorsArraySize = size + (64 - size % 64);

    this->colorsArray = new char[colorsArraySize];

    int counter = 0;

    for(int i = 0; i < image.height();i++)
    {
        for(int j = 0; j < image.width();j++)
        {
            this->colorsArray[counter++]=(char) reds[i][j];
            this->colorsArray[counter++]=(char) greens[i][j];
            this->colorsArray[counter++]=(char) blues[i][j];
        }
    }
    return pixmap;
}

void BitmapViewer::paintBitmap(){
    QPainter painter(this);
    painter.drawPixmap(1,1,1000,1000,bitmap);
    scene->addPixmap(bitmap);
}

void BitmapViewer::applyTransformations(const char * colorsArray)
{
    //
    // Aplicar las transformaciones al arreglo de colores utilizando el argumento.
    //
    paintBitmap();
    setWindowTitle("Imagen transformada");
}
