//
// Created by Marian Cichy
//

#include "FpsCamera.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace glm;

namespace mrn {

    mrn::FpsCamera::FpsCamera(vec3 position, vec3 front) {
        this->position = position;
        this->front = front;
        this->fov = 100;
        this->speed = 1;
        this->update();
    }

    mrn::FpsCamera::~FpsCamera() = default;


    void FpsCamera::calcProjectionMat() {

    }

    void FpsCamera::update() {
        // create camera-right from camera-front and world-up
        this->right = normalize(cross(this->front, this->worldUp));
        // create camera-up from camera-right and camera-front
        this->up = normalize(cross(this->right, this->front));

        // TODO: better Pre-Calculate the projection matrix because it doesn't change all the time (only when we change fov and ScreenSize)
        projection = perspective(radians(this->fov), 800.0f / 600.0f, 0.1f, 100.0f);
    }

    mat4 FpsCamera::getViewMatrix() {
        return glm::lookAt(position, vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    }

    void FpsCamera::processKeyboard(CAMERA_COMMAND cmd, float deltaTime) {
        float velocity = speed * deltaTime;
        switch (cmd) {
            case CAM_FORWARD:
                this->position.y -= velocity;
                break;
            case CAM_BACKWARD:
                this->position.y += velocity;
                break;
            case CAM_LEFT:
                this->position.x -= velocity;
                break;
            case CAM_RIGHT:
                this->position.x += velocity;
                break;
        }
    }
}