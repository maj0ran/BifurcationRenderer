//
// Created by mrn on 13.03.2019.
//

#include "Primitives.h"

namespace mrn {

    Mesh* mrn::Primitive::createCube() {
        mrn::Mesh* cube = new Mesh();

        mrn::GLVertex ldf;
        ldf.pos = vec3(-0.5, -0.5, -0.5);
        ldf.rgb =  vec3(0.0, 0.0, 0.0);

        mrn::GLVertex luf;
        luf.pos = vec3(-0.5, 0.5, -0.5);
        luf.rgb = vec3(0.0, 0.0, 1.0);

        mrn::GLVertex rdf;
        rdf.pos = vec3(0.5, -0.5, -0.5);
        rdf.rgb = vec3(0.0, 1.0, 0.0);

        mrn::GLVertex ruf;
        ruf.pos = vec3(0.5, 0.5, -0.5);
        ruf.rgb = vec3(0.0, 1.0, 1.0);

        mrn::GLVertex ldb;
        ldb.pos = vec3(-0.5, -0.5, 0.5);
        ldb.rgb = vec3(1.0, 0.0, 0.0);

        mrn::GLVertex lub;
        lub.pos = vec3(-0.5, 0.5, 0.5);
        lub.rgb = vec3(1.0, 0.0, 1.0);

        mrn::GLVertex rdb;
        rdb.pos = vec3(0.5, -0.5, 0.5);
        rdb.rgb = vec3(1.0, 1.0, 0.0);

        mrn::GLVertex rub;
        rub.pos = vec3(0.5, 0.5, 0.5);
        rub.rgb = vec3(1.0, 1.0, 1.0);

        cube->addVertex(ldf);
        cube->addVertex(luf);
        cube->addVertex(rdf);
        cube->addVertex(ruf);
        cube->addVertex(ldb);
        cube->addVertex(lub);
        cube->addVertex(rdb);
        cube->addVertex(rub);

        // Front
        cube->addTriangleIndices(0, 1, 2);
        cube->addTriangleIndices(1, 2, 3);
        // Left
        cube->addTriangleIndices(0, 2, 4);
        cube->addTriangleIndices(2, 4, 6);
        // Right
        cube->addTriangleIndices(1, 3, 5);
        cube->addTriangleIndices(3, 5, 7);
        // Down
        cube->addTriangleIndices(0, 1, 4);
        cube->addTriangleIndices(1, 4, 5);
        // Up
        cube->addTriangleIndices(2, 3, 6);
        cube->addTriangleIndices(3, 6, 7);
        // Back
        cube->addTriangleIndices(4, 5, 6);
        cube->addTriangleIndices(5, 6, 7);

        return cube;
    }

    Mesh* Primitive::createTriangle() {
        Mesh* triangle = new Mesh();

        GLVertex left;
        left.pos = vec3(-0.5f, -0.5f, 0.0f);
        left.rgb = vec3(1.0f, 0.0f, 0.0f);

        GLVertex right;
        right.pos = vec3(0.5f, -0.5f, 0.0f);
        right.rgb = vec3(0.0f, 1.0f, 0.0f);

        GLVertex up;
        up.pos = vec3(0.0f, 0.5f, 0.0f);
        up.rgb = vec3(0.0f, 0.0f, 1.0f);

        triangle->addVertex(left);
        triangle->addVertex(right);
        triangle->addVertex(up);

        triangle->addTriangleIndices(0, 1, 2);

        return triangle;



        
    }

    Mesh *Primitive::createPyramid() {
        Mesh* pyramid = new Mesh();

        GLVertex leftbottom;
        GLVertex rightbottom;
        GLVertex lefttop;
        GLVertex righttop;
        GLVertex up;

        leftbottom.pos = vec3(-0.5, -0.5, -0.5);
        rightbottom.pos = vec3(0.5, -0.5, -0.5);
        lefttop.pos = vec3(-0.5, 0.5, -0.5);
        righttop.pos = vec3(0.5, 0.5, -0.5);
        up.pos = vec3(0.0, 0.0, 0.5);

        leftbottom.rgb = vec3(1, 0, 0);
        rightbottom.rgb = vec3(0, 1, 0);
        lefttop.rgb = vec3(0, 0, 1);
        righttop.rgb = vec3(1, 1, 0);
        up.rgb = vec3(1, 1, 1);



        pyramid->addVertex(leftbottom);
        pyramid->addVertex(rightbottom);
        pyramid->addVertex(lefttop);
        pyramid->addVertex(righttop);
        pyramid->addVertex(up);

        // ground
        pyramid->addTriangleIndices(0, 1, 2);
        pyramid->addTriangleIndices(1, 2, 3);

        //sides
        pyramid->addTriangleIndices(0, 1, 4);
        pyramid->addTriangleIndices(0, 2, 4);
        pyramid->addTriangleIndices(1, 3, 4);
        pyramid->addTriangleIndices(2, 3, 4);

        return pyramid;
    }
}