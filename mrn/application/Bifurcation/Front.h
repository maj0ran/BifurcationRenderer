//
// Created by mrn on 19/06/20.
//

#pragma once

#include <list>
#include "Edge.h"

using namespace std;
class Front {
public:
    Front() = default;
    ~Front() = default;

    void addEdge(Edge* e);
    Edge* popEdge();
    bool isEmpty();
    list<Edge*> edges;
private:
};


