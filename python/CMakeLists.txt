set(CMAKE_SWIG_FLAGS "")
list(APPEND CMAKE_SWIG_FLAGS "-py3;-DPY3")
set(CMAKE_SWIG_OUTDIR csmapi)
set_source_files_properties(../csmapi.i
                            PROPERTIES CPLUSPLUS ON)

#Find dependencies
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_path(CSM_INCLUDE_DIR NAMES csm.h
                          PATH_SUFFIXES csm)
find_library(CSM_LIBRARY NAMES csmapi)
message("-- Found CSM Include: ${CSM_INCLUDE_DIR}")
message("-- Found CSM Lib: ${CSM_LIBRARY}")
include_directories(${CSM_INCLUDE_DIR})

# Add and link
swig_add_library(csmapi
                 LANGUAGE python
                 SOURCES ../csmapi.i)
swig_link_libraries(csmapi ${CSM_LIBRARY} Python3::Python)
set_property(TARGET csmapi PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)

set_target_properties(csmapi PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SWIG_OUTDIR})

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

if (APPLE)
     set_target_properties(csmapi PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
endif()

# Build out a standard directory structure
# file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)

# Move the static files to move
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in
               ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/__init__.py
               ${CMAKE_CURRENT_BINARY_DIR}/csmapi/__init__.py
               COPYONLY)

# Setup the tests
enable_testing()
add_test(NAME python-wrapper-tests
        COMMAND python -m pytest ${CMAKE_SOURCE_DIR}/python/tests --lib ${CMAKE_CURRENT_BINARY_DIR}/../fixture/libfixturecsm${CMAKE_SHARED_LIBRARY_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
