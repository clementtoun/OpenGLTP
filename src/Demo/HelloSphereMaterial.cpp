#include "Demo/HelloSphereMaterial.h"
#include <iostream>
#include "Geometry/Drawable.h"
#include "Geometry/SphereMesh.h"
#include "Geometry/Material.h"
#include "Geometry/LineMesh.h"

HelloSphereMaterial::HelloSphereMaterial(int width, int height) : OpenGLDemo(width, height) {

    //Create Shader and Create Renderer with Shader
    Shader Meshshader = Shader();
    Meshshader.createProgram("../src/Shader/DefautV.shader","../src/Shader/DefautF.shader");
    Shader lineShader = Shader();
    lineShader.createProgram("../src/Shader/LineShaderV.shader","../src/Shader/LineShaderF.shader");
    Shader lightShader = Shader();
    lightShader.createProgram("../src/Shader/LightV.shader","../src/Shader/LightF.shader");
    m_renderer = new Renderer(Meshshader, lineShader, lightShader, width, height);

    auto *lightiso1 = new Icosahedron(3);
    auto *lightiso2 = new Icosahedron(3);
    auto *lightiso3 = new Icosahedron(3);

    auto *front_light = new Light(lightiso1, glm::vec4(-5.0f, 3.0f, 3.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
    auto *side_light = new Light(lightiso2, glm::vec4(5.0f, 1.0f, 0.0f, 1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
    auto *back_light = new Light(lightiso3, glm::vec4(0.0f, -5.0f, -2.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    m_renderer->add_Light(front_light);
    m_renderer->add_Light(side_light);
    m_renderer->add_Light(back_light);

    //Add AxisMesh
    m_renderer->add_Drawable(new AxisMesh());

    int row_col = 7;
    float space = 15;
    float x_start = - ((float)row_col/2.f / ((float)row_col) * space);
    float y_start = - ((float)row_col/2.f / ((float)row_col) * space);

    for(int i = 0; i < row_col; i++){
        for(int j = 0; j < row_col; j++){
            std::cout << i << "/" << j << " = " << i/(float)(row_col-1) << " / " << j/(float)(row_col-1) << std::endl;
            auto *UVsphere = new UVSphere(50,50);
            UVsphere->setMaterial(Material(DEFAULT_COLOR, i/(float)(row_col-1), j/(float)(row_col-1)));
            UVsphere->scale(glm::vec3(0.2f));
            UVsphere->translate(glm::vec3(x_start + (i/(float)(row_col-1) * space), y_start + (j/(float)(row_col-1) * space), 0.0f));
            m_renderer->add_Drawable(UVsphere);
        }
    }

    m_renderer->get_Camera()->setposition(glm::vec3(0.0f, 0.0f, 3.5f));

}

HelloSphereMaterial::~HelloSphereMaterial() {
    delete m_renderer;
}

void HelloSphereMaterial::resize(int width, int height) {
    OpenGLDemo::resize(width,height);
    m_renderer->resize(width, height);
}

void HelloSphereMaterial::draw() {
    OpenGLDemo::draw();

    //std::cout << "drawcall" << std::endl;
    m_renderer->Draw();

}

void HelloSphereMaterial::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    m_renderer->get_Camera()->processmouseclick(button, xpos, ypos);
}

void HelloSphereMaterial::mousemove(float xpos, float ypos) {
    m_renderer->get_Camera()->processmousemovement(_button, xpos, ypos, true);
}

void HelloSphereMaterial::mousewheel(float delta) {
    m_renderer->get_Camera()->processmousescroll(delta);
}

void HelloSphereMaterial::keyboardmove(int k, double time) {
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

bool HelloSphereMaterial::keyboard(unsigned char k) {
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

