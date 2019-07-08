//
// Created by mrn on 19/06/13.
//

#pragma once

#include <vector>
#include "../../engine/Mesh.h"
#include "Vertex.h"

using namespace std;



struct Pball {
    vec3 pos;
    double r;
};


class Bifurcation{
public:
    Bifurcation();
    ~Bifurcation();
    vector<Vertex> bifurcationData;
    void read(vector<const char*>& filenames);
    void estimateNormal(int point);
    void estimateNormals();
    vector<int> getNeighbors(int center, double r);
    Vertex getPointByIndex(int index);
    void correctNormalDirection();
    void scale(float factor);

private:
public:
    Vertex getCentroid(vector<Vertex>*);
};


