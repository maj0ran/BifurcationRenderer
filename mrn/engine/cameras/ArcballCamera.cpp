#include <cmath>

//
// Created by Marian Cichy
//

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



void mrn::ArcballCamera::onNotify(mrn::Event &e) {
    switch (e.getType()) {
        case KEY_W: {
            theta -= glm::radians(camSpeed * e.readData<double>());
            if (theta < 0.01) {
                theta = 0.01;
            }
            break;
            case KEY_S:
                theta += glm::radians(camSpeed * e.readData<double>());
            if (theta > glm::pi<float>() - 0.01f) {
                theta = glm::pi<float>() - 0.01f;
            }
            break;

            case KEY_A:
                phi += glm::radians(camSpeed * e.readData<double>());
            break;
            case KEY_D:
                phi -= glm::radians(camSpeed * e.readData<double>());
            break;
            case KEY_Z:
                distance -= zoomSpeed  * e.readData<double>();
            break;

            case KEY_X:
                distance += zoomSpeed  * e.readData<double>();
            break;

            default:
                break;
        }
    }
}
