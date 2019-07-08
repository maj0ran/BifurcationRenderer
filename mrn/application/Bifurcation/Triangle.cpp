//
// Created by mrn on 19/06/20.
//

#include "Triangle.h"
#include "Edge.h"

Triangle::Triangle(Vertex* v0, Vertex* v1, Vertex* v2, vec3 ball_center) {
    this->ballCenter = ball_center;
    points.push_back(v0);
    points.push_back(v1);
    points.push_back(v2);


    Edge* e1 = v0->getLinkingEdge(v1);
    if(e1 == nullptr) { e1 = new Edge(v0, v1); }
    e1->addAdjacentTriangle(this);

    Edge* e2 = v1->getLinkingEdge(v2);
    if(e2 == nullptr) { e2 = new Edge(v1, v2); }
    e2->addAdjacentTriangle(this);

    Edge* e3 = v2->getLinkingEdge(v0);
    if(e3 == nullptr) { e3 = new Edge(v2, v0); }
    e3->addAdjacentTriangle(this);

    v0->adjacentTriangles.push_back(this);
    v1->adjacentTriangles.push_back(this);
    v2->adjacentTriangles.push_back(this);

    v0->updateType();
    v1->updateType();
    v2->updateType();


    normal = cross(v1->pos - v0->pos, v2->pos - v0->pos);
}

Triangle::Triangle(Edge *e, Vertex *v) : Triangle(e->source, e->target, v, vec3(0,0,0)) { }

/**
 * gets the Edge that is opposite to the given point
 * @param i index of the point
 * @return opposite edge
 */
Edge *Triangle::getEdge(unsigned int i) {
    Vertex* v1 = points[(i+1) % 3];
    Vertex* v2 = points[(i+2) % 3];

    return v1->getLinkingEdge(v2);
}

bool Triangle::hasVertex(Vertex* v) {
    for(Vertex* q : points) {
        if(q == v) {
            return true;
        }
    }
    return false;
}
