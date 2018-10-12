import csmapi
import pytest

# Loads a CSM compliant lib defined by --lib= in the pytest invocation
def test_loadlib(loadlib):
    assert loadlib is not None

@pytest.fixture
def model():
    plugin = csmapi.Plugin
    pl = plugin.findPlugin('PluginFixture')
    return pl  

def test_plugin_size():
    
    plugin_list = csmapi.Plugin.getList()
    assert len(plugin_list) == 1

def test_plugin_name():
    plugin = csmapi.Plugin
    pl = plugin.getList()[0]
    plugin_name = pl.getPluginName()
    assert plugin_name == "PluginFixture"

def test_model_getNumModels(model):
    assert model.getNumModels() == 1

def test_model_getModelName(model):
    assert model.getModelName(0) == 'FixtureSensorModel'