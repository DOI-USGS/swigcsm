%module(package="csmapi") ellipsoid
%{
    #include "Ellipsoid.h"
%}

%ignore CSM_WGS84_SEMI_MAJOR_AXIS;
%ignore CSM_WGS84_SEMI_MINOR_AXIS;

%include "Ellipsoid.h"
