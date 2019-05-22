//
// Created by Marian Cichy
//

#include <gtc/matrix_transform.hpp>
#include "Camera.h"

float mrn::Camera::getFov() const {
    return fov;
}

void mrn::Camera::setFov(float fov) {
    this->fov = fov;
}

const vec3 &mrn::Camera::getPosition() const {
    return position;
}

void mrn::Camera::setPosition(const vec3 &position) {
    this->position = position;
}

void mrn::Camera::setWorldUp(const vec3 &worldUp) {
    this->worldUp = worldUp;
}

const vec3 &mrn::Camera::getTarget() const {
    return this->target;
}

void mrn::Camera::setTarget(const vec3 &target) {
    this->target = target;
}

const mat4 &mrn::Camera::getViewMatrix()  {
    this->viewMatrix = glm::lookAt(position, target, worldUp);
    return viewMatrix;
}

mrn::Camera::Camera() {

}

mrn::Camera::~Camera() {

}

//const int *const_var;
//int *const const_ptr;