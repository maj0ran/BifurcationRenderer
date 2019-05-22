//
// Created by Marian Cichy
//

#include "Renderable.h"
namespace mrn {

    Renderable::Renderable() {

    }

    Renderable::~Renderable() {

    }

    void Renderable::bind() {
        glBindVertexArray(this->vao);
    }

    void Renderable::initBuf() {
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mrn::Vertex), &this->vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex, rgb));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

    }

    void Renderable::addVertex(mrn::Vertex &vertex) {
        this->vertices.push_back(vertex);
    }


    void Renderable::addTriangleIndices(uint32 p1, uint32 p2, uint32 p3) {
        this->indices.push_back(p1);
        this->indices.push_back(p2);
        this->indices.push_back(p3);
    }
}