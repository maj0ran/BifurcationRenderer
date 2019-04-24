//
// Created by Marian Cichy
//

#include "Model.h"

using namespace glm;

namespace mrn {

    Model::Model() {
        this->trans_mat = mat4(1.0f);
    }

    Model::~Model() {

    }

    void Model::translate(float x, float y, float z) {
        this->pos = vec3(x, y, z);
        trans_mat = mat4(1.0f);
        trans_mat = glm::translate(trans_mat, pos);
        // GLint transform_loc = glGetUniformLocation(shader->id, "transform");
        // glUniformMatrix4fv(transform_loc, 1, GL_FALSE, value_ptr(trans));
    }

    vec3 Model::getPos() {
        return pos;
    }
    ;
    void Model::attachShader(Shader *shader) {
        this->shader = shader;
    //    vertex_array_id = this->vertices->initBuf();
    }

    mat4 Model::getTranslationMat() {
        return trans_mat;
    }

}

