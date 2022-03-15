//
// Created by clement on 05/03/2022.
//

#include "BezierSurfaceMesh.h"

std::vector<glm::vec3> computeNormal(const std::vector<glm::vec3> &vertices, const std::vector<unsigned int> &indices){
    std::vector<glm::vec3> normals(vertices.size());
    std::vector<int> norm_count(vertices.size());
    std::fill(normals.begin(), normals.end(), glm::vec3(0.0f,0.0f,0.0f));
    std::fill(norm_count.begin(), norm_count.end(), 0);

    for(int i = 0; i < (int)indices.size(); i+=3){
        glm::vec3 a = vertices[indices[i+1]] - vertices[indices[i]];
        glm::vec3 b = vertices[indices[i+2]] - vertices[indices[i]];
        glm::vec3 n = glm::cross(b, a);
        normals[indices[i]] += n;
        norm_count[indices[i]]++;
        normals[indices[i+1]] += n;
        norm_count[indices[i+1]]++;
        normals[indices[i+2]] += n;
        norm_count[indices[i+2]]++;
    }

    for(int i = 0; i < (int)normals.size(); i++) {
        normals[i] = glm::normalize(normals[i] / (float)norm_count[i]);
    }

    return normals;
}

BezierSurfaceMesh::BezierSurfaceMesh(const int w, const int h, const std::vector<std::vector<glm::vec3>> &c_point_grid) {
    m_vertices = std::vector<Vertex>(0);
    m_indices = std::vector<unsigned int>(0);
    m_textures = std::vector<Texture>(0);
    m_material.s_color = DEFAULT_COLOR;
    m_type = TRIANGLE_MESH;

    std::vector<glm::vec3> vertices;
    BezierSurface(w, h, c_point_grid, vertices, m_indices);

    std::vector<glm::vec3> normals = computeNormal(vertices, m_indices);

    Vertex vert{};
    for(int i = 0; i < (int)vertices.size(); i++) {
        vert.vertices = vertices[i];
        vert.Normal = normals[i];
        vert.TexCoords = glm::vec2(0.0);
        m_vertices.push_back(vert);
    }

    setupMesh();

}
