//
// Created by mrn on 19/06/20.
//

#pragma once

using namespace std;

#include <vector>
#include "Vertex.h"

class Triangle {
public:
    Triangle(Vertex p1, Vertex p2, Vertex p3);
    Triangle() = default;
    ~Triangle() = default;

    vector<Vertex> points;

};


