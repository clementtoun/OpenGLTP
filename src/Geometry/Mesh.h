//
// Created by clement on 04/03/2022.
//

#ifndef UNTILTED1_MESH_H
#define UNTILTED1_MESH_H

#include <vector>
#include "opengl_stuff.h"
#include "Shader.h"
#include "Drawable.h"

struct Vertex {
    glm::vec3 vertices;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh : public Drawable {

public:

    Mesh();
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    ~Mesh() override;

    void setupMesh();
    void Draw(Shader &shader) override;

    void addVertex(glm::vec3 vertices, glm::vec3 Normal, glm::vec2 TexCoords);
    void addTriangle(uint32_t a, uint32_t b, uint32_t c);
    void addQuad(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

    void computeNormal(int mode = 0);

    void setMaterial(Material m);
    void setColor(glm::vec3 color);
    void setColorTexture(unsigned int texture_id);
    void setRoughnessTexture(unsigned int texture_id);
    void setMetallicTexture(unsigned int texture_id);

    const std::vector<Vertex> &getVertices() const;
    const std::vector<unsigned int> &getIndices() const;

protected:

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    Material m_material = Default_material;

    GLuint m_VAO, m_VBO, m_EBO;

private:

    void clear();

};


#endif //UNTILTED1_MESH_H
