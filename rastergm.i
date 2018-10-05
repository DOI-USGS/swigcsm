%module(package="csmapi") rastergm
%{
    #include "RasterGM.h"
%}

%ignore CSM_RASTER_FAMILY;
%include exception.i
%include warning.i
%import warning.i
%exception {
    try {
        $action
    } catch (const std::exception &e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch (const csm::Warning &w) {
        // Converts the CSM warning into an error
        SWIG_exception(0, "This should be a warning, not a runtime error.");
    }
} 

%import warning.i
%import model.i
%import geometricmodel.i
%import csm.i

%include RasterGM.h
