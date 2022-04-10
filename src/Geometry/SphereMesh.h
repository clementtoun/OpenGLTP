//
// Created by clement on 27/03/2022.
//

#ifndef OPENGLTP_SPHEREMESH_H
#define OPENGLTP_SPHEREMESH_H
#include "Mesh.h"

class UVSphere : public Mesh {
public:
    UVSphere(uint32_t meridians, uint32_t parallels);
};

class Icosahedron : public Mesh {
public:
    explicit Icosahedron(unsigned int n_subdiv);
private:
    void SubdivideMesh();
};


#endif //OPENGLTP_SPHEREMESH_H
