#include "HelloBezierCurve.h"
#include <iostream>
#include "Geometry/Drawable.h"
#include "Geometry/CubeMesh.h"
#include "Geometry/BezierCurveMesh.h"
#include "Geometry/Material.h"

HelloBezierCurve::HelloBezierCurve(int width, int height) : OpenGLDemo(width, height) {

    //Create Shader and Create Renderer with Shader
    Shader Meshshader = Shader();
    Meshshader.createProgram("../src/Shader/DefautV.shader","../src/Shader/DefautF.shader");
    Shader lineShader = Shader();
    lineShader.createProgram("../src/Shader/LineShaderV.shader","../src/Shader/LineShaderF.shader");
    Shader lightShader = Shader();
    lightShader.createProgram("../src/Shader/LightV.shader","../src/Shader/LightF.shader");
    m_renderer = new Renderer(Meshshader, lineShader, lightShader, width, height);

    //Add AxisMesh
    m_renderer->add_Drawable(new AxisMesh());

    auto *lightCube1 = new CubeMesh(glm::vec3(0.0), 1.0f);
    auto *lightCube2 = new CubeMesh(glm::vec3(0.0), 1.0f);
    auto *lightCube3 = new CubeMesh(glm::vec3(0.0), 1.0f);

    auto *front_light = new Light(lightCube1, glm::vec4(0.0f, 3.0f, 10.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
    auto *side_light = new Light(lightCube2, glm::vec4(10.0f, 1.0f, -2.0f, 1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
    auto *back_light = new Light(lightCube3, glm::vec4(0.0f, -.5f, -10.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    m_renderer->add_Light(front_light);
    m_renderer->add_Light(side_light);
    m_renderer->add_Light(back_light);

    //Create control_point
    std::vector<glm::vec3> c_point = {glm::vec3(-1.0,0.0,-2.0),
                                      glm::vec3(-2.5,-1.0,-1.0),
                                      glm::vec3(-1.5,1.0,0.5),
                                      glm::vec3(-2.3,0.2,1.0)};
    //Create and add Bezier Curve Mesh
    auto *bezier_nbseg = new BezierCurveMesh(150 , c_point);
    glm::vec3 nbseg_trans = glm::vec3(5.0f,0.0f,0.0f);
    bezier_nbseg->translate(nbseg_trans);
    m_renderer->add_Drawable(bezier_nbseg);

    auto *bezier_lseg = new BezierCurveMesh(0.001f, 0.0001f, c_point);
    glm::vec3 lseg_trans = glm::vec3(-1.0f,0.0f,0.0f);
    bezier_lseg->translate(lseg_trans);
    m_renderer->add_Drawable(bezier_lseg);

    //Create and add CubeMesh ControlPoint
    auto *cubeMesh = new CubeMesh(glm::vec3(0.0), 1.0f);
    cubeMesh->setMaterial(rought);
    cubeMesh->setColor(glm::vec3(0.2,0.2,0.2));
    m_renderer->add_Drawable(cubeMesh);
    for(int i = 0; i < (int) c_point.size(); i++){
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), c_point[i]+nbseg_trans);
        trans = glm::scale(trans, glm::vec3(0.05));
        if(i==0) {
            cubeMesh->setModel(trans);
        }
        else{
            cubeMesh->add_model(trans);
        }
    }

    for(auto & i : c_point){
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), i+lseg_trans);
        trans = glm::scale(trans, glm::vec3(0.05));
        cubeMesh->add_model(trans);
    }
}

HelloBezierCurve::~HelloBezierCurve() {
    delete m_renderer;
}

void HelloBezierCurve::resize(int width, int height) {
    OpenGLDemo::resize(width,height);
    m_renderer->resize(width, height);
}

void HelloBezierCurve::draw() {
    OpenGLDemo::draw();

    //std::cout << "drawcall" << std::endl;
    m_renderer->Draw();

}

void HelloBezierCurve::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    m_renderer->get_Camera()->processmouseclick(button, xpos, ypos);
}

void HelloBezierCurve::mousemove(float xpos, float ypos) {
    m_renderer->get_Camera()->processmousemovement(_button, xpos, ypos, true);
}

void HelloBezierCurve::mousewheel(float delta) {
    m_renderer->get_Camera()->processmousescroll(delta);
}

void HelloBezierCurve::keyboardmove(int k, double time) {
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

bool HelloBezierCurve::keyboard(unsigned char k) {
    bool b = false;
    switch(k) {
        case 'c':
            m_renderer->change_Camera();
            b = true;
            break;
        case 'n':
            m_renderer->toggleNormalmode();
            break;
        case 't':
            m_renderer->toggleTexcoordmode();
            break;
        default:
            b = false;
    }
    return b;
}

