//
// Created by Marian Cichy
//

#pragma once

#include <glad/glad.h>
#include "Vertex.h"
#include <vector>

namespace mrn {
    class Renderable {
    public:
        Renderable();
        virtual ~Renderable();

        void addVertex(mrn::Vertex &vertex);

        void initBuf();

        void bind();

        GLuint draw_type = GL_TRIANGLES;
        bool use_indices = true;
        std::vector<mrn::Vertex> vertices;
        std::vector<uint32> indices;
    protected:
        GLuint vao;
        GLuint vbo;
        GLuint ebo;

    private:
    };
}

