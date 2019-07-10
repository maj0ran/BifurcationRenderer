//
// Created by Marian Cichy
//

#pragma once

#include <glad/glad.h>
#include "GLVertex.h"
#include "TriangleIndex.h"
#include <vector>

namespace mrn {



    class Mesh {
    public:
        Mesh();
        virtual ~Mesh();

        std::vector<mrn::GLVertex> vertices;
        std::vector<uint32_t> indices;

        void setPatchSize(int size);
        int getPatchSize();


        void addVertex(mrn::GLVertex &vertex);
        void addIndex(uint32 i);

        GLuint draw_type = GL_TRIANGLES;
        bool use_indices = false;

    private:
        int patch_size;
    };
}

