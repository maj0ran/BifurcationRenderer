
#include "Circumsphere.h"

Circumsphere::Circumsphere(vec3 position, float radius) {
    this->center = position;
    this->radius = radius;
}

Circumsphere::~Circumsphere() = default;

vec3 Circumsphere::getPosition() {
    return this->center;
}

void Circumsphere::setPosition(vec3 pos) {
    this->center = pos;
}

float Circumsphere::getRadius() {
    return this->radius;
}

void Circumsphere::setRadius(float radius) {
    this->radius = radius;
}

