//
// Created by Marian Cichy
//
#pragma once

#include <stddef.h>
#include <glm.hpp>
#include "common.h"

using namespace glm;

namespace mrn {
    struct Vertex {
    //    Vertex() = default;
    //    explicit Vertex(vec3 pos) { this->pos = pos; this->rgb = RED; }
        vec3 pos;
        vec3 rgb;
        vec2 tex;
    };


}


