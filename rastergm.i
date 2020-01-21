%module(package="csmapi") rastergm
%include <std_pair.i>
%include <std_vector.i>
%template(VecDouble) std::vector<double>;
%template(SensorPartials) std::pair<double, double>;
%template(VecSensorPartials) std::vector<std::pair<double, double>>;

%{
    #include "RasterGM.h"
%}

%ignore CSM_RASTER_FAMILY;
%include exception.i
%exception {
    try {
        $action
    } catch (const std::exception &e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch (const csm::Warning &e) {
        PyErr_WarnEx(PyExc_UserWarning, e.getMessage().c_str(), 1);
    }
}
%import model.i
%import geometricmodel.i
%import csm.i

%include RasterGM.h
