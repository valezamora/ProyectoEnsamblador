#include "sitvgviewer.h"
#include "ui_sitvgviewer.h"

SITVGViewer::SITVGViewer(SITVGData && imgData, const QString & windowTitle, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SITVGViewer),
    imgData (std::move(imgData))
{
    ui->setupUi(this);
    setWindowTitle(windowTitle);
    ui->graphicsView->setScene(&this->scene);

    this->paintSITVG();
}

SITVGViewer::~SITVGViewer()
{
    ui->graphicsView->hide();
    //this->imgData.clear(); Automatically cleared
    delete ui;
}

// Debería hacerla un thread aparte. ###############################################################################
void SITVGViewer::paintSITVG()
{
    unsigned long long coordIndex = 0;
    short verticesAmount = 0;
    bool closedFig = false;

    QPen pen;

    float x1 = 0, x2 = 0, y1 = 0, y2 = 0, firstX = 0, firstY = 0;

    for (unsigned fig = 0; fig < this->imgData.getFigsAmount(); ++fig )
    {
        pen.setColor(this->imgData.colorAt(fig).argb());
        pen.setWidth(this->imgData.thicknessAt(fig));

        verticesAmount = this->imgData.verticesAmountAt(fig);

        if (verticesAmount == 0)
            continue;

        if (verticesAmount < 0)
        {
            verticesAmount *= -1;
            closedFig = true;
        }
        else
            closedFig = false;

        firstX = this->imgData.xAt(coordIndex);
        firstY = this->imgData.yAt(coordIndex++);

        if (verticesAmount == 1)  // Draw dot
        {
            this->scene.addLine(firstX - 1, firstY - 1, firstX+1, firstY+1, pen);
            this->scene.addLine(firstX + 1, firstY - 1, firstX - 1, firstY + 1, pen);
            // Fix... Might not draw dots. ##################################################################
        }
        else // Draw lines
        {
            x1 = firstX;
            y1 = firstY;

            for (short ver = 1; ver < verticesAmount; ++ver)
            {
                x2 = this->imgData.xAt(coordIndex);
                y2 = this->imgData.yAt(coordIndex ++);
                this->scene.addLine(x1, y1, x2, y2, pen);

                x1 = x2;
                y1 = y2;
            }

            // If the number of vertices in the figure was negative, the first and last vertices are connected.
            if (closedFig)
            {
                this->scene.addLine(x2, y2, firstX, firstY, pen);
            }
        }
    }
}
