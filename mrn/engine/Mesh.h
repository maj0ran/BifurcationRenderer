//
// Created by Marian Cichy
//

#pragma once

#include <vector>
#include "Vertex.h"
#include "glad/glad.h"
#include "Renderable.h"


namespace mrn {

    using namespace glm;

    class Mesh : public Renderable {
    public:


        Mesh();
        ~Mesh() override;

        void addTriangleIndices(uint32 p1, uint32 p2, uint32 p3);


    };

}


