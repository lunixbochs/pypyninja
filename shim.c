#undef PyErr_Print
#undef PyEval_InitThreads
#undef PyEval_SaveThread
#undef PyGILState_Ensure
#undef PyGILState_Release
#undef PyImport_ImportModule
#undef PyList_Insert
#undef PyObject_GetAttrString
#undef PyRun_SimpleString
#undef Py_DontWriteBytecodeFlag
#undef Py_GetVersion
#undef Py_IsInitialized
#undef PyUnicode_FromString

#include "shim.h"

CFFI_DLLEXPORT int Py_DontWriteBytecodeFlag;

CFFI_DLLEXPORT void PyErr_Print(void) {}

CFFI_DLLEXPORT void PyEval_InitThreads(void) {}

CFFI_DLLEXPORT PyThreadState *PyEval_SaveThread(void) { return NULL; }

CFFI_DLLEXPORT PyGILState_STATE PyGILState_Ensure(void) {
    return 0;
}

CFFI_DLLEXPORT void PyGILState_Release(PyGILState_STATE state) {}

CFFI_DLLEXPORT PyObject *PyImport_ImportModule(const char *name) {
    return (PyObject *)name;
}

CFFI_DLLEXPORT PyObject *PyObject_GetAttrString(PyObject *obj, const char *name) {
    if (strcmp((char *)obj, "sys") == 0 && strcmp((char *)name, "path") == 0) {
        return (PyObject *)"sys.path";
    }
    return (PyObject *)name;
}

CFFI_DLLEXPORT int PyList_Insert(PyObject *obj, Py_ssize_t i, PyObject *item) {
    // only used for sys.path.insert(0, item)
    pps_sys_path_insert(i, (const char *)item);
    return 0;
}

CFFI_DLLEXPORT int PyRun_SimpleString(const char *str) {
    pps_eval(str);
    return 0;
}
CFFI_DLLEXPORT void PySys_SetArgvEx(int argc, wchar_t **argv, int unk) {}
CFFI_DLLEXPORT PyObject *PyUnicode_FromString(const char *u) { return (PyObject *)u; }
CFFI_DLLEXPORT const char *Py_GetVersion(void) {
    return pps_get_version();
}

static int initialized = 0;
CFFI_DLLEXPORT void Py_Initialize(void) { initialized = 1; }
CFFI_DLLEXPORT int Py_IsInitialized(void) { return initialized; }

/*
 * Undeclared on purpose:
PyMem_Free
Py_GetPath
Py_EncodeLocale
Py_DontWriteBytecodeFlag
Py_SetPythonHome
*/
