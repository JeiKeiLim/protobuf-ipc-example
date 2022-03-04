cmake_minimum_required(VERSION 3.20.5)
project(
	cpluscplus_template  # Change this for your project name
	VERSION 0.1.0
)

option(test "Build all tests." OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -fPIC")
set(BUILD_SHARED_LIBS OFF)

include_directories( include )
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB SOURCES_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Remove executable cpp files
FOREACH(source_executable ${SOURCES_EXECUTABLE})
    list(REMOVE_ITEM SOURCES ${source_executable})
ENDFOREACH()

# Add executable list of executable cpp files
FOREACH(source_executable ${SOURCES_EXECUTABLE})
    get_filename_component(source_executable_name ${source_executable} NAME_WLE)
    set(executable_name ${PROJECT_NAME}-${source_executable_name})

    if (BUILD_SHARED_LIBS)
        add_library( ${PROJECT_NAME}_lib ${SOURCES} )

        add_executable( ${executable_name}
            ${source_executable}
        )
        target_link_libraries(${executable_name} ${PROJECT_NAME}_lib)
    else()
        add_executable( ${executable_name}
            ${SOURCES}
            ${source_executable}
        )
    endif()
ENDFOREACH()

if (test)
    set(TEST_NAME_BASE test-${PROJECT_NAME})

    add_subdirectory("/usr/src/gtest" ${CMAKE_BINARY_DIR}/gtest)
    include_directories(${GTEST_INCLUDE_DIRS})
	enable_testing()

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    # Auto adding unit test files starting with test_*.cpp
    FILE(GLOB UNITTEST_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_*.cpp")
    FOREACH(unittest_path ${UNITTEST_LIST})
        get_filename_component(unittest_name ${unittest_path} NAME_WLE)
        string(REPLACE "test_" "" unittest_name ${unittest_name})
        set(TEST_NAME ${TEST_NAME_BASE}-${unittest_name})

        message("Build Unit Test for ${unittest_path} with name of ${TEST_NAME}")

        if (BUILD_SHARED_LIBS)
            add_executable(${TEST_NAME} ${unittest_path})
            target_link_libraries(${TEST_NAME}
                gtest
                gtest_main
                ${PROJECT_NAME}_lib
                )
        else()
            add_executable(${TEST_NAME} ${unittest_path} ${SOURCES})
            target_link_libraries(${TEST_NAME}
                gtest
                gtest_main
            )
        endif()

        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    ENDFOREACH()
endif()
