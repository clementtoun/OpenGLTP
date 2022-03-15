//
// Created by clement on 04/03/2022.
//

#include "Mesh.h"

Mesh::Mesh() {
    m_material.s_color = DEFAULT_COLOR;
    m_type = TRIANGLE_MESH;
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;
    m_material.s_color = DEFAULT_COLOR;
    m_type = TRIANGLE_MESH;
    setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
}

Mesh::~Mesh() {
    clear();
}

void Mesh::Draw(Shader &shader) {
    for(int i = 0; i < (int) m_model.size(); i++) {
        shader.use();
        shader.setMat4("model", m_model[i]);
        shader.setVec3("color", m_material.s_color);

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Mesh::addVertex(glm::vec3 vertices, glm::vec3 Normal, glm::vec2 TexCoords) {
    Vertex v;
    v.vertices = vertices;
    v.Normal = Normal;
    v.TexCoords = TexCoords;
    m_vertices.emplace_back(v);
}

void Mesh::addTriangle(uint32_t a, uint32_t b, uint32_t c) {
    m_indices.emplace_back(a);
    m_indices.emplace_back(b);
    m_indices.emplace_back(c);
}

void Mesh::addQuad(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    m_indices.emplace_back(a);
    m_indices.emplace_back(b);
    m_indices.emplace_back(c);
    m_indices.emplace_back(a);
    m_indices.emplace_back(c);
    m_indices.emplace_back(d);
}

void Mesh::clear()
{
    m_vertices.clear();
    m_indices.clear();
    m_textures.clear();
}

const std::vector<Vertex> &Mesh::getVertices() const {
    return m_vertices;
}

const std::vector<unsigned int> &Mesh::getIndices() const {
    return m_indices;
}
