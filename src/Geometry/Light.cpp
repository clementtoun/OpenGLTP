//
// Created by clement on 07/03/2022.
//

#include "Light.h"

Light::Light(Mesh *mesh, glm::vec4 vec, glm::vec3 color) : m_vec(vec), m_color(color), m_mesh(mesh) {
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, glm::vec3(m_vec));
    m = glm::scale(m, glm::vec3(0.1f));
    m_mesh->setModel(m);
}

Light::~Light() {
    delete m_mesh;
}

void Light::Draw(Shader &shader) {
    shader.use();
    shader.setVec3("color", m_color);
    m_mesh->Draw(shader);
}

const glm::vec4 &Light::getVec() const {
    return m_vec;
}

void Light::setVec(const glm::vec4 &mVec) {
    m_vec = mVec;
}

const glm::vec3 &Light::getColor() const {
    return m_color;
}

void Light::setColor(const glm::vec3 &mColor) {
    m_color = mColor;
}
