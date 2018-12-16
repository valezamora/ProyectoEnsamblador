#ifndef BITMAPVIEWER_H
#define BITMAPVIEWER_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <utility>
#include <QPixmap>
#include <QVector>
#include <QPainter>
#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>

namespace Ui {
class BitmapViewer;
}

class BitmapViewer : public QWidget
{
    Q_OBJECT

  private:
    Ui::BitmapViewer * ui;
    QGraphicsScene * scene;
    QPixmap bitmap;
    QImage image;

    // With 000s
    char * colorsArray = nullptr;

    int colorsArraySize = 0;

  public:
    explicit BitmapViewer(QString * filePath, QWidget *parent = 0);
    ~BitmapViewer();

    /**
     * @brief Returns a pointer to a copy of the object.
     * @remarks Returned object must be deallocated from dynamic memory.
     */
    BitmapViewer * newClone() const;

    /**
     * @brief Gets the data of the image needed to transform its bits.
     * @param colors Pointer in which the colors vector is put.
     * @param noOfColors Unsigned integer in which the amount of colors is put.
     */
    void getDataForTransformation(char *&colors, unsigned & noOfBytes) const;

    /**
     * @brief Modifies the images data to assume the transformed colors
     * in xsThenYsArray. For this, a copy of the array is used.
     * @remarks The transformed array must be derived from this image's data.
     * It must also be deallocated from dynamic memory afterwards.
     */
    void applyTransformations(const char *colorsArray);

    /**
     * @brief Opens and reads the image at filePath.
     * @return The QPixMap with the image's data.
     */
    QPixmap readImage(QString filePath);

  private:
    /**
     * @brief Paints the bitmap image to the scene
     */
    void paintBitmap();
};

#endif // BITMAPVIEWER_H
