//
// Created by mrn on 19/06/20.
//

#include "Edge.h"
#include "Triangle.h"

Edge::Edge(Vertex *source, Vertex *target) {
 this->source = source;
 this->target = target;

 source->adjacentEdges.push_back(this);
 target->adjacentEdges.push_back(this);

 this->source->state = VERTEXSTATE_FRONT;
 this->target->state = VERTEXSTATE_FRONT;
 this->state = EDGESTATE_FRONT;
}

vec3 Edge::getMidpoint() {
    return (this->target->pos + this->source->pos) / 2.0f;
}

Vertex *Edge::getOppositeVertex() {
    for(Vertex* v : adjacentTriangle1->points) {
        if(v != this->source && v != this->target) {
            return v;
        }
    }
}

bool Edge::addAdjacentTriangle(Triangle *t) {
    if(adjacentTriangle1 == t || adjacentTriangle2 == t) {
        return false;
    }

    if(adjacentTriangle1 == nullptr) {
        adjacentTriangle1 = t;
        this->state = EDGESTATE_FRONT;
        return true;
    }

    if(adjacentTriangle2 == nullptr) {
        adjacentTriangle2 = t;
        this->state = EDGESTATE_INNER;
        return true;
    }

    return false;
}

Triangle *Edge::getTriangle1() {
    return adjacentTriangle1;
}

Triangle *Edge::getTriangle2() {
    return adjacentTriangle2;
}
