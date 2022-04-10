#include "mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    w.resize(screenGeometry.width()/2.5, screenGeometry.height()/2);
    int x = (screenGeometry.width()-w.width()) / 2;
    int y = (screenGeometry.height()-w.height()) / 2;
    w.move(x,y);
    w.show();
    return a.exec();
}
