cmake_minimum_required(VERSION 3.4)
project(CPPTutorial)

#include_directories(inc)

if(UT_TEST)
	add_executable(CPPTutorialTest InterfaceCase.cpp ProtocolCase.cpp)
	target_link_libraries(CPPTutorialTest gtest gtest_main)
endif()