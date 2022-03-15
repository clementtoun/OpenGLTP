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

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;  // we store the path of the texture to compare with other textures
};

class Mesh : public Drawable {

public:

    Mesh();
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
    ~Mesh() override;

    void setupMesh();
    void Draw(Shader &shader) override;

    void addVertex(glm::vec3 vertices, glm::vec3 Normal, glm::vec2 TexCoords);
    void addTriangle(uint32_t a, uint32_t b, uint32_t c);
    void addQuad(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

    const std::vector<Vertex> &getVertices() const;
    const std::vector<unsigned int> &getIndices() const;

protected:

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;

private:

    void clear();
    GLuint m_VAO, m_VBO, m_EBO;

};


#endif //UNTILTED1_MESH_H
