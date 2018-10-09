%module(package="csmapi") rastergm
%{
    #include "Warning.h"
    #include "RasterGM.h"
%}

%ignore CSM_RASTER_FAMILY;
%include exception.i
%include warning.i
%exception {
    try {
        $action
    } catch (const std::exception &e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch (const csm::Warning &e) {
        // Converts the CSM warning into an error
        PyErr_WarnEx(PyExc_UserWarning, e.getMessage().c_str(), 0);
    }
} 
%import model.i
%import geometricmodel.i
%import csm.i

%include RasterGM.h