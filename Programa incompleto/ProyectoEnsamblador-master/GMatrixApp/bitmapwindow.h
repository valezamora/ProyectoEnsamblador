#ifndef BITMAPWINDOW_H
#define BITMAPWINDOW_H

#include <QWidget>
#include "transformationlist.h"
#include <QFileDialog>
#include "bitmapviewer.h"
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cassert>
#include <QStatusBar>
#include <QString>

namespace Ui {
class BitmapWindow;
}

class BitmapWindow : public QWidget
{
    Q_OBJECT

  private:
    /// User interface
    Ui::BitmapWindow *ui;

    /// Input bitmap image
    BitmapViewer * baseImage;

    /// Transformed bitmap image
    BitmapViewer * transImage;

    /// List of transformations stored as an array
    TransformationList transList;

    /// True when most of the user interactible widgets are activated.
    bool enabledInteractions = false;

    /// Window status bar
    QStatusBar * statusBar;

  public:
    explicit BitmapWindow(QWidget *parent = 0);
    ~BitmapWindow();

  private slots: // Self explanatory widget interactions.

    void on_changeFileButton_clicked();

    void on_viewBaseButton_clicked();

    void on_addButton_clicked();

    void on_cleanParamButton_clicked();

    void on_cleanListButton_clicked();

    void on_applyButton_clicked();

    void on_viewTransButtom_clicked();

    void on_saveButton_clicked();

  private:
    /**
    * @brief Opens a new bitmap file as image to transform.
    */
    bool setInputFile();

    /**
    * @brief Disables every widget's user interactions in the UI.
    */
    void disableAllInteractions();

    /**
    * @brief Enables every currently usable widget's user interactions in the UI.
    */
    void enableAllInteractions();

    /**
    * @brief Sends the SITVG's coordinates and the transformations in the list to
    * the device driver so the transformation process begins.
    */
    void sendTransformations();
};

#endif // BITMAPWINDOW_H
