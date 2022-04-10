#include "Demo/HelloBezierSurface.h"
#include <iostream>
#include "Geometry/Drawable.h"
#include "Geometry/CubeMesh.h"
#include "Geometry/BezierSurfaceMesh.h"
#include "Geometry/Material.h"
#include "Geometry/LineMesh.h"

HelloBezierSurface::HelloBezierSurface(int width, int height) : OpenGLDemo(width, height) {

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

    unsigned int metal_color = loadTexture("../Texture/22_BaseColor.jpeg");
    unsigned int metal_roughness = loadTexture("../Texture/22_Roughness.jpeg");
    unsigned int metal_metal = loadTexture("../Texture/22_Metallic.jpeg");

    //Create control-grid and add Bezier_Surface
    std::vector<std::vector<glm::vec3>> c_point_grid;
    c_point_grid.emplace_back(std::vector<glm::vec3>({glm::vec3(-1.0,0.0,-2.0),glm::vec3(0.0,1.0,-2.0),glm::vec3(1.0,0.0,-2.0)}));
    c_point_grid.emplace_back(std::vector<glm::vec3>({glm::vec3(-1.0,1.0,-1.0),glm::vec3(0.0,0.0,-1.0),glm::vec3(1.0,-2.0,-1.0)}));
    c_point_grid.emplace_back(std::vector<glm::vec3>({glm::vec3(-1.0,0.0,0.0),glm::vec3(0.0,-1.0,0.0),glm::vec3(1.0,0.0,0.0)}));
    c_point_grid.emplace_back(std::vector<glm::vec3>({glm::vec3(-1.0,-2.0,1.0),glm::vec3(0.0,0.0,1.0),glm::vec3(1.0,-1.0,1.0)}));
    auto *bezier_surface = new BezierSurfaceMesh(50, 50, c_point_grid);
    bezier_surface->setColorTexture(metal_color);
    bezier_surface->setRoughnessTexture(metal_roughness);
    bezier_surface->setMetallicTexture(metal_metal);
    m_renderer->add_Drawable(bezier_surface);

    auto *cubeMesh = new CubeMesh(glm::vec3(0.0), 1.0f);
    cubeMesh->setMaterial(rought);
    m_renderer->add_Drawable(cubeMesh);
    int i = 0;
    for(auto &line : c_point_grid){
        for(auto &point : line){
            glm::mat4 trans = glm::translate(glm::mat4(1.0f), point);
            trans = glm::scale(trans, glm::vec3(0.05));
            if(i==0){
                cubeMesh->setModel(trans);
            }
            else{
                cubeMesh->add_model(trans);
            }
            i++;
        }
    }
}

HelloBezierSurface::~HelloBezierSurface() {
    delete m_renderer;
}

void HelloBezierSurface::resize(int width, int height) {
    OpenGLDemo::resize(width,height);
    m_renderer->resize(width, height);
}

void HelloBezierSurface::draw() {
    OpenGLDemo::draw();

    //std::cout << "drawcall" << std::endl;
    m_renderer->Draw();

}

void HelloBezierSurface::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    m_renderer->get_Camera()->processmouseclick(button, xpos, ypos);
}

void HelloBezierSurface::mousemove(float xpos, float ypos) {
    m_renderer->get_Camera()->processmousemovement(_button, xpos, ypos, true);
}

void HelloBezierSurface::mousewheel(float delta) {
    m_renderer->get_Camera()->processmousescroll(delta);
}

void HelloBezierSurface::keyboardmove(int k, double time) {
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

bool HelloBezierSurface::keyboard(unsigned char k) {
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

