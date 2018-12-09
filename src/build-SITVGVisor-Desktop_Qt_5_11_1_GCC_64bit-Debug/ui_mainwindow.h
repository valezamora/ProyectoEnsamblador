/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_File;
    QAction *actionClose_File;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionSITVG_V_conversor_help;
    QAction *actionWindow_help;
    QAction *actionChange_file;
    QAction *actionCambiar_archivo;
    QAction *actionSalir;
    QAction *actionAyuda;
    QAction *actionVolver_al_men_principal;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLabel *fileNameLabel;
    QPushButton *viewBaseButton;
    QPushButton *changeFileButton;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *reflectionSelect;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *scalingSelect;
    QLabel *label_5;
    QLineEdit *factorLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QRadioButton *translationSelect;
    QLabel *label;
    QLineEdit *xLineEdit;
    QLabel *label_2;
    QLineEdit *yLineEdit;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_3;
    QPushButton *addButton;
    QPushButton *cleanParamButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_2;
    QLabel *label_6;
    QLabel *label_3;
    QListView *listView;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *cleanListButton;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *applyButton;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *viewTransButtom;
    QPushButton *saveButton;
    QSpacerItem *horizontalSpacer_11;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(620, 542);
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionClose_File = new QAction(MainWindow);
        actionClose_File->setObjectName(QStringLiteral("actionClose_File"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSITVG_V_conversor_help = new QAction(MainWindow);
        actionSITVG_V_conversor_help->setObjectName(QStringLiteral("actionSITVG_V_conversor_help"));
        actionWindow_help = new QAction(MainWindow);
        actionWindow_help->setObjectName(QStringLiteral("actionWindow_help"));
        actionChange_file = new QAction(MainWindow);
        actionChange_file->setObjectName(QStringLiteral("actionChange_file"));
        actionCambiar_archivo = new QAction(MainWindow);
        actionCambiar_archivo->setObjectName(QStringLiteral("actionCambiar_archivo"));
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QStringLiteral("actionSalir"));
        actionAyuda = new QAction(MainWindow);
        actionAyuda->setObjectName(QStringLiteral("actionAyuda"));
        actionVolver_al_men_principal = new QAction(MainWindow);
        actionVolver_al_men_principal->setObjectName(QStringLiteral("actionVolver_al_men_principal"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_7->setFont(font);

        horizontalLayout_6->addWidget(label_7);

        fileNameLabel = new QLabel(centralWidget);
        fileNameLabel->setObjectName(QStringLiteral("fileNameLabel"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fileNameLabel->sizePolicy().hasHeightForWidth());
        fileNameLabel->setSizePolicy(sizePolicy);
        fileNameLabel->setFont(font);

        horizontalLayout_6->addWidget(fileNameLabel);

        viewBaseButton = new QPushButton(centralWidget);
        viewBaseButton->setObjectName(QStringLiteral("viewBaseButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(viewBaseButton->sizePolicy().hasHeightForWidth());
        viewBaseButton->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(viewBaseButton);

        changeFileButton = new QPushButton(centralWidget);
        changeFileButton->setObjectName(QStringLiteral("changeFileButton"));
        sizePolicy1.setHeightForWidth(changeFileButton->sizePolicy().hasHeightForWidth());
        changeFileButton->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(changeFileButton);


        verticalLayout_2->addLayout(horizontalLayout_6);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        reflectionSelect = new QRadioButton(centralWidget);
        reflectionSelect->setObjectName(QStringLiteral("reflectionSelect"));

        horizontalLayout_4->addWidget(reflectionSelect);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_11->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        scalingSelect = new QRadioButton(centralWidget);
        scalingSelect->setObjectName(QStringLiteral("scalingSelect"));

        horizontalLayout_2->addWidget(scalingSelect);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        factorLineEdit = new QLineEdit(centralWidget);
        factorLineEdit->setObjectName(QStringLiteral("factorLineEdit"));
        sizePolicy1.setHeightForWidth(factorLineEdit->sizePolicy().hasHeightForWidth());
        factorLineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(factorLineEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_11->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        translationSelect = new QRadioButton(centralWidget);
        translationSelect->setObjectName(QStringLiteral("translationSelect"));

        horizontalLayout->addWidget(translationSelect);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        xLineEdit = new QLineEdit(centralWidget);
        xLineEdit->setObjectName(QStringLiteral("xLineEdit"));
        sizePolicy1.setHeightForWidth(xLineEdit->sizePolicy().hasHeightForWidth());
        xLineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(xLineEdit);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        yLineEdit = new QLineEdit(centralWidget);
        yLineEdit->setObjectName(QStringLiteral("yLineEdit"));
        sizePolicy1.setHeightForWidth(yLineEdit->sizePolicy().hasHeightForWidth());
        yLineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(yLineEdit);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);


        verticalLayout_11->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout_11);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        addButton = new QPushButton(centralWidget);
        addButton->setObjectName(QStringLiteral("addButton"));
        sizePolicy1.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
        addButton->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(addButton);

        cleanParamButton = new QPushButton(centralWidget);
        cleanParamButton->setObjectName(QStringLiteral("cleanParamButton"));

        verticalLayout_3->addWidget(cleanParamButton);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_5);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout_2->addWidget(listView);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        cleanListButton = new QPushButton(centralWidget);
        cleanListButton->setObjectName(QStringLiteral("cleanListButton"));

        horizontalLayout_8->addWidget(cleanListButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        applyButton = new QPushButton(centralWidget);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        horizontalLayout_9->addWidget(applyButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        viewTransButtom = new QPushButton(centralWidget);
        viewTransButtom->setObjectName(QStringLiteral("viewTransButtom"));

        horizontalLayout_10->addWidget(viewTransButtom);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        horizontalLayout_10->addWidget(saveButton);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_11);


        verticalLayout_2->addLayout(horizontalLayout_10);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SITVG Viewer", nullptr));
        actionOpen_File->setText(QApplication::translate("MainWindow", "Open file", nullptr));
        actionClose_File->setText(QApplication::translate("MainWindow", "Close current file", nullptr));
        actionClose->setText(QApplication::translate("MainWindow", "Exit", nullptr));
#ifndef QT_NO_WHATSTHIS
        actionClose->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionSITVG_V_conversor_help->setText(QApplication::translate("MainWindow", "SITVG V conversor help", nullptr));
        actionWindow_help->setText(QApplication::translate("MainWindow", "Ayuda", nullptr));
        actionChange_file->setText(QApplication::translate("MainWindow", "Change file", nullptr));
        actionCambiar_archivo->setText(QApplication::translate("MainWindow", "Cambiar archivo", nullptr));
        actionSalir->setText(QApplication::translate("MainWindow", "Salir", nullptr));
        actionAyuda->setText(QApplication::translate("MainWindow", "Ayuda", nullptr));
        actionVolver_al_men_principal->setText(QApplication::translate("MainWindow", "Volver al men\303\272 principal", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Imagen por transformar:", nullptr));
        fileNameLabel->setText(QApplication::translate("MainWindow", "ninguna", nullptr));
        viewBaseButton->setText(QApplication::translate("MainWindow", "Ver imagen", nullptr));
        changeFileButton->setText(QApplication::translate("MainWindow", "Cambiar imagen", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Transformaciones disponibles:", nullptr));
        reflectionSelect->setText(QApplication::translate("MainWindow", "Reflexi\303\263n", nullptr));
        scalingSelect->setText(QApplication::translate("MainWindow", "Escalaci\303\263n", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Factor:", nullptr));
        translationSelect->setText(QApplication::translate("MainWindow", "Translaci\303\263n", nullptr));
        label->setText(QApplication::translate("MainWindow", "X:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Y:", nullptr));
        addButton->setText(QApplication::translate("MainWindow", "Agregar\n"
"transformaci\303\263n", nullptr));
        cleanParamButton->setText(QApplication::translate("MainWindow", "Limpiar\n"
"par\303\241metros", nullptr));
        label_6->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Transformaciones por aplicar:", nullptr));
        cleanListButton->setText(QApplication::translate("MainWindow", "Limpiar cola de transformaciones", nullptr));
        applyButton->setText(QApplication::translate("MainWindow", "Aplicar transformaciones", nullptr));
        viewTransButtom->setText(QApplication::translate("MainWindow", "Ver imagen transformada", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Guardar imagen transformada", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
