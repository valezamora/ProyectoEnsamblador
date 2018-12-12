#include "gmatrixperf.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GMatrixPerf w;
    w.show();

    return a.exec();
}
