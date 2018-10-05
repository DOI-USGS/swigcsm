import ctypes

import pytest

def pytest_addoption(parser):
    parser.addoption("--lib", action="store", default="libfixturecsm")

@pytest.fixture(scope='module')
def loadlib(request):
    libname =  request.config.getoption("--lib")
    return ctypes.CDLL(libname)