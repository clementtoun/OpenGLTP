//
// Created by clement on 04/03/2022.
//

#include "Renderer.h"

Renderer::Renderer(Shader &shader, Shader &lineShader, Shader &lightShader, int width, int height) : m_active_camera(0) {

    m_shader = shader;
    m_lineShader = lineShader;
    m_lightShader = lightShader;
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
    for(auto l : m_lights)
        delete l;
    m_shader.deleteProg();
    m_lineShader.deleteProg();
    m_lightShader.deleteProg();
    m_cameraconstructors.clear();
    m_camera.reset(nullptr);
}

void Renderer::Draw() {
    for(Drawable *drawable : m_drawables){
        if (drawable->getType() == TRIANGLE_MESH){
            m_shader.use();
            m_shader.setVec3("eyePos", m_camera->position());
            m_shader.setMat4("projection", m_camera->projectionmatrix());
            m_shader.setMat4("view", m_camera->viewmatrix());
            m_shader.setBool("normalmode", m_normal_mode);
            m_shader.setBool("Texcoordmode", m_Texcoord_mode);

            for(int i = 0; i < (int) m_lights.size(); i++){
                std::string str_i = std::to_string(i);
                m_shader.setVec4("lights["+str_i+"].vec", m_lights[i]->getVec());
                m_shader.setVec3("lights["+str_i+"].color", m_lights[i]->getColor());
            }

            drawable->Draw(m_shader);
        }
        if (drawable->getType() == LINE_MESH){
            m_lineShader.use();
            m_lineShader.setMat4("projection", m_camera->projectionmatrix());
            m_lineShader.setMat4("view", m_camera->viewmatrix());
            drawable->Draw(m_lineShader);
        }
        for(auto light : m_lights){
            m_lightShader.use();
            m_lightShader.setMat4("projection", m_camera->projectionmatrix());
            m_lightShader.setMat4("view", m_camera->viewmatrix());
            light->Draw(m_lightShader);
        }
    }
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    m_camera->setAspect((GLfloat) ((float) width / height));
}

void Renderer::add_Drawable(Drawable *drawable) {
    m_drawables.emplace_back(drawable);
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

void Renderer::add_Light(Light *light) {
    m_lights.emplace_back(light);
}

void Renderer::toggleNormalmode() {
    if(m_Texcoord_mode)
        m_Texcoord_mode = false;
    m_normal_mode = !m_normal_mode;
}

void Renderer::toggleTexcoordmode() {
    if(m_normal_mode)
        m_normal_mode = false;
    m_Texcoord_mode = !m_Texcoord_mode;
}

