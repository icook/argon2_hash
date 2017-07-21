#include <Python.h>

#include "argon2.h"

static PyObject *argon2_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
	argon2d_hash_raw(2,16,1,(char *)PyBytes_AsString((PyObject*) input),80,(char *)PyBytes_AsString((PyObject*) input),80,output,32);
#else
	argon2d_hash_raw(2,16,1,(char *)PyString_AsString((PyObject*) input),80,(char *)PyString_AsString((PyObject*) input),80,output,32);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef Argon2Methods[] = {
    { "getPoWHash", argon2_getpowhash, METH_VARARGS, "Returns the proof of work hash using argon2 hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef Argon2Module = {
    PyModuleDef_HEAD_INIT,
    "argon2_hash",
    "...",
    -1,
    Argon2Methods
};

PyMODINIT_FUNC PyInit_argon2_hash(void) {
    return PyModule_Create(&Argon2Module);
}

#else

PyMODINIT_FUNC initargon2_hash(void) {
    (void) Py_InitModule("argon2_hash", Argon2Methods);
}
#endif
