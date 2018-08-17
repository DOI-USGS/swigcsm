# Include python
include(FindPythonAnaconda.cmake)
include_directories(${PYTHON_INCLUDE_DIR})

set(CMAKE_SWIG_FLAGS "")
set(CMAKE_SWIG_OUTDIR csmapi)
set_source_files_properties(../csmapi.i 
                            PROPERTIES CPLUSPLUS ON)

#Find dependencies
find_path(CSM_INCLUDE_DIR NAMES csm.h 
                          PATH_SUFFIXES csm 
                          PATHS ${PYTHON_INCLUDE_DIR}/../)
find_library(CSM_LIBRARY NAMES csmapi)
message("-- Found CSM Include: ${CSM_INCLUDE_DIR}")
message("-- Found CSM Lib: ${CSM_LIBRARY}")

include_directories(${CSM_INCLUDE_DIR})

# Add and link 
swig_add_library(csmapi
                 LANGUAGE python 
                 SOURCES ../csmapi.i)
set_target_properties(_csmapi PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SWIG_OUTDIR})
swig_link_libraries(csmapi ${CSM_LIBRARY} ${PYTHON_LIBRARY})

# Build out a standard directory structure
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)

# Move the static files to move
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in
               ${CMAKE_CURRENT_BINARY_DIR}/setup.py) 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/__init__.py
               ${CMAKE_CURRENT_BINARY_DIR}/csmapi/__init__.py)