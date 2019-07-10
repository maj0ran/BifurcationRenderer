//
// Created by mrn on 19/06/19.
//

#include "Vertex.h"
#include "Edge.h"
#include "../../engine/GLVertex.h"
#include "Triangle.h"


Edge *Vertex::getLinkingEdge(Vertex *v) {
    for(Edge* e : this->adjacentEdges) {
        for(Edge* et : v->adjacentEdges) {
            if( e == et) {
                return e;
            }
        }
    }
    return nullptr;
}

void Vertex::updateType() {
    if(this->adjacentEdges.empty()) {
        state = VERTEXSTATE_ORPHAN;
        return;
    }

    for(Edge *e : this->adjacentEdges) {
        if(e->state != EDGESTATE_INNER) {
            state = VERTEXSTATE_FRONT;
            return;
        }
    }
    state = VERTEXSTATE_INNER;

}

Vertex *Vertex::findBorder(Vertex *test) {
    Edge* e0 = getLinkingEdge(test);
    Triangle* t = e0->getTriangle1();

    for(Edge* e : this->adjacentEdges) {
        if(e->state != EDGESTATE_BOUNDARY) {
            continue;
        }

        Vertex *v = e->source;

        if(v == this) {
            continue;
        }

        if(t->hasVertex(v)) {
            continue;
        }
        Edge *e2 = v->getLinkingEdge(test);
        if(e2 == nullptr) {
            continue;
        }
        if((e2->state != EDGESTATE_BOUNDARY) || e2->source != test) {
            continue;
        }
        return v;
    }
    return nullptr;
}


