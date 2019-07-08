//
// Created by mrn on 19/06/20.
//

#pragma once

using namespace std;

#include <vector>
#include "Vertex.h"

/**
 * Store the vertices in the order so that the normal of the triangle has positive scalar
 * product with (v1 - v0) x (v2 - v0)
 */
class Triangle {
public:
    Triangle(Vertex* v0, Vertex* v1, Vertex* v2, vec3 ball_center);
    Triangle(Edge* e, Vertex* v);
 //   Triangle() = default;
    ~Triangle() = default;
    Edge* getEdge(unsigned int i);

    vector<Vertex*> points;
    vec3 normal;
    vec3 ballCenter;
    bool hasVertex(Vertex* v);

};


