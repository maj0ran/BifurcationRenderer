//
// Created by mrn on 12.04.2019.
//

#pragma once

#include "../engine/Vertex.h"
#include "../engine/Line.h"

#include <glad/glad.h>

#include <string>
namespace mrn {

    enum AXIS_DIRECTION {
        RIGHT,
        UP,
        BACK,
    };

    /*** Class that represents a single Axis ***/
    class Axis {
    public:
        Axis(AXIS_DIRECTION direction);
        ~Axis();
        std::string label;
        float min;
        float max;
        AXIS_DIRECTION direction;

        mrn::Line axis_line;
    private:
        glm::vec3 direction_vector;
    };


    /*** Class that represents the whole Grid ***/
    class CoordSystem3D : public Mesh {
    public:
        CoordSystem3D();
        ~CoordSystem3D();

        Axis x;
        Axis y;
        Axis z;
    private:

    };

}



