//
// Created by clement on 04/03/2022.
//

#include "CubeMesh.h"

CubeMesh::CubeMesh(const glm::vec3 position, const float size) {
    m_material = Default_material;
    m_type = TRIANGLE_MESH;
    m_vertices = std::vector<Vertex>(0);
    m_indices = std::vector<unsigned int>(0);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,position);
    model = glm::scale(model, glm::vec3(size));
    setModel(model);

    glm::vec3 vertices[8] =
    {
        glm::vec3(-1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f, -1.f),
        glm::vec3(1.f, 1.f, -1.f),
        glm::vec3(-1.f, 1.f, -1.f),
        glm::vec3(-1.f, -1.f, 1.f),
        glm::vec3(1.f, -1.f, 1.f),
        glm::vec3(1.f, 1.f, 1.f),
        glm::vec3(-1.f, 1.f, 1.f)
    };

    glm::vec2 texCoords[4] =
    {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f)
    };

    int indices[6 * 4] =
    {
        1, 0, 3, 2,
        5, 1, 2, 6,
        4, 5, 6, 7,
        0, 4, 7, 3,
        7, 6, 2, 3,
        0, 1, 5, 4,
    };

    for (int i = 0; i < 24; i++) {
        m_vertices.emplace_back(Vertex{vertices[indices[i]], glm::vec3(0.0f,0.0f,0.0f), texCoords[i % 4]});
        if(i%4 == 0)
            addQuad(i,i+1,i+2,i+3);
    }

    computeNormal(1);
    setupMesh();
}


