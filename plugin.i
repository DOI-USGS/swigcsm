%module(package="csmapi") plugin
%{
    #include "Plugin.h"

%}

%include <std_string.i>
%include <std_list.i>
%include Model.h


%apply SWIGTYPE *DYNAMIC { csm::Model * };

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


// A general purpose function for dynamic casting of a Model *
%{
static swig_type_info *
Model_dynamic(void **ptr) {
   csm::RasterGM *b;
   b = dynamic_cast<csm::RasterGM *>((csm::Model *) *ptr);
   if (b) {
      *ptr = (void *) b;
      return SWIGTYPE_p_csm__RasterGM;
   }
   return 0;
}
%}

// Register the above casting function
DYNAMIC_CAST(SWIGTYPE_p_csm__Model, Model_dynamic);
