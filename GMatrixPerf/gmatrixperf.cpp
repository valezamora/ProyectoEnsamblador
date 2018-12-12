#include "gmatrixperf.h"
#include "ui_gmatrixperf.h"

GMatrixPerf::GMatrixPerf(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GMatrixPerf)
{
    ui->setupUi(this);
}

GMatrixPerf::~GMatrixPerf()
{
    delete ui;
}
