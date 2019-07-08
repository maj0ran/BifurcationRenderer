//
// Created by mrn on 19/06/27.
//

#pragma once

#include <vector>
#include <vec3.hpp>
#include "engine/Shader.h"
#include "engine/Vertex.h"

class Debug {
private:
    std::vector<mrn::GLVertex> points;
    mrn::Shader* shader = new mrn::Shader("shader/default_mvp.vert", "shader/default.frag");

    GLuint vbo;
    GLuint vao;

public:
    Debug();
    ~Debug() = default;

    int getVertexCount();
    void addPoint(glm::vec3 point, glm::vec3 color);
    void toVram();
    void draw();
};


