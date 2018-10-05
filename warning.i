%module(package="csmapi") warning
%{
    #include "Warning.h"
%}

%include "std_list.i"
%include Warning.h
%template(Warning_List) std::list<csm::Warning>;