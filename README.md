# SWIG wrappers for the Community Sensor Model

This repository contains SWIG wrappers for the CSM. The wrappers are currently
only be created for Python, though many other languages can be supported.

## Building, Installing, and Testing
- Ensure that the library is installed
- (Optional) Install the USGS CSM_CameraModel libraries to ensure that this
  wrapper is able to do something.
- mkdir build
- cd build
- cmake .. 
- cmake --build .
- cd python
- python setup.py install
- ctest

## Usage
The CSM is designed so that plugins with a common insterface are dynamically
loaded.  This wrapper is designed to continue that philosophy. Therefore,
loading an implementation of the interface is a little different than a
standard python import.

```python
import csmapi
import ctypes

# THis dynamically registers this plugin with the CSM API.
lib = ctypes.CDLL('path_to_the_csm_plugin_library.so')

# The two methods that are implemented are getList and findPlugin
plugin_list = csmapi.Plugin.getList()

# Should be greater than 0
print(len(plugin_list))
```

## Issues
The dynamic cast from the model up the inheretance tree to RasterGM has not
yet been implemented.  The test_functional.py (in tests) demonstrates how the
returned object is a pointer to a Model. This needs to be dynamically cast (I
think with a %factory directive) to the RasterGM class that contains the full
suite of methods.


```
