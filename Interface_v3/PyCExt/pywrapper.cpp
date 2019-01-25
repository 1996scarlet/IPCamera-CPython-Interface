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

//////////////////////////////////////////////////////////////////
// numpy examples
// 
// python test code maybe:
//
// import pycext
// pycext.numpyTest("xyzzz")
// pycext.numpyTest("list")
// pycext.numpyTest("array")
// pycext.numpyTest("bytes")
//
typedef unsigned char BYTE;

static PyObject *
spam_numpyTest(PyObject *self, PyObject *args)
{
	const char *cmd;
	if (!PyArg_ParseTuple(args, "s", &cmd))
		return NULL;

	if (cmd == NULL) return (PyObject*)Py_BuildValue("s", "Null Parammfd!");
	else if (strcmp(cmd, "list") != 0 && strcmp(cmd, "array") != 0 && strcmp(cmd, "bytes") != 0) return (PyObject*)Py_BuildValue("s", cmd);

	PyObject *pretobj = nullptr;

	int Index_i = 0, Index_k = 0, Index_m = 0, Index_n = 0;
	if (strcmp(cmd, "list") == 0)
	{/*Pass by List: Transform an C Array to Python List*/
		double CArray[] = { 1.2, 4.5, 6.7, 8.9, 1.5, 0.5 };

		PyObject *PyList = PyList_New(6);
		pretobj = PyTuple_New(1);
		for (Index_i = 0; Index_i < PyList_Size(PyList); Index_i++){

			PyList_SetItem(PyList, Index_i, PyFloat_FromDouble(CArray[Index_i]));
		}

		// PyObject *pFuncFour = PyDict_GetItemString(pDict, "PassListFromCToPython");
		// cout << "C Array Pass Into The Python List:" << endl;
		PyTuple_SetItem(pretobj, 0, PyList);
		//PyObject_CallObject(pFuncFour, ArgList);
	}
	else if (strcmp(cmd, "array") == 0)
	{/*Pass by Python Array: Transform an C Array to Python Array*/
		double CArrays[3][3] = { { 1.3, 2.4, 5.6 }, { 4.5, 7.8, 8.9 }, { 1.7, 0.4, 0.8 } };
		npy_intp Dims[2] = { 3, 3 };

		PyObject *PyArray = PyArray_SimpleNewFromData(2, Dims, NPY_DOUBLE, CArrays);
		pretobj = PyTuple_New(1);
		PyTuple_SetItem(pretobj, 0, PyArray);

		//PyObject *pFuncFive = PyDict_GetItemString(pDict, "PassArrayFromCToPython");
		//PyObject_CallObject(pFuncFive, ArgArray);
	}
	else
	{/*Pass by Python Array: Transform an C Array to Python Array*/
		BYTE CArrays[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
		npy_intp Dims[2] = { 3, 3 };

		PyObject *PyArray = PyArray_SimpleNewFromData(2, Dims, NPY_UBYTE, CArrays);
		pretobj = PyTuple_New(1);
		PyTuple_SetItem(pretobj, 0, PyArray);

		//PyObject *pFuncFive = PyDict_GetItemString(pDict, "PassArrayFromCToPython");
		//PyObject_CallObject(pFuncFive, ArgArray);
	}

	return pretobj;
}

//* Example of wrapping the cos function from math.h using the Numpy-C-API.
//* wrapped cosine function
//*
//* python test code:
//
//* ArrList = [1, 2, 3, 4, 5, 6, 7, 8, 9]
//* Array_A  = np.asarray(ArrList, dtype='float' )
//* Array_B  = np.asarray(ArrList, dtype='double')
//* pycext.cos_func_np(Array_A)
//* pycext.cos_func_np(Array_B)
//*
static PyObject* cos_func_np(PyObject* self, PyObject* args)
{
	PyArrayObject *in_array;
	PyObject      *out_array;
	PyArrayIterObject *in_iter;
	PyArrayIterObject *out_iter;

	/*  parse single numpy array argument */
	if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &in_array))
		return NULL;

	/*  construct the output array, like the input array */
	out_array = PyArray_NewLikeArray(in_array, NPY_ANYORDER, NULL, 0);
	if (out_array == NULL)
		return NULL;

	/*  create the iterators */
	/* TODO: this iterator API is deprecated since 1.6
	*       replace in favour of the new NpyIter API */
	in_iter = (PyArrayIterObject *)PyArray_IterNew((PyObject*)in_array);
	out_iter = (PyArrayIterObject *)PyArray_IterNew(out_array);
	if (in_iter == NULL || out_iter == NULL)
		goto fail;

	/*  iterate over the arrays */
	while (in_iter->index < in_iter->size
		&& out_iter->index < out_iter->size) {
		/* get the datapointers */
		double * in_dataptr = (double *)in_iter->dataptr;
		double * out_dataptr = (double *)out_iter->dataptr;

		(*in_dataptr) += 1;

		/* cosine of input into output */
		*out_dataptr = cos(*in_dataptr);
		/* update the iterator */
		PyArray_ITER_NEXT(in_iter);
		PyArray_ITER_NEXT(out_iter);
	}

	/*  clean up and return the result */
	Py_DECREF(in_iter);
	Py_DECREF(out_iter);
	Py_INCREF(out_array);
	return out_array;

	/*  in case bad things happen */
fail:
	Py_XDECREF(out_array);
	Py_XDECREF(in_iter);
	Py_XDECREF(out_iter);
	return NULL;
}


/***************************************************************************
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
static PyMethodDef pycext_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"hello", (PyCFunction)say_hello, METH_VARARGS, NULL},
    {"numpyTest", (PyCFunction)spam_numpyTest, METH_VARARGS, NULL},
    {"np_cos", (PyCFunction)cos_func_np, METH_VARARGS, NULL},
    {NULL, NULL}
};

// for python 3.x
#if PY_MAJOR_VERSION >= 3

static int pycext_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int pycext_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

/*
 Defination for module info
*/
static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "pycext",
        NULL,
        sizeof(struct module_state),
        pycext_methods,
        NULL,
        pycext_traverse,
        pycext_clear,
        NULL
};

PyMODINIT_FUNC PyInit_pycext(void)
#define INITERROR_RETURN return NULL

#else // for python 2.x

PyMODINIT_FUNC initpycext(void)
#define INITERROR_RETURN return

#endif

{
    extern PyTypeObject CIPCamera_ClassInfo;
    CIPCamera_ClassInfo.tp_new = PyType_GenericNew; // fuction "new" --- create new instance
    /////////////////////////////////////////////////////
    // PyType_Ready: initialize the object type object
    // return:
    // 0 -- success
    // failed --- -1 and throws ex
    if (PyType_Ready(&CIPCamera_ClassInfo) < 0)
	 INITERROR_RETURN;

#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("pycext", pycext_methods);
#endif
    if (module == NULL) INITERROR_RETURN;

    struct module_state *st = GETSTATE(module);
    st->error = PyErr_NewException("pycext.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR_RETURN;
    }
    // Py_INCREF(st->error);
    // PyModule_AddObject(module,"error", st->error);

    // exporting the IPCamera class to python
    // Py_INCREF(&moduledef);
    PyModule_AddObject(module, "IPCamera", (PyObject*)&CIPCamera_ClassInfo); // export in module Dictionary

    //* IMPORTANT: this must be called for numpy (avoid exception:Segment Fault)
    import_array();

	// printf("debug:===>xx1 PyArray_API=0x%x PyArray_API[93]=0x%X\r\n", PyArray_API, PyArray_API[93]);
	// NET_DVR_Init();

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
