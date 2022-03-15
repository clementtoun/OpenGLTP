//
// Created by clement on 05/03/2022.
//
#include <vector>

#ifndef OPENGLTP_DRAWABLE_H
#define OPENGLTP_DRAWABLE_H
#include "opengl_stuff.h"
#include "Shader.h"
#include "Material.h"

enum Mesh_type {
    TRIANGLE_MESH,
    LINE_MESH
};

class Drawable {

public:
    virtual void Draw(Shader &shader) = 0;
    virtual ~Drawable();
    void translate(glm::vec3 translation, int index = 0);
    void rotate(float angle, glm::vec3 rotation, int index = 0);
    void scale(glm::vec3 scale, int index = 0);
    void setModel(const glm::mat4 &model, int index = 0);
    void add_model(const glm::mat4 &model);
    void setColor(glm::vec3 color);
    Mesh_type getType() const;


protected:
    std::vector<glm::mat4> m_model{glm::mat4(1.0f)};
    Material m_material{DEFAULT_COLOR};
    Mesh_type m_type;

};


#endif //OPENGLTP_DRAWABLE_H
