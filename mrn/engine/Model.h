//
// Created by Marian Cichy
//

#pragma once

#include <glm.hpp>
#include "Mesh.h"
#include "Shader.h"

using namespace glm;

namespace mrn {
    class Model {
    public:
        Model();
        ~Model();

        Shader* shader;
        Renderable* vertex_data;
        GLuint vertex_array_id;

        void translate(float x, float y, float z);
        vec3 getPos();

        void attachShader(Shader* shader);

        mat4 getTranslationMat();
        size_t  getVertexCount();
    private:
        vec3 pos;
        vec3 rot;
        vec3 scale;

        mat4 trans_mat;
        mat4 rot_mat;
        mat4 scale_mat;
    };

}

