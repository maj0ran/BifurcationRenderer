//
// Created by Marian Cichy
//
#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace glm;

namespace mrn {
    class Shader {
    public:
        GLuint id;
        mat4 proj = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
        Shader(const char *vertexPath, const char *fragmentPath);

        void use();
        void translate();

    private:
        const char *readFile(const char *filepath);

    };

}

