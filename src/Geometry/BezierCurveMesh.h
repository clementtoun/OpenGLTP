//
// Created by clement on 05/03/2022.
//

#ifndef OPENGLTP_BEZIERCURVEMESH_H
#define OPENGLTP_BEZIERCURVEMESH_H
#include "LineMesh.h"
#include "Bezier.h"

class BezierCurveMesh : public LineMesh {
public:

    BezierCurveMesh(int nb_segment, const std::vector<glm::vec3> &c_point);
    BezierCurveMesh(float segment_size, float epsilon, const std::vector<glm::vec3> &c_point);

};

#endif //OPENGLTP_BEZIERCURVEMESH_H
