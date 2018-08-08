%module(package="csmapi") rastergm
%{
    #include "RasterGM.h"
%}

%ignore CSM_RASTER_FAMILY;

%import model.i
%import geometricmodel.i
%import csm.i
%include RasterGM.h
