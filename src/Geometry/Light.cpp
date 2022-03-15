//
// Created by clement on 07/03/2022.
//

#include "Light.h"

Light::Light(glm::vec4 position) : m_position(position) {

}

const glm::vec4 &Light::getPosition() const {
    return m_position;
}

void Light::Draw(Shader &shader) {
    shader.use();
    shader.setMat4("model", m_model.front());
    shader.setVec3("color", m_material.s_color);
}
