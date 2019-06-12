//
// Created by Marian Cichy
//

#pragma once

#include <glad/glad.h>
#include "Vertex.h"
#include <vector>

namespace mrn {
    class Mesh {
    public:
        Mesh();
        virtual ~Mesh();

        void addVertex(mrn::Vertex &vertex);
        void addTriangleIndices(uint32 p1, uint32 p2, uint32 p3);


        GLuint draw_type = GL_TRIANGLES;
        bool use_indices = true;
        std::vector<mrn::Vertex> vertices;
        std::vector<uint32> indices;

    private:
    };
}

