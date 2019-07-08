//
// Created by Marian Cichy
//

#pragma once

#include <glad/glad.h>
#include "Vertex.h"
#include "TriangleIndex.h"
#include <vector>

namespace mrn {

    struct Normal {
        vec3 pos;
        vec3 dir;
    };

    class Mesh {
    public:
        std::vector<mrn::GLVertex> vertices;
        std::vector<uint32> indices;


        Mesh();
        virtual ~Mesh();

        void addVertex(mrn::GLVertex &vertex);
        void addTriangleIndices(uint32 p1, uint32 p2, uint32 p3);
        void addTriangle(TriangleIndex triangle);


        GLuint draw_type = GL_TRIANGLES;
        bool use_indices = false;

        size_t getTriangleCount();
        TriangleIndex getTriangle(size_t index);
        Normal calcNormalOfTriangle(size_t index);
    private:
        std::vector<TriangleIndex> triangleIndices;
    };
}

