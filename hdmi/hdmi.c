#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#include <string.h>

static PyObject* rgba_to_rgb16(PyObject* self, PyObject* args) {
    const char* rgba;
    Py_ssize_t data_len;
    int width, height;

    if (!PyArg_ParseTuple(args, "y#ii", &rgba, &data_len, &width, &height)) {
        return NULL;
    }

    if (width <= 0 || height <= 0) {
        PyErr_SetString(PyExc_ValueError, "width and height must be positive");
        return NULL;
    }

    Py_ssize_t expected_len = (Py_ssize_t)width * (Py_ssize_t)height * 4;
    if (data_len < expected_len) {
        PyErr_SetString(PyExc_ValueError, "RGBA buffer is smaller than width * height * 4");
        return NULL;
    }

    Py_ssize_t rgb565_size = (Py_ssize_t)width * (Py_ssize_t)height * (Py_ssize_t)sizeof(unsigned short);
    unsigned short *rgb565 = malloc((size_t)rgb565_size);
    if (!rgb565) {
        PyErr_NoMemory();
        return NULL;
    }

    for (Py_ssize_t i = 0; i < (Py_ssize_t)width * (Py_ssize_t)height; ++i)
    {
        unsigned char r = rgba[i * 4];
        unsigned char g = rgba[i * 4 + 1];
        unsigned char b = rgba[i * 4 + 2];

        rgb565[i] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }
    PyObject *result = PyBytes_FromStringAndSize((char*)rgb565, rgb565_size);
    free(rgb565);
    return result;
}

static PyObject* rgb_to_rgb16(PyObject* self, PyObject* args) {
    const char* rgb;
    Py_ssize_t data_len;
    int width, height;

    if (!PyArg_ParseTuple(args, "y#ii", &rgb, &data_len, &width, &height)) {
        return NULL;
    }

    if (width <= 0 || height <= 0) {
        PyErr_SetString(PyExc_ValueError, "width and height must be positive");
        return NULL;
    }

    Py_ssize_t expected_len = (Py_ssize_t)width * (Py_ssize_t)height * 3;
    if (data_len < expected_len) {
        PyErr_SetString(PyExc_ValueError, "RGB buffer is smaller than width * height * 3");
        return NULL;
    }

    Py_ssize_t rgb565_size = (Py_ssize_t)width * (Py_ssize_t)height * (Py_ssize_t)sizeof(unsigned short);
    unsigned short *rgb565 = malloc((size_t)rgb565_size);
    if (!rgb565) {
        PyErr_NoMemory();
        return NULL;
    }

    for (Py_ssize_t i = 0; i < (Py_ssize_t)width * (Py_ssize_t)height; ++i)
    {
        unsigned char r = rgb[i * 3];
        unsigned char g = rgb[i * 3 + 1];
        unsigned char b = rgb[i * 3 + 2];

        rgb565[i] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }
    PyObject *result = PyBytes_FromStringAndSize((char*)rgb565, rgb565_size);
    free(rgb565);
    return result;
}

static PyMethodDef clib_methods[] = {
    {"rgba_to_rgb16", rgba_to_rgb16, METH_VARARGS, "Convert RGBA to RGB565"},
    {"rgb_to_rgb16", rgb_to_rgb16, METH_VARARGS, "Convert RGB to RGB565"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef clib_module = {
    PyModuleDef_HEAD_INIT,
    "_clib",
    "C library for image conversion",
    -1,
    clib_methods
};

// This is the required function name for Python 3
PyMODINIT_FUNC PyInit__clib(void) {
    return PyModule_Create(&clib_module);
}