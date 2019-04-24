//
// Created by Marian Cichy
//

#pragma once
#include <glm.hpp>
#include <ext/matrix_clip_space.hpp>

namespace mrn {
    class ArcballCamera {
    public:
        ArcballCamera(float phi, float theta, float distance, glm::vec3 target);
        ~ArcballCamera();

        glm::mat4 getViewMatrix();

        void update();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        glm::vec3 position;
        glm::vec3 target;
        float distance;


        float theta = 0; // XZ
        float phi = 0;
    };

}


