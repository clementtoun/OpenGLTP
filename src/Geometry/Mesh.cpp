//
// Created by clement on 04/03/2022.
//

#include "Mesh.h"

Mesh::Mesh() {
    m_material = Default_material;
    m_type = TRIANGLE_MESH;
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    m_vertices = vertices;
    m_indices = indices;
    m_material = Default_material;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));
}

Mesh::~Mesh() {
    clear();
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Active_Texture(int id, unsigned int texture_id){
    switch(id) {
        case 0:
            glActiveTexture(GL_TEXTURE0);
            break;
        case 1:
            glActiveTexture(GL_TEXTURE1);
            break;
        default:
            glActiveTexture(GL_TEXTURE2);
    }
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Mesh::Draw(Shader &shader) {
    shader.use();
    shader.setVec3("material.color", m_material.getColor());
    shader.setFloat("material.roughness", m_material.getRoughness());
    shader.setFloat("material.metallic", m_material.getMetallic());

    shader.setBool("material.has_color_texture", m_material.isHasColorTexture());
    shader.setInt("material.colorTexture", 0);
    if(m_material.isHasColorTexture()) {
        Active_Texture(0, m_material.getColorTexture());
    }
    shader.setBool("material.has_roughness_texture", m_material.isHasRoughnessTexture());
    shader.setInt("material.roughnessTexture", 1);
    if(m_material.isHasRoughnessTexture()) {
        Active_Texture(1, m_material.getRoughnessTexture());
    }
    shader.setBool("material.has_metallic_texture", m_material.isHasMetallicTexture());
    shader.setInt("material.metallicTexture", 2);
    if(m_material.isHasMetallicTexture()) {
        Active_Texture(2, m_material.getMetallicTexture());
    }

    for(auto & i : m_model) {
        shader.use();
        shader.setMat4("model", i);

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}

void Mesh::addVertex(glm::vec3 vertices, glm::vec3 Normal, glm::vec2 TexCoords) {
    Vertex v{};
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
}

const std::vector<Vertex> &Mesh::getVertices() const {
    return m_vertices;
}

const std::vector<unsigned int> &Mesh::getIndices() const {
    return m_indices;
}

void Mesh::computeNormal(int mode){
    glm::vec3 n;
    glm::vec3 a;
    glm::vec3 b;
    for(int i = 0; i < (int)m_indices.size(); i+=3){
        a = m_vertices[m_indices[i+1]].vertices - m_vertices[m_indices[i]].vertices;
        b = m_vertices[m_indices[i+2]].vertices - m_vertices[m_indices[i]].vertices;
        if(mode)
            n = glm::cross(a, b);
        else
            n = glm::cross(b, a);
        m_vertices[m_indices[i]].Normal =+ n;
        m_vertices[m_indices[i+1]].Normal =+ n;
        m_vertices[m_indices[i+2]].Normal =+ n;
    }

    for(auto & m_vertice : m_vertices) {
        m_vertice.Normal = glm::normalize(m_vertice.Normal);
        //std::cout << m_vertices[i].Normal.x << m_vertices[i].Normal.y << m_vertices[i].Normal.z << std::endl;
        //glm::vec3 n = glm::vec4(m_vertices[i].Normal*0.5f + 0.5f, 1.0f);
        //std::cout << "n " << n.x << " " << n.y << " " << n.z << std::endl;
    }
}

void Mesh::setMaterial(Material m){
    m_material = m;
}

void Mesh::setColor(glm::vec3 color){
    m_material.setColor(color);
}

void Mesh::setColorTexture(unsigned int texture_id) {
    m_material.setColorTexture(texture_id);
}

void Mesh::setRoughnessTexture(unsigned int texture_id) {
    m_material.setRoughnessTexture(texture_id);
}

void Mesh::setMetallicTexture(unsigned int texture_id) {
    m_material.setMetallicTexture(texture_id);
}
