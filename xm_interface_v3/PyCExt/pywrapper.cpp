#include "Python.h"
#include <numpy/arrayobject.h> // for numpy array
#include <math.h>

static PyObject *
say_hello(PyObject *self, PyObject *args) {
    PyObject *name, *result;

    if (!PyArg_ParseTuple(args, "U:say_hello", &name))
	return NULL;

    result = PyUnicode_FromFormat("Hello, %S!", name);
    return result;
}

/*                   
/* Module initialization and state

   Python 3 has a revamped extension module initialization system. (See PEP 3121.) Instead of storing module state in globals, they should be stored in an interpreter specific structure. Creating modules that act correctly in both Python 2 and Python 3 is tricky. The following simple example demonstrates how.
*/
struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
  #define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
  #define GETSTATE(m) (&_state)
  static struct module_state _state; // define the global state obj
#endif

static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

/*
 The exported function list of this module
*/
static PyMethodDef xmcext_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"hello", (PyCFunction)say_hello, METH_VARARGS, NULL},
    {NULL, NULL}
};

// for python 3.x
#if PY_MAJOR_VERSION >= 3

static int xmcext_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int xmcext_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

/*
 Defination for module info
*/
static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "xmcext",
        NULL,
        sizeof(struct module_state),
        xmcext_methods,
        NULL,
        xmcext_traverse,
        xmcext_clear,
        NULL
};

PyMODINIT_FUNC PyInit_xmcext(void)
#define INITERROR_RETURN return NULL

#else // for python 2.x

PyMODINIT_FUNC initxmcext(void)
#define INITERROR_RETURN return

#endif

{
    extern PyTypeObject CXMCamera_ClassInfo;
    CXMCamera_ClassInfo.tp_new = PyType_GenericNew; // fuction "new" --- create new instance
    /////////////////////////////////////////////////////
    // PyType_Ready: initialize the object type object
    // return:
    // 0 -- success
    // failed --- -1 and throws ex
    if (PyType_Ready(&CXMCamera_ClassInfo) < 0)
	 INITERROR_RETURN;

#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("xmcext", xmcext_methods);
#endif
    if (module == NULL) INITERROR_RETURN;

    struct module_state *st = GETSTATE(module);
    st->error = PyErr_NewException("xmcext.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR_RETURN;
    }
    // Py_INCREF(st->error);
    // PyModule_AddObject(module,"error", st->error);

    // exporting the XMCamera class to python
    // Py_INCREF(&moduledef);
    PyModule_AddObject(module, "XMCamera", (PyObject*)&CXMCamera_ClassInfo); // export in module Dictionary

    //* IMPORTANT: this must be called for numpy (avoid exception:Segment Fault)
    import_array();


#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
