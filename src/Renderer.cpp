//
// Created by clement on 04/03/2022.
//

#include "Renderer.h"

Renderer::Renderer(Shader &shader, Shader &lineShader, int width, int height) : m_active_camera(0) {

    m_shader = shader;
    m_lineShader = lineShader;
    m_width = width;
    m_height = height;

    m_cameraconstructors.emplace_back([](glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat fov, GLfloat aspect)->EulerCamera*{
        std::cout << "EulerCamera loaded" << std::endl; return new EulerCamera(position, up, yaw, pitch, fov, aspect);
    });

    m_cameraconstructors.emplace_back([](glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat fov, GLfloat aspect)->TrackballCamera*{
        std::cout << "TrackballCamera loaded" << std::endl; return new TrackballCamera(position, up, yaw, pitch, fov, aspect);
    });

    m_camera.reset(m_cameraconstructors[0](glm::vec3(0.0f,0.0f,10.0f), glm::vec3(0.0,1.0,0.0), -90.0, 0, 45.0, (m_width/(float)m_height)));

}

Renderer::~Renderer() {
    for(auto d : m_drawables)
        delete d;
    m_shader.deleteProg();
}

void Renderer::Draw() {
    for(Drawable *drawable : m_drawables){
        if (drawable->getType() == TRIANGLE_MESH){
            m_shader.use();
            m_shader.setMat4("projection", m_camera->projectionmatrix());
            m_shader.setMat4("view", m_camera->viewmatrix());
            m_shader.setVec4("lightVector", m_lightVector);
            m_shader.setBool("normalmode", m_normal_mode);

            drawable->Draw(m_shader);
        }
        if (drawable->getType() == LINE_MESH){
            m_lineShader.use();
            m_lineShader.setMat4("projection", m_camera->projectionmatrix());
            m_lineShader.setMat4("view", m_camera->viewmatrix());
            drawable->Draw(m_lineShader);
        }
    }
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    m_camera->setAspect((GLfloat) ((float) width / height));
}

void Renderer::add_Drawable(Drawable *drawable) {
    m_drawables.push_back(drawable);
}

void Renderer::change_Camera(){
    unsigned int cam_size = m_cameraconstructors.size();
    if(m_active_camera < cam_size){
        m_active_camera = (m_active_camera+1)%cam_size;
        m_camera.reset(m_cameraconstructors[m_active_camera](glm::vec3(0.0,0.0f,10.0f), glm::vec3(0.0,1.0,0.0), -90.0, 0, 45, (m_width/(float)m_height)));
    }
}

Camera* Renderer::get_Camera() {
    return m_camera.get();
}

void Renderer::add_Light(glm::vec4 lightVector) {
    m_lightVector = lightVector;
}

void Renderer::toggleNormalmode() {
    m_normal_mode = !m_normal_mode;
}

