// Include Python.h first, otherwise we will get warnings about "_POSIX_C_SOURCE" redefined etc
#include <Python.h>

#include <iostream>

int main( int argc, char *argv[]) {

  PyObject *sys, *path;
  PyObject *pModuleName, *pModule;
  PyObject *pClassName,  *pClass;
  PyObject *pAdder;
  PyObject *pMethodName, *pMethod;
  PyObject *pAdderValue, *pX;
  PyObject *pInitArgs,   *pResult;

  // C++ string names for module, class, and method
  std::string moduleName("ClassDef");
  std::string className("Adder");
  std::string methodName("add");

  double adderValue = 2.0;
  double x = 3.0;
  double result;

  // Start Python interpreter
  Py_Initialize();

  sys  = PyImport_ImportModule("sys");
  path = PyObject_GetAttrString(sys,"path");
  PyList_Append(path, PyString_FromString("."));

  pModuleName = PyString_FromString((char*)moduleName.c_str());
  pClassName  = PyString_FromString((char*)className.c_str());
  pMethodName = PyString_FromString((char*)methodName.c_str());

  pAdderValue = PyFloat_FromDouble(adderValue);
  pX = PyFloat_FromDouble(x);

  // Import the module
  pModule = PyImport_Import(pModuleName);

  if( PyObject_HasAttr( pModule, pClassName ) ) {

    pClass = PyObject_GetAttr( pModule, pClassName );

    pInitArgs = PyTuple_Pack(1,pAdderValue);
    Py_DECREF( pAdderValue );

    // Create an instance of the Adder class defined in ClassDef.py
    pAdder = PyObject_CallObject( pClass, pInitArgs );
   
    pResult = PyObject_CallMethodObjArgs( pAdder, pMethodName, pX, NULL );      
     
    result = PyFloat_AsDouble(pResult);

    std::cout << "a = " << className << "(" << adderValue << ")" << std::endl;
    std::cout << "a." << methodName << "(" << x << ")" << std::endl;
    std::cout << "result = " << result << std::endl; 

  }

  // Undo initializations 
  Py_Finalize();

  return 0;
}
