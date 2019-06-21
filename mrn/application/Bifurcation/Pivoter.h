//
// Created by mrn on 19/06/20.
//

#pragma once

#include "Vertex.h"
#include <vector>
#include <map>
#include "Triangle.h"
#include "Front.h"

struct CircumSphere {
    vec3 center;
    float radius;
};
using namespace std;

class Pivoter {
public:
    Pivoter() = default;
    ~Pivoter() = default;

    void pivot(vector<Vertex> points);
    Triangle findSeedTriangle(vector<Vertex> points);
    map<int, bool> notUsed;

    vector<Vertex> sortbyDistance(vector<Vertex> points);
    int nearestPoint(Vertex* src, vector<Vertex> points);

    CircumSphere circumcenter(Vertex* a, Vertex* b, Vertex* c);
    bool testEmptyBall(CircumSphere *sphere, vector<Vertex> *cloud);

    Front expansionFront;


};


