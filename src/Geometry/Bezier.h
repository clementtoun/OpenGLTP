//
// Created by clement on 05/03/2022.
//

#ifndef OPENGLTP_BEZIER_H
#define OPENGLTP_BEZIER_H

#endif //OPENGLTP_BEZIER_H

#include <glm.hpp>
#include <vector>

void BezierSurface(int w, int h, const std::vector<std::vector<glm::vec3>> &c_point_grid, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);
void BezierCurve_SegCount(int nb_segment, const std::vector<glm::vec3> &c_point, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);
void BezierCurve_SegLenght(float segmentLenght, const std::vector<glm::vec3> &c_point, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);