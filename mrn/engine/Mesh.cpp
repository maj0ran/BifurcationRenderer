//
// Created by Marian Cichy
//

#include "Mesh.h"
namespace mrn {



    Mesh::Mesh() {

    }

    Mesh::~Mesh() {

    }

    void Mesh::addVertex(mrn::Vertex &vertex) {
        this->vertices.push_back(vertex);
    }


    void Mesh::addTriangleIndices(uint32 p1, uint32 p2, uint32 p3) {
        this->indices.push_back(p1);
        this->indices.push_back(p2);
        this->indices.push_back(p3);
        TriangleIndex triangle;
        triangle.setVertices(p1, p2, p3);
        this->triangleIndices.push_back(triangle);
    }

    void Mesh::addTriangle(TriangleIndex triangle) {
        this->triangleIndices.push_back(triangle);
    }

    size_t Mesh::getTriangleCount() {
        return triangleIndices.size();
    }

    TriangleIndex Mesh::getTriangle(size_t index) {
        return triangleIndices.at(index);
    }

    Normal Mesh::calcNormalOfTriangle(size_t index) {
        TriangleIndex triangle = getTriangle(index);
        vec3 v1 = vertices[triangle.getP0()].pos;
        vec3 v2 = vertices[triangle.getP1()].pos;
        vec3 v3 = vertices[triangle.getP2()].pos;

        vec3 edge1 = v2 - v1;
        vec3 edge2 = v3 - v1;
        vec3 normal_dir = cross(edge1, edge2);
        normal_dir = normalize(normal_dir);
        normal_dir /= -100;

        float normal_pos_x = (v1.x + v2.x + v3.x) / 3;
        float normal_pos_y = (v1.y + v2.y + v3.y) / 3;
        float normal_pos_z = (v1.z + v2.z + v3.z) / 3;
        vec3 normal_pos = vec3(normal_pos_x, normal_pos_y, normal_pos_z);

        normal_dir = normal_pos + normal_dir;
      //  normal_dir *= 2;

        Normal normal= { normal_dir, normal_pos };
        return normal;
    }
}