%module(package="csmapi") isd
%{
    #include "Isd.h"
%}

%ignore IMAGE_ID_PARAM;
%ignore IMAGE_ID_PARAM;      
%ignore IMAGE_INDEX_PARAM;
%ignore LOGICAL_INDEX_PARAM;
%ignore MODEL_NAME_PARAM;

%include <std_string.i>

%pythoncode %{
    import json    
%}

%include "Isd.h"
%extend csm::Isd {
    %pythoncode %{
        import json
        import numpy as np
        @classmethod
        def loads(cls, stream):
            isd = cls()
            if not isinstance(stream, dict):
                stream = json.loads(stream)
            for k, v in stream.items():
                if isinstance(v, list):
                    for i in v:
                        isd.addParam(k, str(i))
                isd.addParam(k, str(v))
            return isd

        @classmethod
        def load(cls, fp):
            return cls.loads(fp.read())
    %}
}