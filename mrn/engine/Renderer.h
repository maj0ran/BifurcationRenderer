//
// Created by Marian Cichy
//

#pragma once

#include "Renderable.h"
namespace mrn {
    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void writeToVRAM(Renderable *data);

        GLuint vao;
        GLuint vbo;
        GLuint ebo;
    };

}
