# Include python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})


set(CMAKE_SWIG_FLAGS "")
set_source_files_properties(../csmapi.i 
                            PROPERTIES CPLUSPLUS ON)

find_path(CSM_INCLUDE_DIR NAMES csm.h 
                          PATH_SUFFIXES csm 
                          PATHS $ENV{CONDA_PREFIX}/include)
find_library(CSM_LIBRARY NAMES csmapi
                         PATHS $ENV{CONDA_PREFIX}/lib)

include_directories(${CSM_INCLUDE_DIR})

# Add swig module
swig_add_library(csmapi
                 LANGUAGE python 
                 SOURCES ../csmapi.i)


swig_link_libraries(csmapi ${CSM_LIBRARY} ${PYTHON_LIBRARIES})

# Files to install with Python
set(PYTHON_INSTALL_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/csmapi.py
    ${CMAKE_CURRENT_BINARY_DIR}/_csmapi.so)

# Configure setup.py and copy to output directory
set(SETUP_PY_IN ${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in)
set(SETUP_PY_OUT ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
configure_file(${SETUP_PY_IN} ${SETUP_PY_OUT})

# Declare install target for python
#install(TARGETS swig_example
#        COMMAND "${PYTHON_EXECUTABLE} setup.py"
#        COMPONENT swig-python)

# Install target to call setup.py
add_custom_target(install-python
        DEPENDS _csmapi
COMMAND python ${SETUP_PY_OUT} install)
