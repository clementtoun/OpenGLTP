#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QVBoxLayout>

#include <iostream>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QRect rec = QApplication::desktop()->screenGeometry();
    int w = rec.width();
    int h = rec.height();
    resize(w/1.5, h/1.5);
    move(w/2 - (width()/2),h/2 - (height()/2));
    std::cout << w << '/' << h << '/' << width() << '/' << height() << std::endl;

    ui->setupUi(this);

    openglWidget = new MyOpenGLWidget(this);
    openglWidget->setFocus();

    setCentralWidget(openglWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_action_Version_OpenGL_triggered() {
    std::stringstream message;
    message << "Qt version     : " << qVersion() << std::endl;
    message << "Renderer       : " << glGetString(GL_RENDERER) << std::endl;
    message << "Vendor         : " << glGetString(GL_VENDOR) << std::endl;
    message << "Version        : " << glGetString(GL_VERSION) << std::endl;
    message << "GLSL Version   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    QMessageBox::information(this, "OpenGL Information", message.str().c_str());
}

void MainWindow::on_actionHello_clear_triggered() {
    openglWidget->activatedemo(0);
}

