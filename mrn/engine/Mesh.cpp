//
// Created by Marian Cichy
//

#include "Mesh.h"
namespace mrn {



    Mesh::Mesh() {

    }

    Mesh::~Mesh() {

    }

    void Mesh::addVertex(mrn::GLVertex &vertex) {
        this->vertices.push_back(vertex);
    }


    void Mesh::setPatchSize(int size) {
        patch_size = 3;
    }

    int Mesh::getPatchSize() {
        return patch_size;
    }

    void Mesh::addIndex(uint32_t i) {
        indices.push_back(i);
    }
}