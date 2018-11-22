#ifndef SITVGVIEWER_H
#define SITVGVIEWER_H

#include <QWidget>
#include "sitvgdata.h"
#include <QGraphicsView>
#include <QGraphicsScene>

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
    const SITVGData & imgData;
    const float heightOverWidthRatio;
    QGraphicsScene scene;
    Ui::SITVGViewer *ui;

  public:
    explicit SITVGViewer(const SITVGData & imgData, const QString &windowTitle, QWidget *parent = 0);
    ~SITVGViewer();

    /// Method used for mantaining the SITVG viewer aspect ratio.
    int heightForWidth(int w) const override;

  private:

    /**
     * @brief Paints the SITVG image to the scene
     */
    void paintSITVG();
};

#endif // SITVGVIEWER_H
