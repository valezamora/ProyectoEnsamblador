#ifndef SITVGVIEWER_H
#define SITVGVIEWER_H

#include <QWidget>
#include "sitvgdata.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <utility>

namespace Ui {
class SITVGViewer;
}

/**
 * @brief Controller class used to view a SITVG image.
 * @details Depends on the QGraphicsScene (model class) to represent the figures contained.
 * This model class, at the same time, is represented by the QGraphicsView widget (view class)
 * found in the User Interface of the SITVGViewer class.
 */
class SITVGViewer : public QWidget
{
    Q_OBJECT

  private:
    Ui::SITVGViewer *ui;
    SITVGData imgData;
    QGraphicsScene scene;

  public:
    explicit SITVGViewer(SITVGData && imgData, const QString & windowTitle, QWidget *parent = 0);
    ~SITVGViewer();

    /**
     * @brief Returns a pointer to a copy of the object.
     * @remarks Returned object must be deallocated from dynamic memory.
     */
    SITVGViewer * newClone() const;

    /**
     * @brief Gets the data of the image needed to transform its vertices.
     * @param coordinates Pointer in which the coordinates vector is put.
     * @param noOfCoordinates Unsigned integer in which the amount of coordinates is put.
     */
    void getDataForTransformation(float * & coordinates, unsigned & noOfCoordinates) const;

    /**
     * @brief Modifies the images data to assume the transformed coordinates
     * in xsThenYsArray. For this, a copy of the array is used.
     * @remarks The transformed array must be derived from this image's data.
     * It must also be deallocated from dynamic memory afterwards.
     */
    void applyTransformations(const float * xsThenYsArray);

  private:
    /**
     * @brief Paints the SITVG image to the scene
     */
    void paintSITVG();
};

#endif // SITVGVIEWER_H
