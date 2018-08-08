import pytest

import csmapi
import ctypes

# Load a plugin with CSM compliant sensors
lib = ctypes.CDLL('/data/big/github/CSM-CameraModel/build/libusgscsm.so')

@pytest.fixture
def plugin():
    return csmapi.Plugin

@pytest.fixture
def model(plugin):
    pl = plugin.findPlugin('UsgsAstroFramePluginCSM')
    return pl  

def test_plugin_size(plugin):
    plugin_list = plugin.getList()
    assert len(plugin_list) == 2

@pytest.mark.parametrize("plugin, index, expected_name",
                         [(plugin(), 0, 'UsgsAstroFramePluginCSM'),
                          (plugin(), 1, 'USGS_ASTRO_LINE_SCANNER_PLUGIN')])
def test_plugin_name(plugin, index, expected_name):
    pl = plugin.getList()[index]
    plugin_name = pl.getPluginName()
    assert plugin_name == expected_name

def test_model_getNumModels(model):
    assert model.getNumModels() == 1

def test_model_getModelName(model):
    assert model.getModelName(0) == 'USGS_ASTRO_FRAME_SENSOR_MODEL'