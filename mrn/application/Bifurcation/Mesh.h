//
// Created by mrn on 19/06/27.
//

#pragma once

#include <vector>
#include "Triangle.h"

class Mesh {
private:
    std::vector<Triangle> facets;

public:
    Mesh();
    ~Mesh();

    void addTriangle(Triangle* t);
    std::vector<Triangle> triangles();


};


