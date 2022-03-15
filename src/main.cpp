#include "mainwindow.h"

#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QRect rec = QApplication::desktop()->screenGeometry();
    int width = rec.width();
    int height = rec.height();
    MainWindow w;
    w.resize(width/1.5,height/1.5);
    w.show();
    return a.exec();
}
