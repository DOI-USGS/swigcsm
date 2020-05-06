%module(package="csmapi") geometricmodel
%include <std_vector.i>
%template(VecInt) std::vector<int>;
%{
    #include "GeometricModel.h"
%}

%import model.i
%include GeometricModel.h
