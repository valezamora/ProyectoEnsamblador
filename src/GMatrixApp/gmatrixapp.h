#ifndef GMATRIXAPP_H
#define GMATRIXAPP_H

#include <QMainWindow>
#include "sitvgwindow.h"
//#include "bitmapwindow.h"

namespace Ui {
class GMatrixApp;
}

class GMatrixApp : public QMainWindow
{
    Q_OBJECT

  private:
    SITVGWindow * sitvgW = nullptr;
    //BitmapWindow * bitmapW = nullptr;

  public:
    explicit GMatrixApp(QWidget *parent = 0);
    ~GMatrixApp();

  private slots: /// Self explanatory slots for widgets interactions.

    void on_vectorialButton_clicked();

    void on_bitmapButton_clicked();

  private:
    Ui::GMatrixApp *ui;

  public slots:
    void endExecution();

};

#endif // GMATRIXAPP_H
