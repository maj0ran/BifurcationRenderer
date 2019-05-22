#include <cmath>

//
// Created by Marian Cichy
//

#include <ext/matrix_transform.hpp>
#include "ArcballCamera.h"

mrn::ArcballCamera::ArcballCamera(float phi, float theta, float distance, glm::vec3 target) {
    this->target = target;
    this->distance = distance;
    this->phi = phi;
    this->theta = theta;

    float camX = glm::sin(theta) * glm::cos(phi) * distance;
    float camY = glm::cos(theta) * distance;
    float camZ = glm::sin(theta) * glm::sin(phi) * distance;

    position = glm::vec3(camX, camY, camZ);

}

mrn::ArcballCamera::~ArcballCamera() {

}

glm::mat4 mrn::ArcballCamera::getViewMatrix() {
    return glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void mrn::ArcballCamera::update() {
    position.x = glm::sin(theta) * glm::cos(phi) * distance;
    position.y = glm::cos(theta) * distance;
    position.z = glm::sin(theta) * glm::sin(phi) * distance;
}
