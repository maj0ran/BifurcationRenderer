#include <utility>

//
// Created by Marian Cichy
//

#include "Widget.h"

mrn::ui::Widget::Widget(std::string title, float x, float y, float width, float height) :
    title(std::move(title)), x(x), y(y), width(width), height(height)
{
    vec3 color(1, 0, 0);
    mrn::Vertex v1;
    v1.pos = vec3(x, y, 0);
    v1.rgb = color;

    mrn::Vertex v2;
    v2.pos = vec3(x + width, y, 0);
    v2.rgb = color;

    mrn::Vertex v3;
    v3.pos = vec3(x, y + height, 0);
    v3.rgb = color;

    mrn::Vertex v4;
    v4.pos = vec3(x + width, y + height, 0);
    v4.rgb = color;

    this->vertex_data->addVertex(v1);
    this->vertex_data->addVertex(v2);
    this->vertex_data->addVertex(v3);
    this->vertex_data->addVertex(v4);

    this->vertex_data->addTriangleIndices(0, 1, 2);
    this->vertex_data->addTriangleIndices(1, 2, 3);

    this->vertex_data->initBuf();

    this->shader = new Shader("shader/ui.vert", "shader/ui.frag");
    this->shader->use();

}

mrn::ui::Widget::~Widget() {

}

void mrn::ui::Widget::render() {
  //  glDisable(GL_DEPTH_TEST);
    this->shader->use();
    this->vertex_data->bind();
    glDrawElements(GL_TRIANGLES, this->vertex_data->indices.size(), GL_UNSIGNED_INT, 0);
    glEnable(GL_DEPTH_TEST);
}

void mrn::ui::Widget::addElement(mrn::ui::WidgetElement* e) {
    this->elements.push_back(e);
}
