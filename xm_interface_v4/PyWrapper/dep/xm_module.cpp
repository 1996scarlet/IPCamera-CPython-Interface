#include <Python.h>
// #include "../sdk/include/CXMCamera.h"

#include <iostream>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}

int great_function(int a)
{
    return a + 1;
}

static PyObject *_great_function(PyObject *self, PyObject *args)
{
    int _a;
    int res;
    if (!PyArg_ParseTuple(args, "i", &_a))
        return NULL;
    res = great_function(_a);
    return PyLong_FromLong(res);
}

static PyMethodDef GreateModuleMethods[] = {
    {"great_function",
     _great_function,
     METH_VARARGS,
     ""},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef xm_module = {
    PyModuleDef_HEAD_INIT,
    "xm_module",
    NULL,
    -1,
    GreateModuleMethods};

PyMODINIT_FUNC PyInit_xm_module(void)
{
    PyObject *m;
    m = PyModule_Create(&xm_module);
    if (m == NULL)
        return NULL;
    printf("init xm_module module\n");
    return m;
}