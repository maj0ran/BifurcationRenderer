//
// Created by Marian Cichy
//

#include "Line.h"

mrn::Line::Line() {
 draw_type = GL_LINES;
 vertices = std::vector<Vertex>(2);
}

mrn::Line::~Line() {

}



void mrn::Line::p1_pos(vec3 pos) {
    vertices[0].pos = pos;
}

void mrn::Line::p2_pos(vec3 pos) {
    vertices[1].pos = pos;
}

void mrn::Line::p1_color(vec3 color) {
    vertices[0].rgb = color;
}

void mrn::Line::p2_color(vec3 color) {
    vertices[1].rgb = color;
}
