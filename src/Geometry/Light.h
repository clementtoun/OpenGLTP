//
// Created by clement on 07/03/2022.
//

#ifndef OPENGLTP_LIGHT_H
#define OPENGLTP_LIGHT_H

#include "Mesh.h"

class Light {

public:
    Light(Mesh *mesh, glm::vec4 vec, glm::vec3 color);
    ~Light();

    void Draw(Shader &shader);

    const glm::vec4 &getVec() const;
    void setVec(const glm::vec4 &mVec);
    const glm::vec3 &getColor() const;
    void setColor(const glm::vec3 &mColor);

private:

    glm::vec4 m_vec;
    glm::vec3 m_color;
    Mesh *m_mesh;
};


#endif //OPENGLTP_LIGHT_H
