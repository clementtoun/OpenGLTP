//
// Created by clement on 05/03/2022.
//

#ifndef OPENGLTP_BEZIERSURFACEMESH_H
#define OPENGLTP_BEZIERSURFACEMESH_H

#include "Mesh.h"
#include "Bezier.h"

class BezierSurfaceMesh : public Mesh {
public:
    explicit BezierSurfaceMesh(int w, int h, const std::vector<std::vector<glm::vec3>> &c_point_grid);
};

#endif //OPENGLTP_BEZIERSURFACEMESH_H