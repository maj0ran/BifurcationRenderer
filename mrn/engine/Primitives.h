//
// Created by mrn on 13.03.2019.
//

#pragma once

#include "Mesh.h"

namespace mrn {
    class Primitive {
        public:
        static Mesh* createCube();
        static Mesh* createTriangle();
        static Mesh* createPyramid();
    };
}