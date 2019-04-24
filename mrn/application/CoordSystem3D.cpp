//
// Created by mrn on 12.04.2019.
//

#include "CoordSystem3D.h"
#include "../engine/common.h"
#include "../engine/Mesh.h"
#include "../engine/Primitives.h"

namespace mrn {

    Axis::Axis(AXIS_DIRECTION direction) {
        this->direction = direction;
        switch(direction) {
            case RIGHT:
                direction_vector = glm::vec3(1.0, 0.0, 0.0);
                break;
            case UP:
                direction_vector = glm::vec3(0.0, 1.0, 0.0);
                break;
            case BACK:
                direction_vector = glm::vec3(0.0, 0.0, 1.0);
                break;

        }
        min = -8;
        max = 8;

        axis_line.p1_pos(direction_vector * min);
        axis_line.p2_pos(direction_vector * max);

        axis_line.p1_color(vec3(1.0f, 0.0f, 0.0f));
        axis_line.p2_color(vec3(1.0f, 0.0f, 0.0f));


    }

    Axis::~Axis() {

    }

    CoordSystem3D::CoordSystem3D() : x(Axis(RIGHT)), y(Axis(UP)), z(Axis(BACK)) {
        draw_type = GL_LINES;
        use_indices = false;
        x.axis_line.p1_color(RED);
        x.axis_line.p2_color(RED);
        y.axis_line.p1_color(GREEN);
        y.axis_line.p2_color(GREEN);
        z.axis_line.p1_color(BLUE);
        z.axis_line.p2_color(BLUE);
        vertices.insert(std::end(vertices), std::begin(x.axis_line.vertices), std::end(x.axis_line.vertices));
        vertices.insert(std::end(vertices), std::begin(y.axis_line.vertices), std::end(y.axis_line.vertices));
        vertices.insert(std::end(vertices), std::begin(z.axis_line.vertices), std::end(z.axis_line.vertices));

        mrn::Mesh* x_arrow = mrn::Primitive::createPyramid();
        mrn::Mesh* y_arrow = mrn::Primitive::createPyramid();
        mrn::Mesh* z_arrow = mrn::Primitive::createPyramid();

   //     x_arrow.
    }

    CoordSystem3D::~CoordSystem3D() {

    }

}
