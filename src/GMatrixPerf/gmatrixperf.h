#ifndef GMATRIXPERF_H
#define GMATRIXPERF_H

#include <QMainWindow>

namespace Ui {
class GMatrixPerf;
}

class GMatrixPerf : public QMainWindow
{
    Q_OBJECT

public:
    explicit GMatrixPerf(QWidget *parent = 0);
    ~GMatrixPerf();

private:
    Ui::GMatrixPerf *ui;
};

#endif // GMATRIXPERF_H
