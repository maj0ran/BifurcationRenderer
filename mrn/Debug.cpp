//
// Created by mrn on 19/06/27.
//

#include "Debug.h"

void Debug::addPoint(glm::vec3 point, glm::vec3 color) {
    mrn::GLVertex v;
    v.pos = point;
    v.rgb = color;
    this->points.push_back(v);
}

Debug::Debug() {

}

void Debug::toVram() {
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(mrn::GLVertex), &this->points[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mrn::GLVertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mrn::GLVertex), (void*)offsetof(mrn::GLVertex, rgb));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Debug::draw() {
    glBindVertexArray(this->vao);
    glDrawArrays(GL_POINTS, 0, getVertexCount());
}

int Debug::getVertexCount() {
    return this->points.size();
}
