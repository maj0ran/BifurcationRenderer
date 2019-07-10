//
// Created by mrn on 19/07/09.
//

#include "PyFunction.h"

PyFunction::PyFunction(PyObject *pyFunc) {
    pyFuncPtr = pyFunc;
}

PyFunction::~PyFunction() {

}
