from distutils import dir_util
import json
import os

import csmapi
import pytest


# Loads a CSM compliant lib defined by --lib= in the pytest invocation
def test_loadlib(loadlib):
    assert loadlib is not None

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
    plugin = csmapi.Plugin.findPlugin('PluginFixture')
    return plugin 
