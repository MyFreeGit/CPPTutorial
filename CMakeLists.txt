cmake_minimum_required(VERSION 3.4)
project(CPPTutorial)

option(UT_TEST "By default, not compiling UT test" FALSE)

include_directories(inc)
add_subdirectory(src)

if(UT_TEST)
    add_subdirectory(ut)
endif()
