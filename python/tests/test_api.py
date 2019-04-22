import csmapi
import pytest

def test_loadlib(loadlib):
    assert loadlib is not None

def test_streamisd():
    print(dir(csmapi))
    stream = "The is a stream."
    isd = csmapi.BytestreamIsd(stream)
    assert stream == isd.data()

