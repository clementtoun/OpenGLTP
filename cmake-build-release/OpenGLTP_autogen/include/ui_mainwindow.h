/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Version_OpenGL;
    QAction *actionHello_clear;
    QAction *actionHello_MyApp;
    QAction *actionHello_BezierCurve;
    QAction *actionHello_BezierSurface;
    QAction *actionHello_SphereMaterial;
    QMenuBar *menuBar;
    QMenu *menuInfo;
    QMenu *menu_Demo;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(512, 512);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        action_Version_OpenGL = new QAction(MainWindow);
        action_Version_OpenGL->setObjectName(QString::fromUtf8("action_Version_OpenGL"));
        actionHello_clear = new QAction(MainWindow);
        actionHello_clear->setObjectName(QString::fromUtf8("actionHello_clear"));
        actionHello_MyApp = new QAction(MainWindow);
        actionHello_MyApp->setObjectName(QString::fromUtf8("actionHello_MyApp"));
        actionHello_BezierCurve = new QAction(MainWindow);
        actionHello_BezierCurve->setObjectName(QString::fromUtf8("actionHello_BezierCurve"));
        actionHello_BezierSurface = new QAction(MainWindow);
        actionHello_BezierSurface->setObjectName(QString::fromUtf8("actionHello_BezierSurface"));
        actionHello_SphereMaterial = new QAction(MainWindow);
        actionHello_SphereMaterial->setObjectName(QString::fromUtf8("actionHello_SphereMaterial"));
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 512, 22));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        menu_Demo = new QMenu(menuBar);
        menu_Demo->setObjectName(QString::fromUtf8("menu_Demo"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Demo->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuInfo->addAction(action_Version_OpenGL);
        menu_Demo->addAction(actionHello_clear);
        menu_Demo->addAction(actionHello_MyApp);
        menu_Demo->addAction(actionHello_BezierCurve);
        menu_Demo->addAction(actionHello_BezierSurface);
        menu_Demo->addAction(actionHello_SphereMaterial);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hello OpenGL ...", nullptr));
        action_Version_OpenGL->setText(QApplication::translate("MainWindow", "&Version OpenGL", nullptr));
        actionHello_clear->setText(QApplication::translate("MainWindow", "Hello clear ...", nullptr));
        actionHello_MyApp->setText(QApplication::translate("MainWindow", "Hello MyApp ...", nullptr));
        actionHello_BezierCurve->setText(QApplication::translate("MainWindow", "Hello BezierCurve ...", nullptr));
        actionHello_BezierSurface->setText(QApplication::translate("MainWindow", "Hello BezierSurface ...", nullptr));
        actionHello_SphereMaterial->setText(QApplication::translate("MainWindow", "Hello SphereMaterial ...", nullptr));
        menuInfo->setTitle(QApplication::translate("MainWindow", "Info", nullptr));
        menu_Demo->setTitle(QApplication::translate("MainWindow", "&Demo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
