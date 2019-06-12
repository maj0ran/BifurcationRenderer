#include "Vertex.h"

namespace mrn {
    struct Triangle {
        Vertex p1;
        Vertex p2;
        Vertex p3;

        vec3 normal;
    };
}