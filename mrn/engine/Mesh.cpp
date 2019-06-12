//
// Created by Marian Cichy
//

#include "Mesh.h"
namespace mrn {

    Mesh::Mesh() {

    }

    Mesh::~Mesh() {

    }

    void Mesh::addVertex(mrn::Vertex &vertex) {
        this->vertices.push_back(vertex);
    }


    void Mesh::addTriangleIndices(uint32 p1, uint32 p2, uint32 p3) {
        this->indices.push_back(p1);
        this->indices.push_back(p2);
        this->indices.push_back(p3);
    }
}