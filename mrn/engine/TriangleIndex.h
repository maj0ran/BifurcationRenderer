//
// Created by mrn on 19/06/12.
//

#pragma once

#include "GLVertex.h"

namespace mrn {
    class TriangleIndex {
    public:
        TriangleIndex();
        ~TriangleIndex();

        void setVertices(uint32_t p0, uint32_t p1, uint32_t p2);
        uint32_t getP0();
        uint32_t getP1();
        uint32_t getP2();

    private:
        uint32_t p0, p1, p2;



    };


}