//
// Created by Marian Cichy
//

#pragma once

#include "Mesh.h"
namespace mrn {
    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void writeToVRAM(Mesh *data);

        GLuint vao;
        GLuint vbo;
        GLuint ebo;
    };

}
