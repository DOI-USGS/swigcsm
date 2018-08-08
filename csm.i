%module(package="csmapi") csm
%{
    #include "csm.h"
%}

%ignore CSM_UNKNOWN;
%ignore CSM_SENSOR_TYPE_UNKNOWN;     
%ignore CSM_SENSOR_TYPE_EO;            
%ignore CSM_SENSOR_TYPE_IR;            
%ignore CSM_SENSOR_TYPE_MWIR;          
%ignore CSM_SENSOR_TYPE_LWIR;          
%ignore CSM_SENSOR_TYPE_SAR;           
%ignore CSM_SENSOR_TYPE_EOIRSC;        
%ignore CSM_SENSOR_MODE_UNKNOWN;       
%ignore CSM_SENSOR_MODE_FRAME;        
%ignore CSM_SENSOR_MODE_PULSE;         
%ignore CSM_SENSOR_MODE_PB;            
%ignore CSM_SENSOR_MODE_WB;            
%ignore CSM_SENSOR_MODE_SPOT;          
%ignore CSM_SENSOR_MODE_STRIP;         
%ignore CSM_SENSOR_MODE_SCAN;          
%ignore CSM_SENSOR_MODE_VIDEO;         
%ignore CSM_SENSOR_MODE_BODY_POINTING; 

%include "csm.h"
