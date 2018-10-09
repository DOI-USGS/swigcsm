%module(package="csmapi") rastergm
%{
    #include "RasterGM.h"
%}

%ignore CSM_RASTER_FAMILY;
%include exception.i
<<<<<<< HEAD
=======
%include warning.i
%import warning.i
>>>>>>> fd255992846472a9d84e82726cd39e16e276d0e3
%exception {
    try {
        $action
    } catch (const std::exception &e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
<<<<<<< HEAD
    }
} 

=======
    } catch (const csm::Warning &w) {
        // Converts the CSM warning into an error
        SWIG_exception(0, "This should be a warning, not a runtime error.");
    }
} 
>>>>>>> fd255992846472a9d84e82726cd39e16e276d0e3

%import warning.i
%import model.i
%import geometricmodel.i
%import csm.i

%include RasterGM.h
