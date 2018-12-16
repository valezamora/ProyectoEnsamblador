#ifndef SITVGWINDOW_H
#define SITVGWINDOW_H

#include <QWidget>
#include "sitvgdata.h"
#include "sitvgloader.h"
#include "sitvgviewer.h"
#include <QString>
#include <QFileDialog>
#include "transformationlist.h"
//#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <QStatusBar>

namespace Ui {
class SITVGWindow;
}

/**
 * @brief Class for managing SITGV transformations.
 * @remarks Class to be converted to a non main window.
 */
class SITVGWindow : public QWidget
{
    Q_OBJECT

  private:
    /// User interface
    Ui::SITVGWindow *ui;

    /// Input SITVG image
    SITVGViewer * baseImage;

    /// Transformed SITVG image
    SITVGViewer * transImage;

    /// List of transformations stored as an array
    TransformationList transList;

    /// True when most of the user interactible widgets are activated.
    bool enabledInteractions = false;

    /// Window status bar
    QStatusBar * statusBar;

  public:
    explicit SITVGWindow(/*QString inputFilePath,*/ QWidget *parent = 0);
    ~SITVGWindow();

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
     * @brief Opens a new SITVG file as image to transform.
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

#endif // SITVGWINDOW_H
