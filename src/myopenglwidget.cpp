#include "myopenglwidget.h"


#include <QMessageBox>
#include <QApplication>
#include <QDateTime>

#include <iostream>
#include <stdexcept>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :QOpenGLWidget(parent), _openglDemo(nullptr), _lastime(0) {
    setFocusPolicy(Qt::StrongFocus); startTimer(1000/60);
    // add all demo constructors here
    _democonstructors.emplace_back([](int width, int height)->OpenGLDemo*{
        std::cout << "Hello cube" << std::endl; return new OpenGLDemo(width, height);
        } );
}

MyOpenGLWidget::~MyOpenGLWidget() {
    cleanup();
}

QSize MyOpenGLWidget::minimumSizeHint() const
{
    return {512, 512};
}

QSize MyOpenGLWidget::sizeHint() const
{
    return {1080, 720};
}

void MyOpenGLWidget::cleanup() {
    _democonstructors.clear();
    _openglDemo.reset(nullptr);
}

void MyOpenGLWidget::initializeGL() {
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MyOpenGLWidget::cleanup);

    // Initialize OpenGL and all OpenGL dependent stuff below
    _openglDemo.reset(_democonstructors[0](width(), height()));
}

void MyOpenGLWidget::paintGL() {
    std::int64_t starttime = QDateTime::currentMSecsSinceEpoch();
    _openglDemo->draw();
    glFinish();
    std::int64_t endtime = QDateTime::currentMSecsSinceEpoch();
    _lastime = endtime-starttime;
}

void MyOpenGLWidget::resizeGL(int width, int height) {
    _openglDemo->resize(width, height);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
    // buttons are 0(left), 1(right) to 2(middle)
    int b;
    Qt::MouseButton button=event->button();
    if (button & Qt::LeftButton) {
        if ((event->modifiers() & Qt::AltModifier))
            b = 2;
        else
            b = 0;
    } else if (button & Qt::RightButton)
        b = 1;
    else if (button & Qt::MiddleButton)
        b = 2;
    else
        b=3;
    _openglDemo->mouseclick(b, event->x(), event->y());
    _lastime = QDateTime::currentMSecsSinceEpoch();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    _openglDemo->mousemove(event->x(), event->y());
    update();
}

void MyOpenGLWidget::wheelEvent( QWheelEvent* event ) {
    _openglDemo->mousewheel( event->angleDelta().y() * 0.01f + event->angleDelta().x() * 0.01f );
    update();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event) {
    auto key = event->key();
    switch(key) {
        case Qt::Key_Escape:
            QApplication::quit();
        // Demo keys
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            activatedemo(key-Qt::Key_0);
            break;
        // Move keys
        case Qt::Key_Q:
            keys[Qt::Key_Q] = true;
            QWidget::keyPressEvent(event);
            break;
        case Qt::Key_Z:
            keys[Qt::Key_Z] = true;
            QWidget::keyPressEvent(event);
            break;
        case Qt::Key_D:
            keys[Qt::Key_D] = true;
            QWidget::keyPressEvent(event);
            break;
        case Qt::Key_S:
            keys[Qt::Key_S] = true;
            QWidget::keyPressEvent(event);
            break;
        case Qt::Key_Space:
            keys[Qt::Key_Space] = true;
            QWidget::keyPressEvent(event);
            break;
        case Qt::Key_Shift:
            keys[Qt::Key_Shift] = true;
            QWidget::keyPressEvent(event);
            break;
        break;
        // Wireframe key
        case Qt::Key_W:
            _openglDemo->toggledrawmode();
            update();
            break;
        // Other keys are transmitted to the scene
        default :
            _openglDemo->keyboard(event->text().toStdString()[0]);
            update();
    }
}

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    keys[event->key()] = false;
    QWidget::keyReleaseEvent(event);
}

const double fps = 1/60.f;

void MyOpenGLWidget::timerEvent(QTimerEvent *event) {
    if(keys[Qt::Key_S]) {
        _openglDemo->keyboardmove(Qt::Key_Down - Qt::Key_Left, fps /*double(_lastime)*/);
        update();
    }
    if(keys[Qt::Key_Z]) {
        _openglDemo->keyboardmove(Qt::Key_Up - Qt::Key_Left, fps /*double(_lastime)*/);
        update();
    }
    if(keys[Qt::Key_Q]) {
        _openglDemo->keyboardmove(Qt::Key_Left - Qt::Key_Left, fps /*double(_lastime)*/);
        update();
    }
    if(keys[Qt::Key_D]) {
        _openglDemo->keyboardmove(Qt::Key_Right - Qt::Key_Left, fps /*double(_lastime)*/);
        update();
    }
    if(keys[Qt::Key_Space]) {
        _openglDemo->keyboardmove(Qt::Key_Space, fps /*double(_lastime)*/);
        update();
    }
    if(keys[Qt::Key_Shift]) {
        _openglDemo->keyboardmove(Qt::Key_Shift, fps /*double(_lastime)*/);
        update();
    }

}

void MyOpenGLWidget::activatedemo(unsigned int numdemo) {
    if (numdemo < _democonstructors.size()) {
        std::cout << "Activating demo " << numdemo << " : ";
        makeCurrent();
        _openglDemo.reset(_democonstructors[numdemo](width(), height()));
        doneCurrent();
        update();
    }
}

