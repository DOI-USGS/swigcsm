import csmapi
import pytest

# Loads a CSM compliant lib defined by --lib= in the pytest invocation
def test_loadlib(loadlib):
    assert loadlib is not None


@pytest.fixture
def plugin_pool():
    """
    This fixture is the umbrella plugin object that
    stores all of the currently loaded plugin.
    """
    return csmapi.Plugin

@pytest.fixture
def plugin(plugin_pool):
    """
    This fixture is a single loaded plugin accessed
    from the plugin pool. From this plugin a model 
    could be loaded.
    """
    return plugin_pool.findPlugin('PluginFixture')

def test_plugin_size(plugin_pool):
    plugin_list = plugin_pool.getList()
    assert len(plugin_list) == 1

def test_plugin_list_type(plugin_pool):
    plugin_list = plugin_pool.getList()
    assert isinstance(plugin_list, csmapi.PluginList)

def test_plugin_name(plugin_pool):
    pl = plugin_pool.getList()[0]
    plugin_name = pl.getPluginName()
    assert plugin_name == "PluginFixture"

def test_model_getNumModels(plugin):
    assert plugin.getNumModels() == 1

def test_model_getModelName(plugin):
    assert plugin.getModelName(0) == 'FixtureSensorModel'
