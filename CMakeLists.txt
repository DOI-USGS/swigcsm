cmake_minimum_required(VERSION 3.15)

project(swigcsm VERSION 1.0.1 DESCRIPTION "SWIG wrappers for the Community Sensor Model API")

find_package(SWIG REQUIRED)
include(UseSWIG)

add_subdirectory(python)
add_subdirectory(fixture)