//
// Created by mrn on 19/06/20.
//

#include "Pivoter.h"
#include "Edge.h"
#include "Triangle.h"
#include "glm.hpp"

#define EPSILON 0.0000001 // used in testEmptyBall() to exclude the points on the surface of the ball because of rounding errors

void Pivoter::pivot(vector<Vertex> points) {

}

Triangle Pivoter::findSeedTriangle(vector<Vertex> points) {
    auto sortedPoints = sortbyDistance(points);
    Vertex p = sortedPoints[0];
    for(auto q : sortedPoints) {
        for(auto s : sortedPoints) {
            if(q.pos == s.pos || p.pos == q.pos || p.pos == s.pos) continue; // p != q != s
            CircumSphere ball = circumcenter(&p, &q, &s);
            bool found = testEmptyBall(&ball, &sortedPoints);
            if(found) {
                printf("BALL RADIUS: %f\n", ball.radius);
                return Triangle(p, q, s);
            }
        }
    }

    return Triangle();
}

vector<Vertex> Pivoter::sortbyDistance(vector<Vertex> points) {
    vector<Vertex> sortedPoints;
    sortedPoints.push_back(points[0]);
    points.erase(points.begin());

    for(int i = 0; i < points.size(); i++) {
        int nearestIndex = nearestPoint(&sortedPoints[0], points);
        printf("FOUND INDEX: %d\n", nearestIndex);
        sortedPoints.push_back(points[nearestIndex]);
        points.erase(points.begin() + nearestIndex);
    }

    return sortedPoints;

}

int Pivoter::nearestPoint(Vertex* src, vector<Vertex> points) {
    double smallestDistance = numeric_limits<double>::infinity();
    int nearest;
    for(int i = 0; i < points.size(); i++) {
 //       if(points[i].pos == src->pos) { // skip self-comparison
 //           continue;
 //       }
        double d = glm::distance(src->pos, points[i].pos);
        if(d < smallestDistance) {
            nearest = i;
            smallestDistance = d;
        }
    }
    return nearest;
}

CircumSphere Pivoter::circumcenter(Vertex* a, Vertex* b, Vertex* c) {
     vec3 ac = c->pos - a->pos;
     vec3 ab = b->pos - a->pos;
     vec3 abXac = cross(ab, ac);

     //         |c-a|^2 [(b-a)x(c-a)]x(b-a) + |b-a|^2 (c-a)x[(b-a)x(c-a)]
     //  m = a + ---------------------------------------------------------.
     //                           2 | (b-a)x(c-a) |^2

     // this is the vector from point "a" TO the circumsphere center
    vec3 toCircumsphereCenter = (cross(abXac, ab) * (length(ac) * length(ac)) + cross(ac, abXac) * (length(ab) * length(ab)))
            / (2.f * (length(abXac) * length(abXac)));

    // the actual coordinates of the circumcenter;
    vec3 circumcenter = a->pos + toCircumsphereCenter;
    // the radius of the circumsphere
    float radius = length(toCircumsphereCenter);

    return CircumSphere {circumcenter, radius};
}

bool Pivoter::testEmptyBall(CircumSphere *sphere, vector<Vertex> *cloud) {
    for(auto p : *cloud) {
        if( pow(p.pos.x - sphere->center.x, 2) +
            pow(p.pos.y - sphere->center.y, 2) +
            pow(p.pos.z - sphere->center.z, 2) < pow(sphere->radius, 2) - EPSILON) {
                return false;
        }
    }
    return true;
}
