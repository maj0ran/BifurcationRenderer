//
// Created by mrn on 19/06/20.
//

#pragma once

#include "Vertex.h"

enum EdgeState {
    EDGESTATE_FRONT,
    EDGESTATE_BOUNDARY,
    EDGESTATE_INNER,
};
class Edge {
public:
    Vertex* source;
    Vertex* target;
    EdgeState state;
 //   vector<Triangle*> adjacentTriangles;
    bool addAdjacentTriangle(Triangle* t);
    Triangle* getTriangle1();
    Triangle* getTriangle2();
    Edge(Vertex* source, Vertex* target);
    ~Edge() = default;

    vec3 getMidpoint();
    Vertex* getOppositeVertex();

private:
    Triangle* adjacentTriangle1 = nullptr;
    Triangle* adjacentTriangle2 = nullptr;
};


