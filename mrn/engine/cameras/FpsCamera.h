//
// Created by Marian Cichy
//

#pragma once

#include <glm.hpp>
#include <glad/glad.h>

using namespace glm;

enum CAMERA_COMMAND {
    CAM_FORWARD,
    CAM_BACKWARD,
    CAM_LEFT,
    CAM_RIGHT,
};

namespace mrn {
    class FpsCamera {
    public:
        FpsCamera(vec3 position, vec3 front);
        ~FpsCamera();

        vec3 position;
        vec3 front;
        vec3 right;
        vec3 up;

        float fov;
        float speed;
        mat4 getViewMatrix();
        mat4 projection;


        void calcProjectionMat();
        void update();

    private:
        vec3 worldUp = vec3(0, 1, 0);
        void processKeyboard(CAMERA_COMMAND cmd, float deltaTime);


    };

}


