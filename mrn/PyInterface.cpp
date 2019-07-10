//
// Created by mrn on 19/07/09.
//

#include <Python.h>
#include "PyInterface.h"

PyInterface::PyInterface() {
    // TODO: All the Magic after Py_Initialize() is just copypasted and not understood
    char* syspath = (char*)malloc(256);
    char* pwd = (char*)malloc(256);
    Py_Initialize();
    PyRun_SimpleString("import sys");
    strcpy(syspath, "sys.path.append('");
    if (getcwd(pwd, 255) != nullptr)
        strcat(syspath, pwd);
    strcat(syspath, "')");
    PyRun_SimpleString(syspath);
}

PyInterface::~PyInterface() {
    Py_Finalize();
}

PyFunction PyInterface::getFunction(string pythonfile, string funcname) {
    PyObject *pyName = PyUnicode_FromString(pythonfile.c_str());
    PyObject *pyModule = PyImport_Import(pyName);

    Py_DECREF(pyName);

    if(pyModule == nullptr) {
        PyErr_Print();
        fprintf(stderr, "Failed to load Script %s\n", pythonfile.c_str());
        exit(1337);
    }

    PyObject *pyFunc = PyObject_GetAttrString(pyModule, funcname.c_str());

    if(!pyFunc || !PyCallable_Check(pyFunc)) {
        if(PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function %s\n", funcname.c_str());
    }

    PyFunction func(pyFunc);

    return func;

}

PyObject *PyInterface::interpolate_triangles(std::vector<mrn::GLVertex> vertices, std::vector<uint32_t> indices) {
    import_array();

    const char* pythonfile = "interpol";
    const char* function_name = "interpolate_triangles";
    PyObject *pyName = PyUnicode_FromString(pythonfile);
    PyObject *pyModule = PyImport_Import(pyName);
    PyObject *pyArgs;

    Py_DECREF(pyName);

    if(pyModule == nullptr) {
        PyErr_Print();
        fprintf(stderr, "Failed to load Script %s\n", pythonfile);
        exit(1337);
    }

    PyObject *pyFunc = PyObject_GetAttrString(pyModule, function_name);

    if(!pyFunc || !PyCallable_Check(pyFunc)) {
        if(PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function %s\n", function_name);
    }
    npy_intp* shape = (npy_intp*)malloc(sizeof(int) * 2);
    *(shape + 0) = vertices.size();
    *(shape + 1) = 3;

    // we only need the positions from the Vertices
    std::vector<float> vertex_positions;
    for(int i = 0; i < vertices.size(); i++) {
        vertex_positions.push_back(vertices[i].pos.x);
        vertex_positions.push_back(vertices[i].pos.y);
        vertex_positions.push_back(vertices[i].pos.z);
    }
    pyArgs = PyTuple_New(2);
    PyObject* pyVertices = PyArray_SimpleNewFromData(2, shape, NPY_FLOAT32, &vertex_positions[0]);
    PyObject* pyIndices = PyArray_SimpleNewFromData(2, shape, NPY_INT, &indices[0]);
    PyTuple_SetItem(pyArgs, 0, pyVertices);
    PyTuple_SetItem(pyArgs, 1, pyIndices);

    PyArrayObject *pyResult = reinterpret_cast<PyArrayObject*>(PyObject_CallObject(pyFunc, pyArgs));
    printf("RESULT : %f\n", (float)*(double*)pyResult->data);



}
