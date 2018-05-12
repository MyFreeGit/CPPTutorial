cmake_minimum_required(VERSION 3.4)
project(CPPTutorial)

#include_directories(inc)

if(NOT UT_TEST)
    add_executable(CPPTutorial CPPTutorial.cpp)
endif()
