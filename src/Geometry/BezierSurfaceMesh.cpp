//
// Created by clement on 05/03/2022.
//

#include "BezierSurfaceMesh.h"

BezierSurfaceMesh::BezierSurfaceMesh(const int w, const int h, const std::vector<std::vector<glm::vec3>> &c_point_grid) {
    m_vertices = std::vector<Vertex>(0);
    m_indices = std::vector<unsigned int>(0);
    m_material = Default_material;
    m_type = TRIANGLE_MESH;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> TexCoords;
    BezierSurface(w, h, c_point_grid, vertices, m_indices, TexCoords);

    Vertex vert{};
    for(int i = 0; i < (int)vertices.size(); i++) {
        vert.vertices = vertices[i];
        vert.Normal = glm::vec3(0.0f);
        vert.TexCoords = TexCoords[i];
        m_vertices.push_back(vert);
    }

    computeNormal(1);
    setupMesh();

}
