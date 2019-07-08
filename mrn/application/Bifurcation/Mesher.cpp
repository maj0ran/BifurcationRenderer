//
// Created by mrn on 19/06/20.
//

#include <gtc/constants.hpp>
#include <ext.hpp>
#include <algorithm>
#include "Mesher.h"
#include "Edge.h"
#include "Triangle.h"
#include "glm.hpp"
#include "Circumsphere.h"
#include "Mesh.h"

#define EPSILON 1e-3
#define square(a) pow(a, 2)
#define BALL_RADIUS this->current_ball_radius

Mesher::Mesher(vector<Vertex> pointCloud) : pball(Circumsphere(vec3(0, 0, 0), 0.0)) {
    sortbyDistance(pointCloud);
    float r = 0.03;
    while(r < 5.0) {
        ball_radii.push_back(r);
        r = r + 0.03;
    }
}

Mesh *Mesher::reconstruct() {
    Mesh *mesh;
    int n = 0;
    Triangle *seed;

    for(float radius : ball_radii) {
        current_ball_radius = radius;
        for(int i = 0; i < borderEdges.size(); i++) {
            Edge* e = borderEdges[i];
            Triangle* t = e->getTriangle1();

            if(testEmptyBall(t->points[0], t->points[1], t->points[2], t->ballCenter, radius)) {
                e->state = EDGESTATE_FRONT;
                this->expansionFront.addEdge(e);
                this->borderEdges.erase(borderEdges.begin() + i);
            }
        }
        while ((seed = findSeedTriangle()) != nullptr) {
            expand(seed);
            n++;
            printf("iteration: %d using radius %f\n", n, current_ball_radius);
        }
    }
    fillHoles();
}

Triangle *Mesher::findSeedTriangle() {

    for (int s = 0; s < sortedPoints.size(); s++) {
        Vertex *v0 = &sortedPoints[s];
        if(v0->state != VERTEXSTATE_ORPHAN) {
            continue;
        }
        auto neighbors = getNeighbors(v0->pos, 2 * BALL_RADIUS);
        for (int i = 0; i < neighbors.size(); i++) {
            Vertex *v1 = neighbors[i];
            if(v1->state != VERTEXSTATE_ORPHAN || v0 == v1) {
                continue;
            }
            for (int j = 0; j < neighbors.size(); j++) {
                Vertex *v2 = neighbors[j];
                if(v2->state != VERTEXSTATE_ORPHAN || v0 == v2 || v1 == v2) {
                    continue;
                }

                auto result = calcBall(v0, v1, v2, BALL_RADIUS);
                if (result.first) {
                    bool found = testEmptyBall(v0, v1, v2, result.second, BALL_RADIUS);
                    if (found) {
                        Triangle *t = new Triangle(v0, v1, v2, result.second);
                        t->ballCenter = result.second;
                        reconstructedSurface->addTriangle(t);
                        Edge *e1 = t->getEdge(0);
                        Edge *e2 = t->getEdge(1);
                        Edge *e3 = t->getEdge(2);

                        expansionFront.addEdge(e1);
                        expansionFront.addEdge(e2);
                        expansionFront.addEdge(e3);
                        return t;
                    }
                }
            }
        }
    }
    return nullptr;
}


int Mesher::nearestPoint(Vertex *src, vector<Vertex> points) {
    double smallestDistance = numeric_limits<double>::infinity();
    int nearest;
    for (int i = 0; i < points.size(); i++) {
        double d = glm::distance(src->pos, points[i].pos);
        if (d < smallestDistance) {
            nearest = i;
            smallestDistance = d;
        }
    }
    return nearest;
}


void Mesher::expand(Triangle *seedTriangle) {
    vec3 center = seedTriangle->ballCenter;


    while (!expansionFront.isEmpty()) {
        Edge *e = expansionFront.popEdge();
        if (e->state != EDGESTATE_FRONT) { // consider only front-edges
            continue;
        }
        Vertex *v = findCandidate(e, BALL_RADIUS,
                                  center); // find a suitable vertex to form a triangle with the front-edge

        if (v == nullptr || v->state == VERTEXSTATE_INNER) { // if no candidate or only inner candidates are found, skip
            e->state = EDGESTATE_BOUNDARY;
            borderEdges.push_back(e);
            continue;
        }

        Edge *es = v->getLinkingEdge(e->source);
        Edge *et = v->getLinkingEdge(e->target);


        if ((es != nullptr && es->state != EDGESTATE_FRONT) ||
            (et != nullptr && et->state != EDGESTATE_FRONT)) {
            e->state = EDGESTATE_BOUNDARY;
            borderEdges.push_back(e);
            continue;
        }
        if (e->getTriangle2() != nullptr) {
            continue;
        }
        Triangle *t = new Triangle(e, v);
        t->ballCenter = center;
        //    debugger.addPoint(center, RED);
        reconstructedSurface->addTriangle(t);

        es = v->getLinkingEdge(e->source);
        et = v->getLinkingEdge(e->target);


        if (es->state == EDGESTATE_FRONT) {
            expansionFront.addEdge(es);
        } else {
        }

        if (et->state == EDGESTATE_FRONT) {
            expansionFront.addEdge(et);
        } else {

        }
    }
}


Vertex *Mesher::findCandidate(Edge *e, float radius, vec3 &center) {
    Triangle *t = e->getTriangle1();
    vec3 ball_old = t->ballCenter;
    //  std::pair<bool, vec3> ball_old = calcBall(t->points[0], t->points[1], t->points[2], radius);
//    debugger.addPoint(ball_old, LIGHTBLUE);
    Vertex *candidate = nullptr;
    vec3 m = e->getMidpoint();
    //  debugger.addPoint(m, LIGHTBLUE);
    //  printf("ball_old: %f %f %f\n", ball_old.x, ball_old.y, ball_old.z);

    //
    // Vertex* opp = e->getOppositeVertex();

    //  float rot_radius = length(m - ball_old.second) + radius;
    float rot_radius = radius * 2;
    float min_angle = 2 * pi<float>();
    //   printf("rot radius: %f\n", rot_radius);
    vector<Vertex *> neighbors = getNeighbors(m, rot_radius);
    for (Vertex *v : neighbors) {
        if (v->state == VERTEXSTATE_INNER || v == e->source || v == e->target ||
            v == e->getOppositeVertex()) { // if v is INNER or belongs to e
            continue;
        }


        // TODO: if v is not compatible --> continue
        //  std::pair<bool, vec3> ball_new = calcBall(e->target, e->source, v, radius);
        auto ball_new = calcBall(e->target, e->source, v, BALL_RADIUS);
        if (!ball_new.first) {
            //          printf("strange ball check\n");
            continue;
        }
        bool isEmpty = testEmptyBall(e->target, e->source, v, ball_new.second, radius);
        float angle = glm::angle(ball_old - m, ball_new.second - m);
        //   printf("angle: %f\n", angle);

        if (angle > min_angle) {
            continue;
        }

        if (!isEmpty) {
            continue;
        }
        candidate = v;
        min_angle = angle;
        center = ball_new.second;
        //      debugger.addPoint(ball_new.second, PINK);

    }
    return candidate;
}

std::pair<bool, vec3> Mesher::calcCircumcenter(Vertex *a, Vertex *b, Vertex *c) {
    vec3 ac = c->pos - a->pos;
    vec3 ab = b->pos - a->pos;
    vec3 abXac = cross(ab, ac);

    if (length(abXac) < 1e-1)
        return {false, vec3()};
    //         |c-a|^2 [(b-a)x(c-a)]x(b-a) + |b-a|^2 (c-a)x[(b-a)x(c-a)]
    //  m = a + ---------------------------------------------------------.
    //                           2 | (b-a)x(c-a) |^2

    // this is the vector from point "a" TO the circumsphere center
    vec3 toCircumsphereCenter = (cross(abXac, ab) * (square(length(ac))) + cross(ac, abXac) * square(length(ab)))
                                / (2.0f * square(length(abXac)));

    // the actual coordinates of the circumcenter;
    vec3 circumcenter = a->pos + toCircumsphereCenter;
    //  debugger.addPoint(circumcenter, GREEN);
    //  debugger.addPoint(a->pos, BLUE);
    //   debugger.addPoint(b->pos, BLUE);
    //   debugger.addPoint(c->pos, BLUE);
    printf("circumcenter: %f %f %f\n", circumcenter.x, circumcenter.y, circumcenter.z);
    return {true, circumcenter};

}

/**
 * gets all vertices within a given radius of a given point
 * @param c the center of the radius
 * @param radius
 * @return vector of Vertices within the sphere
 */
vector<Vertex *> Mesher::getNeighbors(vec3 c, float radius) {
    vector<Vertex *> neighbors;
    for (auto &n : sortedPoints) {
        bool inserted = false;
        float distance = length(c - n.pos);
        if (distance < radius) { // insert if within radius
            int i = 0;
            while (i < neighbors.size() && length(neighbors[i]->pos - c) < length(n.pos - c)) {
                i++;
            }
            neighbors.insert(neighbors.begin() + i, &n);
        }
    }
    return neighbors;
}

std::pair<bool, vec3> Mesher::calcBall(Vertex *a, Vertex *b, Vertex *c, float ballradius) {
    //  printf("in calcball: %f %f %f\n", a->pos, b->pos, c->pos);
    auto circumcenter = calcCircumcenter(a, b, c);
    if (!circumcenter.first) return {false, vec3()};
    float circumradius = length(circumcenter.second - a->pos);
    float height = square(ballradius) - square(circumradius);
    if (height >= 0.0) {
        vec3 normal = calcNormal(a, b, c);
        vec3 origin = circumcenter.second + (sqrt(abs(height)) * normal);
        return {true, origin};
    }
    return {false, glm::vec3()};
}

bool Mesher::testEmptyBall(Vertex *A, Vertex *B, Vertex *C, vec3 ballCenter, float radius) {
    for (Vertex &p : sortedPoints) {
        if (&p == A || &p == B || &p == C) { continue; }
        if (square(length(p.pos - ballCenter)) < square(radius)) {
            return false;
        }
    }
    return true;
}

vec3 Mesher::calcNormal(Vertex *a, Vertex *b, Vertex *c) {
    vec3 normal = normalize(cross(b->pos - a->pos, c->pos - a->pos));
    vec3 vertexNormals = a->normal + b->normal + c->normal;
    normalize(vertexNormals);
    if (glm::dot(normal, vertexNormals) < 0.0) {
        normal = -normal;
    }
    return normal;
}

void Mesher::sortbyDistance(vector<Vertex> points) {
    for (auto p : points) {
        sortedPoints.push_back(p);
    }

    Vertex p = points[0];
    points.erase(points.begin());

//    for(int i = 0; i < points.size(); i++) {
    std::sort(sortedPoints.begin(), sortedPoints.end(),
              [p](const Vertex &p1, const Vertex &p2) { return length(p.pos - p1.pos) < length(p.pos - p2.pos); });
    //   int nearestIndex = nearestPoint(&sortedPoints[0], points);
    //   sortedPoints.push_back(points[nearestIndex]);
    //    points.erase(points.begin() + nearestIndex);
//    }

}

vector<Vertex> Mesher::getPoints() {
    return this->sortedPoints;
}


Debug Mesher::getDebugger() {
    return debugger;
}

// from http://www.ipol.im/pub/art/2014/81/article.pdf p. 155
// however, this seems not to be a good idea, because of the very small values, all the squared-terms will eventually be 0 in float arithmetic

vec3 Mesher::getCircumcenter(Vertex *A, Vertex *B, Vertex *C) {
    double a = length(C->pos - B->pos);
    double b = length(C->pos - A->pos);
    double c = length(B->pos - A->pos);

    printf("lengths: %f %f %f\n", a, b, c);
    double barycentric_a = square(a) * (square(b) + square(c) - square(a));
    double barycentric_b = square(b) * (square(a) + square(c) - square(b));
    double barycentric_c = square(c) * (square(a) + square(b) - square(c));

    printf("bary: %f %f %f\n", barycentric_a, barycentric_b, barycentric_c);

    double x = (barycentric_a * A->pos.x + barycentric_b * B->pos.x + barycentric_c * C->pos.x) /
               (barycentric_a + barycentric_b + barycentric_c);
    double y = (barycentric_a * A->pos.y + barycentric_b * B->pos.y + barycentric_c * C->pos.y) /
               (barycentric_a + barycentric_b + barycentric_c);
    double z = (barycentric_a * A->pos.z + barycentric_b * B->pos.z + barycentric_c * C->pos.z) /
               (barycentric_a + barycentric_b + barycentric_c);
    vec3 result(x, y, z);
    debugger.addPoint(A->pos, BLUE);
    debugger.addPoint(B->pos, BLUE);
    debugger.addPoint(C->pos, BLUE);
    debugger.addPoint(result, GREEN);
    return result;

    float sq_circumradius = square(a) * square(b) * square(c) / (a + b + c) * (b + c - a) * (c + a - b) * (a + b - c);

}

std::pair<bool, vec3> Mesher::circumcenter3(Vertex *A, Vertex *B, Vertex *C) {
    //compute the circumcenter barycentric coordinates
    double c = square(distance(B->pos, A->pos));
    double b = square(distance(A->pos, C->pos));
    double a = square(distance(C->pos, B->pos));
    double alpha = a * (b + c - a);
    double beta = b * (a + c - b);
    double gamma = c * (a + b - c);
    double temp = alpha + beta + gamma;

    if (temp < 1e-30)//aligned case
        return {false, vec3()};


    alpha = alpha / temp;
    beta = beta / temp;
    gamma = gamma / temp;


    //computing the triangle circumcircle center
    double x = alpha * A->pos.x + beta * B->pos.x + gamma * C->pos.x;
    double y = alpha * A->pos.y + beta * B->pos.y + gamma * C->pos.y;
    double z = alpha * A->pos.z + beta * B->pos.z + gamma * C->pos.z;

//    debugger.addPoint(vec3(x, y,z), GREEN);

    //computing the radius of the circumcircle
    double sq_circumradius = a * b * c;


    a = sqrt(a);
    b = sqrt(b);
    c = sqrt(c);

    sq_circumradius = sq_circumradius /
                      ((a + b + c) * (b + c - a) * (c + a - b) * (a + b - c));

    //compute the ortogonal distance from the hypothetic center to the triangle
    double height = square(BALL_RADIUS) - sq_circumradius;

    //compute the normal of the three points


    if (height >= 0.0) {
        vec3 normal = calcNormal(A, B, C);
        height = sqrt(height);
        vec3 center = vec3(vec3(x, y, z) + height * normal);
        return {true, center};
    }
    return {false, vec3()};
}

void Mesher::fillHoles() {

    auto it = borderEdges.begin();
    while(it != borderEdges.end()) {
        Edge* e = *it;
        if(e->state != EDGESTATE_BOUNDARY) {
            borderEdges.erase(it);
            continue;
        }
        Vertex *v = e->source->findBorder(e->target);
        if(v == nullptr) {
            it++;
            continue;
        }
        Triangle *t = new Triangle(e->source, e->target, v, vec3(0,0,0));
        reconstructedSurface->addTriangle(t);
        borderEdges.erase(it);

    }


}
