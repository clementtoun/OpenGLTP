#include "opengldemo.h"
#include <iostream>
#include "Geometry/Drawable.h"
#include "Geometry/CubeMesh.h"
#include "Geometry/LineMesh.h"
#include "Geometry/BezierCurveMesh.h"
#include "Geometry/BezierSurfaceMesh.h"

OpenGLDemo::OpenGLDemo(int width, int height) :  _width(width), _height(height), _drawfill(true) {
    if (!initializeOpenGLFunctions()) {
        std::cout << "OpenGL initialization error\n"
                     "MyOpenGLWidget::initializeGL() : "
                     "Unable to initialize OpenGL functions" << std::endl;
        exit(1);
    }
    Shader shader = Shader();
    shader.createProgram("../src/Shader/DefautV.shader","../src/Shader/DefautF.shader");
    Shader lineShader = Shader();
    lineShader.createProgram("../src/Shader/LineShaderV.shader","../src/Shader/LineShaderF.shader");
    m_renderer = new Renderer(shader, lineShader, width, height);

    m_renderer->add_Drawable(new AxisMesh());

    std::vector<glm::vec3> c_point = {glm::vec3(-1.0,0.0,-2.0),
                                      glm::vec3(-2.5,-1.0,-1.0),
                                      glm::vec3(-1.5,1.0,0.5),
                                      glm::vec3(-2.3,0.2,1.0)};
    m_renderer->add_Drawable(new BezierCurveMesh(150 , c_point));

    auto *cubeMesh = new CubeMesh(glm::vec3(0.0), 1.0f);
    m_renderer->add_Drawable(cubeMesh);

    for(int i = 0; i < (int) c_point.size(); i++){
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), c_point[i]);
        trans = glm::scale(trans, glm::vec3(0.1));
        if(i==0) {
            cubeMesh->setModel(trans, 0);
            cubeMesh->setColor(glm::vec3(0.960, 0.843, 0.219));
        }
        else{
            cubeMesh->add_model(trans);
        }
    }

    std::vector<std::vector<glm::vec3>> c_point_grid;
    c_point_grid.emplace_back(std::vector<glm::vec3>({glm::vec3(1.0,0.0,0.0),glm::vec3(1.0,0.5,1.0),glm::vec3(1.0,0.0,2.0)}));
    c_point_grid.emplace_back(std::vector<glm::vec3>({glm::vec3(2.0,0.5,0.0),glm::vec3(2.0,0.0,1.0),glm::vec3(2.0,-0.5,2.0)}));
    c_point_grid.emplace_back(std::vector<glm::vec3>({glm::vec3(3.0,0.0,0.0),glm::vec3(3.0,-0.5,1.0),glm::vec3(3.0,0.5,2.0)}));
    auto *bezier_surface = new BezierSurfaceMesh(16, 16, c_point_grid);
    bezier_surface->setColor(glm::vec3(0.0,0.8,0.4));
    m_renderer->add_Drawable(bezier_surface);

    LineMesh *line = new LineMesh();
    std::vector<Vertex> vertices = bezier_surface->getVertices();
    int j = 0;
    for(int i = 0; i < (int)vertices.size(); i++) {
        line->addVertex(vertices[i].vertices);
        line->addVertex(vertices[i].vertices + (vertices[i].Normal) * 0.1f);
        line->addLine(j++, j++);
    }
    line->setupLineMesh();
    m_renderer->add_Drawable(line);

    for(auto &line : c_point_grid){
        for(auto &point : line){
            glm::mat4 trans = glm::translate(glm::mat4(1.0f), point);
            trans = glm::scale(trans, glm::vec3(0.1));
            cubeMesh->add_model(trans);
        }
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
}

OpenGLDemo::~OpenGLDemo() {
    delete m_renderer;
}

void OpenGLDemo::resize(int width, int height) {
   _width = width;
   _height = height;
    glViewport(0, 0, _width, _height);
    m_renderer->resize(_width, _height);
}

void OpenGLDemo::draw() {
    glClearColor(0.023, 0.313, 0.454, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_drawfill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //std::cout << "drawcall" << std::endl;
    m_renderer->Draw();

}

void OpenGLDemo::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    m_renderer->get_Camera()->processmouseclick(button, xpos, ypos);
}

void OpenGLDemo::mousemove(float xpos, float ypos) {
    m_renderer->get_Camera()->processmousemovement(_button, xpos, ypos, true);
}

void OpenGLDemo::mousewheel(float delta) {
    m_renderer->get_Camera()->processmousescroll(delta);
}

void OpenGLDemo::keyboardmove(int k, double time) {
    switch (k) {
        case 0x01000020:
            m_renderer->get_Camera()->processkeyboard(Camera_Movement(DOWN), time);
            break;
        case 0x20:
            m_renderer->get_Camera()->processkeyboard(Camera_Movement(UP), time);
            break;
        default:
            m_renderer->get_Camera()->processkeyboard(Camera_Movement(k), time);
    }
}

bool OpenGLDemo::keyboard(unsigned char k) {
    bool b;
    if(k == 'c'){
        m_renderer->change_Camera();
        b=true;
    }
    else if (k == 'n'){
        m_renderer->toggleNormalmode();
    }
    else
        b=false;
    return b;
}

void OpenGLDemo::toggledrawmode() {
    _drawfill = !_drawfill;
}

