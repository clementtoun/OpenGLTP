#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "myopenglwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    // forbid copy of a main window
    MainWindow(const MainWindow&) = delete;
    MainWindow &operator=(const MainWindow&) = delete;
    ~MainWindow() override;

private slots:
    void on_action_Version_OpenGL_triggered();

    void on_actionHello_clear_triggered();

    void on_actionHello_MyApp_triggered();

    void on_actionHello_BezierCurve_triggered();

    void on_actionHello_BezierSurface_triggered();

    void on_actionHello_SphereMaterial_triggered();

private:
    Ui::MainWindow *ui;
    MyOpenGLWidget *openglWidget;
};

#endif // MAINWINDOW_H
