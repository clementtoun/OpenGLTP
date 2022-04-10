//
// Created by clement on 05/03/2022.
//

#ifndef OPENGLTP_LINEMESH_H
#define OPENGLTP_LINEMESH_H

#include <vector>
#include "opengl_stuff.h"
#include "Shader.h"
#include "Drawable.h"
#include "Mesh.h"

class LineMesh : public Drawable {
public:

    LineMesh();
    explicit LineMesh(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);
    ~LineMesh() override;

    void setupLineMesh();
    void Draw(Shader &shader) override;

    void addVertex(glm::vec3 vertex);
    void addLine(uint32_t a, uint32_t b);


protected:
    std::vector<glm::vec3> m_vertices;
    std::vector<unsigned int> m_indices;
    GLuint m_VAO;
    glm::vec3 m_color;
    
private:

    void clear();
    GLuint m_VBO, m_EBO;
};

class AxisMesh : public LineMesh {

public:
    AxisMesh();
    void Draw(Shader &shader) override;
};


#endif //OPENGLTP_LINEMESH_H
