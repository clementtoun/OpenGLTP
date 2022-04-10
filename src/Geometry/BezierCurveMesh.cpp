//
// Created by clement on 05/03/2022.
//

#include "BezierCurveMesh.h"

BezierCurveMesh::BezierCurveMesh(const int nb_segment, const std::vector<glm::vec3> &c_point) {
    m_vertices = std::vector<glm::vec3>(0);
    m_indices = std::vector<unsigned int>(0);
    m_color = DEFAULT_COLOR;
    m_type = LINE_MESH;

    BezierCurve_SegCount(nb_segment, c_point, m_vertices, m_indices);

    setupLineMesh();
}

BezierCurveMesh::BezierCurveMesh(const float segment_size, const float epsilon, const std::vector<glm::vec3> &c_point) {
    m_vertices = std::vector<glm::vec3>(0);
    m_indices = std::vector<unsigned int>(0);

    BezierCurve_SegLenght(segment_size, epsilon, c_point, m_vertices, m_indices);

    setupLineMesh();
}

