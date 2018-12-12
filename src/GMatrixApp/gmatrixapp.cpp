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
    SITVGWindow sitvgW;
    this->hide();
    sitvgW.exec(); // Should block current window
    this->close();
}

void GMatrixApp::on_bitmapButton_clicked()
{
    BitmapWindow bitmapW;
    this->hide();
    bitmapW.exec(); // Should block current window
    this->close();
}
