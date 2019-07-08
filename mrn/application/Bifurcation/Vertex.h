//
// Created by mrn on 19/06/19.
//

#pragma once

#include <glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

// Forward Delcarations are completely fine and you should not be ashamed of using them!
class Triangle;
class Edge;

enum VertexState {
    VERTEXSTATE_ORPHAN,
    VERTEXSTATE_FRONT,
    VERTEXSTATE_INNER
};
class Vertex {
public:
    Vertex() = default;
    ~Vertex() = default;

    vec3 pos;
    vec3 normal;
    VertexState state = VERTEXSTATE_ORPHAN;

    vector<Triangle*> adjacentTriangles;
    vector<Edge*> adjacentEdges;

    Edge* getLinkingEdge(Vertex* v);
    void updateType();
    Vertex* findBorder(Vertex* test);

};


