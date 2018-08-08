import ctypes
from distutils import dir_util
import json
import os

import pytest

import csmapi

# Load a plugin with CSM compliant sensors
lib = ctypes.CDLL('/data/big/github/CSM-CameraModel/build/libusgscsm.so')

@pytest.fixture
def datadir(tmpdir, request):
    '''
    Fixture responsible for searching a folder with the same name of test
    module and, if available, moving all contents to a temporary directory so
    tests can use them freely.
    '''
    filename = request.module.__file__
    test_dir, _ = os.path.splitext(filename)

    if os.path.isdir(test_dir):
        dir_util.copy_tree(test_dir, str(tmpdir))
    return tmpdir

@pytest.fixture
def isd(datadir):
    with open(datadir.join('simpleFramerISD.json')) as f:
        i = csmapi.Isd.load(f)
    return i
    

@pytest.fixture
def plugin():
    plugin = csmapi.Plugin.findPlugin('UsgsAstroFramePluginCSM')
    return plugin 

def test_isd_to_model_to_ground(isd, plugin):
    model_name = "USGS_ASTRO_FRAME_SENSOR_MODEL"
    assert plugin.canModelBeConstructedFromISD(isd, model_name)
    assert plugin.canISDBeConvertedToModelState(isd, model_name)
    
    model = plugin.constructModelFromISD(isd, model_name)
    assert model.getVersion().version() == '0.1.0'
    print(dir(model))
    assert False
    