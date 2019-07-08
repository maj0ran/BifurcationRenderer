//
// Created by mrn on 19/06/20.
//

#pragma once

#include "Vertex.h"
#include <vector>
#include <map>
#include "Triangle.h"
#include "Front.h"
#include "Circumsphere.h"
#include "../../Debug.h"
#include "Mesh.h"


using namespace std;

class Mesher {
public:
    Mesher(vector<Vertex> pointCloud);
    ~Mesher() = default;

    Triangle* findSeedTriangle();
    void expand(Triangle* seedTriangle);
    Mesh* reconstruct();

    vector<Vertex> getPoints();
    Debug getDebugger();
    Mesh* reconstructedSurface = new Mesh();
private:
    Circumsphere pball;
    std::vector<float> ball_radii = {  };
    float current_ball_radius;
    Front expansionFront;
    vector<Edge*> borderEdges;
    vector<Vertex> sortedPoints;
    Debug debugger;
    void fillHoles();


    std::pair<bool, vec3> calcCircumcenter(Vertex *a, Vertex *b, Vertex *c);
    vec3 getCircumcenter(Vertex* A, Vertex* B, Vertex* C);
    std::pair<bool, vec3> circumcenter3(Vertex* A, Vertex *B, Vertex *C);
    vec3 calcNormal(Vertex *a, Vertex *b, Vertex *c);
    std::pair<bool, vec3> calcBall(Vertex *a, Vertex *b, Vertex *c, float ballradius);

    vector<Vertex*> getNeighbors(vec3 c, float radius);
    bool testEmptyBall(Vertex* A, Vertex* B, Vertex* C, vec3 ballCenter, float radius);
    Vertex* findCandidate(Edge* e, float radius, vec3 &center);

    void sortbyDistance(vector<Vertex> points);
    int nearestPoint(Vertex *src, vector<Vertex> points);

};


