//
// Created by Marian Cichy
//
#pragma once

#include <stddef.h>
#include <glm.hpp>
#include "common.h"
#include "../application/Bifurcation/Vertex.h"

using namespace glm;

namespace mrn {
    struct GLVertex {
        GLVertex() = default;
        explicit GLVertex(vec3 pos) { this->pos = pos; this->rgb = RED; }
        vec3 pos;
        vec3 rgb;
        vec2 tex;
        vec3 normal;

        GLVertex(Vertex v) {
            this->pos = v.pos;
            this->rgb = RED;
        }

        GLVertex(Vertex v, vec3 color) {
            this->pos = v.pos;
            this->rgb = color;
        }
    };


}


