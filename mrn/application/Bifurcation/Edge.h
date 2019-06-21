//
// Created by mrn on 19/06/20.
//

#pragma once

#include "Vertex.h"


enum EdgeState {
    ACTIVE,
    BOUNDARY,
    FROZEN,
};
class Edge {
public:
    Edge(Vertex* v1, Vertex* v2);
    ~Edge() = default;

    Vertex* v1;
    Vertex* v2;
    EdgeState state;
    Edge* prev;
    Edge* next;
};


