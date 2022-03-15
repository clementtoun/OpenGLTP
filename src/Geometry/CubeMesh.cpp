//
// Created by clement on 04/03/2022.
//

#include "CubeMesh.h"

CubeMesh::CubeMesh(const glm::vec3 position, const float size) {
    m_material.s_color = DEFAULT_COLOR;
    m_type = TRIANGLE_MESH;
    m_vertices = std::vector<Vertex>(0);
    m_indices = std::vector<unsigned int>(0);
    m_textures = std::vector<Texture>(0);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,position);
    model = glm::scale(model, glm::vec3(size));
    setModel(model);
    
    addVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 0.0));
    addVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(-1.0, 0.0, 0.0), glm::vec2(1.0, 0.0));
    addVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.0, -1.0, 0.0), glm::vec2(0.0, 0.0));
    addVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 0.0));
    addVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec3(1.0, 0.0, 0.0), glm::vec2(0.0, 0.0));
    addVertex(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.0, -1.0, 0.0), glm::vec2(1.0, 0.0));
    addVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 1.0));
    addVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(1.0, 0.0, 0.0), glm::vec2(0.0, 1.0));
    addVertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 0.0));
    addVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 1.0));
    addVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 0.0));
    addVertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(-1.0, 0.0, 0.0), glm::vec2(1.0, 1.0));
    addVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.0, 0.0, -1.0), glm::vec2(0.0, 0.0));
    addVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-1.0, 0.0, 0.0), glm::vec2(0.0, 0.0));
    addVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.0, -1.0, 0.0), glm::vec2(0.0, 1.0));
    addVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.0, -1.0, 0.0), glm::vec2(1.0, 1.0));
    addVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(1.0, 0.0, 0.0), glm::vec2(1.0, 0.0));
    addVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0.0, 0.0, -1.0), glm::vec2(1.0, 0.0));
    addVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 1.0));
    addVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.0, 0.0, -1.0), glm::vec2(0.0, 1.0));
    addVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(-1.0, 0.0, 0.0), glm::vec2(0.0, 1.0));
    addVertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0));
    addVertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(1.0, 0.0, 0.0), glm::vec2(1.0, 1.0));
    addVertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.0, 0.0, -1.0), glm::vec2(1.0, 1.0));

    addQuad(0, 3, 6, 9); //Front
    addQuad(1, 13, 20, 11); //Left
    addQuad(2, 5, 15, 14); //Bot
    addQuad(4, 16, 22, 7); //Right
    addQuad(10, 8, 21, 18); //Top
    addQuad(12, 17, 23, 19); //Back

    setupMesh();
}


