#include "opengldemo.h"
#include <iostream>


OpenGLDemo::OpenGLDemo(int width, int height) :  _width(width), _height(height), _drawfill(true) {
    if (!initializeOpenGLFunctions()) {
        std::cout << "OpenGL initialization error\n"
                     "MyOpenGLWidget::initializeGL() : "
                     "Unable to initialize OpenGL functions" << std::endl;
        exit(1);
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
}

OpenGLDemo::~OpenGLDemo() = default;

void OpenGLDemo::resize(int width, int height) {
   _width = width;
   _height = height;
    glViewport(0, 0, _width, _height);
}

void OpenGLDemo::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (_drawfill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void OpenGLDemo::mouseclick(int , float , float ) {

}

void OpenGLDemo::mousemove(float , float ) {

}

void OpenGLDemo::mousewheel(float ) {

}

void OpenGLDemo::keyboardmove(int , double ) {

}

bool OpenGLDemo::keyboard(unsigned char ) {
    return false;
}

void OpenGLDemo::toggledrawmode() {
    _drawfill = !_drawfill;
}

