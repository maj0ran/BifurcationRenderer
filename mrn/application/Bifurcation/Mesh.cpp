//
// Created by mrn on 19/06/27.
//

#include "Mesh.h"

Mesh::Mesh() {

}

Mesh::~Mesh() {

}

void Mesh::addTriangle(Triangle *t) {
    this->facets.push_back(*t);
}

std::vector<Triangle> Mesh::triangles() {
    return this->facets;
}
