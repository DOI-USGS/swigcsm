%module(package="csmapi") plugin
%{
    #include "Plugin.h"
%}

%include <std_string.i>
%include <std_list.i>
%include typemaps.i
%include Plugin.h




%template(PluginList) std::list<const csm::Plugin*>;

%{
    namespace swig {
    template <> struct traits<csm::Plugin>
    {
        typedef pointer_category category;
        static const char* type_name()
        {
            return "Plugin";
        }
    };
    }
%}


