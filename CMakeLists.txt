cmake_minimum_required(VERSION 3.0)
project(PyCallClass)

# I needed to specify the 2.7 as otherwise CMake would use 3.5
# which seems to not support PyString_FromString
find_package( PythonLibs 2.7 REQUIRED )
add_executable(PyCallClass pycallclass.cpp)

include_directories(${PYTHON_INCLUDE_DIR})

# This has to be after the add_executable
target_link_libraries(PyCallClass ${PYTHON_LIBRARY})

