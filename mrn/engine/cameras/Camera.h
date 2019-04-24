//
// Created by Marian Cichy
//

/**
 * The Base-Class for all Cameras. Every Camera has:
 * a position,
 * a target where it looks at,
 * the vector which represents "up" in the world (usually [0, 1, 0])
 *
 * furthermore:
 * a fov, the calculated viewMatrix and projectionMatrix
 */
#include <glm.hpp>
using namespace glm;

namespace mrn {
    class Camera {

    private:
        vec3 position;
        vec3 target;
        vec3 worldUp = vec3(0.0f, 1.0f, 0.0);

        float fov;

        mat4 projectionMatrix;
        mat4 viewMatrix;
    public:

        Camera();
        ~Camera();
        float getFov() const;
        void setFov(float fov);

        const vec3 &getPosition() const;
        void setPosition(const vec3 &position);

        const vec3 &getTarget() const;
        void setTarget(const vec3 &target);

        void setWorldUp(const vec3 &worldUp);

        const mat4 &getViewMatrix() ;


    };

}


