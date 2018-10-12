find_path(CSM_INCLUDE_DIR NAMES "csm.h"
            PATH_SUFFIXES "csm" 
            PATHS $ENV{CONDA_PREFIX}/include/)
find_library(CSM_LIBRARY csmapi PATHS $ENV{CONDA_PREFIX}/lib)

add_library(fixturecsm SHARED
    model.cpp
    plugin.cpp)

target_include_directories(fixturecsm
                           PRIVATE
                           ${CSM_INCLUDE_DIR}
)

target_link_libraries(fixturecsm
                      ${CSM_LIBRARY})