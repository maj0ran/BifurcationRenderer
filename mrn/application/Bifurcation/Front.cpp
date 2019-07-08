//
// Created by mrn on 19/06/20.
//

#include "Front.h"

void Front::addEdge(Edge* edge) {
    this->edges.push_front(edge);
}

Edge *Front::popEdge() {
    Edge* e = this->edges.front();
    this->edges.pop_front();
    return e;
}

bool Front::isEmpty() {
    return this->edges.empty();
}
