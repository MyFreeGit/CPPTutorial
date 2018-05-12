cmake_minimum_required(VERSION 3.4)
project(CPPTutorial)

#include_directories(inc)

if(UT_TEST)
  find_package(GTest)

  if(GTEST_FOUND)
    add_executable(CPPTutorialTest ${TESTCASE_SRC} ${SOURCES})

    target_link_libraries(CPPTutorialTest PUBLIC
      ${GTEST_BOTH_LIBRARIES})

    target_include_directories(CPPTutorialTest PUBLIC
      ${GTEST_INCLUDE_DIRS} # doesn't do anything on linux
    )
  
  endif()
endif()