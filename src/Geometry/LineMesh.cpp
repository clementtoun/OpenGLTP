//
// Created by clement on 05/03/2022.
//

#include "LineMesh.h"

LineMesh::LineMesh() {
    m_material.s_color = DEFAULT_COLOR;
    m_type = LINE_MESH;
}

LineMesh::LineMesh(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices) : m_vertices(vertices), m_indices(indices) {
    m_material.s_color = DEFAULT_COLOR;
    m_type = LINE_MESH;
    setupLineMesh();
}

LineMesh::~LineMesh() {
    clear();
}

void LineMesh::setupLineMesh() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
}

void LineMesh::Draw(Shader &shader) {
    for(int i = 0; i < (int)m_model.size(); i++) {
        shader.use();
        shader.setMat4("model", m_model[i]);
        shader.setVec3("color",m_material.s_color);

        glBindVertexArray(m_VAO);
        glDrawElements(GL_LINES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void LineMesh::clear() {
    m_vertices.clear();
    m_indices.clear();
}

void LineMesh::addVertex(glm::vec3 vertex) {
    m_vertices.emplace_back(vertex);
}

void LineMesh::addLine(uint32_t a, uint32_t b) {
    m_indices.emplace_back(a);
    m_indices.emplace_back(b);
}

AxisMesh::AxisMesh() {
    m_vertices = std::vector<glm::vec3>(0);
    m_indices = std::vector<unsigned int>(0);
    m_type = LINE_MESH;

    addVertex(glm::vec3(0.0, 0.0, 0.0));
    addVertex(glm::vec3(1.0, 0.0, 0.0));
    addLine(0,1);
    setupLineMesh();

}

void AxisMesh::Draw(Shader &shader) {
    auto m = glm::mat4(1.0f);
    shader.use();
    shader.setMat4("model", m);
    shader.setVec3("color",glm::vec3(1.0, 0.0, 0.0));
    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m = glm::rotate(m,glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    shader.use();
    shader.setMat4("model", m);
    shader.setVec3("color",glm::vec3(0.0, 1.0, 0.0));
    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);


    m = glm::rotate(m,glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
    shader.use();
    shader.setMat4("model", m);
    shader.setVec3("color",glm::vec3(0.0, 0.0, 1.0));
    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

