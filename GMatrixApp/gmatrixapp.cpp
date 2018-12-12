#include "gmatrixapp.h"
#include "ui_gmatrixapp.h"

GMatrixApp::GMatrixApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GMatrixApp)
{
    ui->setupUi(this);
}

GMatrixApp::~GMatrixApp()
{
    delete ui;
}

void GMatrixApp::on_vectorialButton_clicked()
{
    this->sitvgW = new SITVGWindow();
    this->hide();
    this->sitvgW->show();
}

void GMatrixApp::on_bitmapButton_clicked()
{
    this->bitmapW = new BitmapWindow();
    this->hide();
    this->bitmapW->show();
}

void GMatrixApp::endExecution()
{
    if (sitvgW)
        delete sitvgW;
    if (bitmapW)
        delete bitmapW;
    this->close();
}
