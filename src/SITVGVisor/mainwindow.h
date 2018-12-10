#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sitvgdata.h"
#include "sitvgloader.h"
#include "sitvgviewer.h"
#include <QString>
#include <QFileDialog>
#include "transformationlist.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief Class for managing SITGV transformations.
 * @remarks Class to be converted to a non main window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

  private:
    /// User interface
    Ui::MainWindow *ui;

    /// Input SITVG image
    SITVGViewer * baseImage;

    /// Transformed SITVG image
    SITVGViewer * transImage;

    /// List of transformations stored as an array
    TransformationList transList;

    /// True when most of the user interactible widgets are activated.
    bool enabledInteractions = false;

  public:
    explicit MainWindow(/*QString inputFilePath,*/ QWidget *parent = 0);
    ~MainWindow();

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

#endif // MAINWINDOW_H
