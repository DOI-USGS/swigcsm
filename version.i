%module(package="csmapi") version
%{
    #include "Version.h"
%}

%include <std_string.i>

%rename ("$ignore", fullname=1) csm::Version::print;
%ignore operator<<;
%include "Version.h"


