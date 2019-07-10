//
// Created by mrn on 19/07/09.
//

#pragma once
#include <string>
#include <vector>
#include <numpy/arrayobject.h>
#include "PyFunction.h"
#include "engine/GLVertex.h"

using namespace std;


class PyInterface {
public:
    PyInterface();
    ~PyInterface();

    PyFunction getFunction(string pythonfile, string funcname);
    PyObject* interpolate_triangles(std::vector<mrn::GLVertex>, std::vector<uint32_t> indices);

};


