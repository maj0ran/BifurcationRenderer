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
        this->fov = CAM_FOV;
        this->speed = CAM_SPEED;
        this->pitch = 0;
        this->yaw = 0;
        this->update();

        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    }

    mrn::FpsCamera::~FpsCamera() = default;


    void FpsCamera::calcProjectionMat() {

    }

    void FpsCamera::update() {
        if(pitch > 89.0) {
            pitch = 89.0;
        }

        if(pitch < -89.0) {
            pitch = -89.0;
        }

        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        front = normalize(front);
        // create camera-right from camera-front and world-up
        this->right = normalize(cross(this->front, this->worldUp));
        // create camera-up from camera-right and camera-front
        this->up = normalize(cross(this->right, this->front));

        // TODO: better Pre-Calculate the projection matrix because it doesn't change all the time (only when we change fov and ScreenSize)
        projection = perspective(radians(this->fov), 800.0f / 600.0f, 0.1f, 1000.0f);
    }

    mat4 FpsCamera::getViewMatrix() {
        return glm::lookAt(position, position - front, worldUp);
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

    void FpsCamera::onNotify(Event &e) {
        //   float veloctiy = speed *
        switch (e.getType()) {
            case KEY_W:
                this->position -= this->front * (float)(this->speed * e.readData<double>());
                break;
            case KEY_S:
                this->position += this->front * (float)(this->speed * e.readData<double>());
                break;

            case KEY_A:
                this->position += normalize(cross(front, up)) * (float)(this->speed * e.readData<double>());
                break;
            case KEY_D:
                this->position -= normalize(cross(front, up)) * (float)(this->speed * e.readData<double>());
                break;

            case MOUSE_MOVED: {
                MousePos offset = e.readData<MousePos>();
                this->yaw += offset.x;
                this->pitch -= offset.y;
                break;
            }
            case WINDOW_RESIZE: {
                ScreenSize size = e.readData<ScreenSize>();
                projection = perspective(radians(this->fov), (float) size.width / size.height, 0.001f, 1000.0f);
                break;
            }
                default:
                break;
        }
    }
}