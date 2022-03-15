//
// Created by clement on 05/03/2022.
//

#include "BezierCurveMesh.h"

BezierCurveMesh::BezierCurveMesh(const int nb_segment, const std::vector<glm::vec3> &c_point) {
    m_vertices = std::vector<glm::vec3>(0);
    m_indices = std::vector<unsigned int>(0);
    m_material.s_color = DEFAULT_COLOR;
    m_type = LINE_MESH;

    BezierCurve_SegCount(nb_segment, c_point, m_vertices, m_indices);

    setupLineMesh();
}

BezierCurveMesh::BezierCurveMesh(float segment_size, const std::vector<glm::vec3> &c_point) {
    m_vertices = std::vector<glm::vec3>(0);
    m_indices = std::vector<unsigned int>(0);
    m_model.emplace_back(glm::mat4(1.0f));

    BezierCurve_SegLenght(segment_size, c_point, m_vertices, m_indices);


    setupLineMesh();
}

