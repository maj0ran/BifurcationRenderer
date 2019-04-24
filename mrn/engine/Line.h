//
// Created by Marian Cichy
//

#pragma once

#include <glad/glad.h>
#include "Vertex.h"
#include "Renderable.h"

namespace mrn {
    class Line : public Renderable {
    public:
        Line();
        ~Line();

        void p1_pos(vec3 pos);
        void p2_pos(vec3 pos);

        void p1_color(vec3 color);
        void p2_color(vec3 color);
    private:
    };

}
