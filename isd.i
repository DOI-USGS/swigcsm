%module(package="csmapi") isd
%{
    #include "Isd.h"
%}

%ignore IMAGE_ID_PARAM;
%ignore IMAGE_ID_PARAM;      
%ignore IMAGE_INDEX_PARAM;
%ignore LOGICAL_INDEX_PARAM;
%ignore MODEL_NAME_PARAM;

%include <std_string.i>

%include "Isd.h"