//
// Created by mrn on 19/07/09.
//

#pragma once

#include <Python.h>
#include <numpy/arrayobject.h>

class PyFunction {
public:
    explicit PyFunction(PyObject *pyFunc);
    ~PyFunction();

private:
    PyObject *pyFuncPtr;
};


