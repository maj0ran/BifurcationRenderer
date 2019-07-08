#pragma once

#include "glm.hpp"

using namespace glm;

class Circumsphere {
public:
    Circumsphere(vec3 position, float radius);
    ~Circumsphere();

vec3 getPosition();
void setPosition(vec3 pos);

float getRadius();
void setRadius(float radius);

private:
    vec3 center;
    float radius;
};