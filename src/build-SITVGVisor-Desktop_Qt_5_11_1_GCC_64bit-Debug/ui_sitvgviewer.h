/********************************************************************************
** Form generated from reading UI file 'sitvgviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SITVGVIEWER_H
#define UI_SITVGVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SITVGViewer
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *SITVGViewer)
    {
        if (SITVGViewer->objectName().isEmpty())
            SITVGViewer->setObjectName(QStringLiteral("SITVGViewer"));
        SITVGViewer->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SITVGViewer->sizePolicy().hasHeightForWidth());
        SITVGViewer->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(SITVGViewer);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new QGraphicsView(SITVGViewer);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

        horizontalLayout->addWidget(graphicsView);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SITVGViewer);

        QMetaObject::connectSlotsByName(SITVGViewer);
    } // setupUi

    void retranslateUi(QWidget *SITVGViewer)
    {
        SITVGViewer->setWindowTitle(QApplication::translate("SITVGViewer", "SITVG Viewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SITVGViewer: public Ui_SITVGViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SITVGVIEWER_H
