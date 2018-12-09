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

  private:

    /**
     * @brief Paints the SITVG image to the scene
     */
    void paintSITVG();
};

#endif // SITVGVIEWER_H
