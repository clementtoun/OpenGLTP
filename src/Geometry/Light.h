//
// Created by clement on 07/03/2022.
//

#ifndef OPENGLTP_LIGHT_H
#define OPENGLTP_LIGHT_H

#include "vec3.hpp"
#include "Mesh.h"

class Light : public Drawable {

public:
    Light(glm::vec4 position);
    const glm::vec4 &getPosition() const;

    void Draw(Shader &shader) override;


private:
    glm::vec4 m_position;

};


#endif //OPENGLTP_LIGHT_H
