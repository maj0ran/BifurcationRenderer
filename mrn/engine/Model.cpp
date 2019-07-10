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

    size_t Model::getVertexCount() {
        return vertex_data->vertices.size();
    }

    void Model::initBuf() {
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(mrn::GLVertex), &this->vertex_data->vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_data->indices.size() * sizeof(uint32), &vertex_data->indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mrn::GLVertex), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mrn::GLVertex), (void*)offsetof(GLVertex, rgb));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }

    void Model::bind() {
        glBindVertexArray(this->vao);
    }

    Model::Model(mrn::Mesh *mesh, mrn::Shader* shader) {
        this->vertex_data = mesh;
        this->shader = shader;
        initBuf();
    }

}

