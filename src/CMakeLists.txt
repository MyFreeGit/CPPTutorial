cmake_minimum_required(VERSION 3.4)
project(CPPTutorial)

if(NOT UT_TEST)
    add_executable(CPPTutorial ${SOURCES} ../CPPTutorial.cpp)
endif()
