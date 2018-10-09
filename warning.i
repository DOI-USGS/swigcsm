%module(package="csmapi") warning
%{
    #include "Warning.h"
%}

%include "std_list.i"
%include Warning.h

%template(WarningList) std::list<csm::Warning>;