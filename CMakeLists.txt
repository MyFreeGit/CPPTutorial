cmake_minimum_required(VERSION 3.4)
project(CPPTutorial)

option(UT_TEST "By default, not compiling UT test" FALSE)

include_directories(inc)
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE TESTCASE_SRC ut/*.cpp)

######################################################################
# Here I use a option to control the CMake to build test or executable
# That can save time when only build one target not both.
######################################################################
if(UT_TEST)
    add_subdirectory(ut)
else()
    add_subdirectory(src)
endif()

#######################################################################
# The code in comments are another way to build the executable and the
# unit test at same time. But the generated makefile has an test target
# to run the unit_test
#######################################################################
#add_executable(CPPTutorial ${SOURCES} CPPTutorial.cpp)
#enable_testing()

#find_package(GTest)
#if(GTEST_FOUND)
#  add_executable(CPPTutorialTest ${TESTCASE_SRC} ${SOURCES})

#  target_link_libraries(CPPTutorialTest PUBLIC
#      ${GTEST_BOTH_LIBRARIES})

#  target_include_directories(CPPTutorialTest PUBLIC
#      ${GTEST_INCLUDE_DIRS})

#  add_test(CPPTutorialTest CPPTutorialTest)
#endif()


