cmake_minimum_required(VERSION 3.4)
project(CPPTutorial)

#include_directories(inc)

if(UT_TEST)
    find_package(GTest)

    if(GTEST_FOUND)
        add_executable(CPPTutorialTest ${TESTCASE_SRC} ${SOURCES})
        if (CMAKE_SYSTEM_NAME MATCHES "MINGW.*" OR CMAKE_SYSTEM_NAME MATCHES "MSYS.*")
            Message("Link without pthread")
            # MinGW doesn't support the pthread library
            target_link_libraries(CPPTutorialTest PUBLIC
                ${GTEST_BOTH_LIBRARIES})
        else()
            target_link_libraries(CPPTutorialTest PUBLIC
                ${GTEST_BOTH_LIBRARIES} pthread)
        endif()
        target_include_directories(CPPTutorialTest PUBLIC
            ${GTEST_INCLUDE_DIRS})
  
  endif()
endif()