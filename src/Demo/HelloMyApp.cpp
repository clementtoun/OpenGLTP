#include "Demo/HelloMyApp.h"
#include <iostream>
#include "Geometry/Drawable.h"
#include "Geometry/CubeMesh.h"
#include "Geometry/LineMesh.h"
#include "Geometry/SphereMesh.h"
#include "Geometry/Material.h"
#include "Geometry/Light.h"

HelloMyApp::HelloMyApp(int width, int height) : OpenGLDemo(width, height) {

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

    auto *front_light = new Light(lightiso1, glm::vec4(0.0f, 3.0f, 10.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
    auto *side_light = new Light(lightiso2, glm::vec4(10.0f, 1.0f, -2.0f, 1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
    auto *back_light = new Light(lightiso3, glm::vec4(-3.0f, -.5f, -10.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    m_renderer->add_Light(front_light);
    m_renderer->add_Light(side_light);
    m_renderer->add_Light(back_light);


    //unsigned int awsomeface = loadTexture("../Texture/awesomeface.png");
    unsigned int earth_texture = loadTexture("../Texture/earthmap1k.jpg");
    unsigned int earth_ocean_texture = loadTexture("../Texture/earthspec1k.jpg");
    unsigned int container_texture = loadTexture("../Texture/container2.png");
    unsigned int container_rough_texture = loadTexture("../Texture/container2_metal.png");
    unsigned int container_metal_texture = loadTexture("../Texture/container2_metal.png");
    unsigned int brick_color = loadTexture("../Texture/Bricks_Color.jpg");
    unsigned int brick_rough = loadTexture("../Texture/Bricks_Roughness.jpg");

    //Add AxisMesh
    m_renderer->add_Drawable(new AxisMesh());

    //Create and add CubeMesh
    auto *cubeMesh = new CubeMesh(glm::vec3(0.0), 1.0f);
    cubeMesh->translate(glm::vec3(0.0,2.0,0.0));
    cubeMesh->setColorTexture(container_texture);
    cubeMesh->setRoughnessTexture(container_rough_texture);
    cubeMesh->setMetallicTexture(container_metal_texture);
    m_renderer->add_Drawable(cubeMesh);

    //Create and add Sphere
    auto *sphere = new UVSphere(50, 50);
    sphere->translate(glm::vec3(-2.0f,0.0f,0.0f));
    sphere->setColorTexture(earth_texture);
    sphere->setRoughnessTexture(earth_ocean_texture);
    m_renderer->add_Drawable(sphere);

    auto *sphere2 = new UVSphere(50, 50);
    sphere2->translate(glm::vec3(2.0f,0.0f,0.0f));
    sphere2->setMaterial(rought);
    sphere2->setColorTexture(brick_color);
    sphere2->setRoughnessTexture(brick_rough);
    m_renderer->add_Drawable(sphere2);

    //Create and add Sphere
    auto *iso = new Icosahedron(5);
    iso->translate(glm::vec3(0.0f,-2.0f,0.0f));
    iso->setMaterial(cool);
    m_renderer->add_Drawable(iso);
}

HelloMyApp::~HelloMyApp() {
    delete m_renderer;
}

void HelloMyApp::resize(int width, int height) {
    OpenGLDemo::resize(width,height);
    m_renderer->resize(width, height);
}

void HelloMyApp::draw() {
    OpenGLDemo::draw();

    //std::cout << "drawcall" << std::endl;
    m_renderer->Draw();

}

void HelloMyApp::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    m_renderer->get_Camera()->processmouseclick(button, xpos, ypos);
}

void HelloMyApp::mousemove(float xpos, float ypos) {
    m_renderer->get_Camera()->processmousemovement(_button, xpos, ypos, true);
}

void HelloMyApp::mousewheel(float delta) {
    m_renderer->get_Camera()->processmousescroll(delta);
}

void HelloMyApp::keyboardmove(int k, double time) {
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

bool HelloMyApp::keyboard(unsigned char k) {
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

