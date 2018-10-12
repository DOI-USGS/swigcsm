from distutils import dir_util
import json
import os

import csmapi
import pytest


# Loads a CSM compliant lib defined by --lib= in the pytest invocation
def test_loadlib(loadlib):
    assert loadlib is not None


@pytest.fixture
def isd():
    return csmapi.Isd()

@pytest.fixture
def plugin():
    plugin = csmapi.Plugin.findPlugin('PluginFixture')
    return plugin 

@pytest.fixture
def model(isd, plugin):
    model_name = "FixtureSensorModel"
    return plugin.constructModelFromISD(isd, model_name)


def test_instantiate_model(isd, plugin):
    model_name = "FixtureSensorModel"
    assert plugin.canModelBeConstructedFromISD(isd, model_name)
    assert plugin.canISDBeConvertedToModelState(isd, model_name)

def test_image_to_ground(model):
    assert hasattr(model, 'imageToGround')
    image_coord = csmapi.ImageCoord()
    gnd = model.imageToGround(image_coord, 0)
    assert gnd.x == 0
    assert gnd.y == 0
    assert gnd.z == 0

def test_model_version(model):
    assert model.getVersion().version() == '0.1.0'

def test_bad_get_image_time(model):
    img_coord = csmapi.ImageCoord(-1,-1)
    with pytest.raises(RuntimeError) as r:
        model.getImageTime(img_coord)
    
def test_ground_to_image(model):
    assert hasattr(model, 'groundToImage')
    gnd_coord = csmapi.EcefCoord(0,0,0)
    img = model.groundToImage(gnd_coord, 0)
    assert img.samp == 0
    assert img.line == 0

def test_bad_ground_to_image(model):
    gnd_coord = csmapi.EcefCoord(-1, -1, 0)
    with pytest.warns(Warning) as w:
        img = model.groundToImage(gnd_coord, 0)
        assert len(w) == 1
    