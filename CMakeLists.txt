cmake_minimum_required(VERSION 3.16)

# Options. Turn on with 'cmake -Dtest=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

# set the project name and version
project(ray_tracer_challenge VERSION 1.0)

# specify the C++ standard
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the name of the chapter to be built
set(MAIN_FILE_NAME "ch10.3.cpp")

# add subdirectories
add_subdirectory(challenges)
add_subdirectory(src)


################################
# Testing
################################
if (test)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  enable_testing()

  include_directories("${CMAKE_SOURCE_DIR}/src")
  add_executable(
    test.out
    tests/all_tests.cpp
    tests/ch1_tuple_tests.cpp
    tests/ch2_canvas_tests.cpp
    tests/ch3_matrix_tests.cpp
    tests/ch4_transformation_tests.cpp
    tests/ch5_ray_tests.cpp
    tests/ch6_shading_tests.cpp
    tests/ch7_world_tests.cpp
    tests/ch8_shadow_tests.cpp
    tests/ch9_shapes_tests.cpp
    tests/ch10_patterns_tests.cpp
  )

  target_link_libraries(
    test.out
    GTest::gmock_main
  )

  target_link_libraries(
    test.out
    src
  )

  include(GoogleTest)
  gtest_discover_tests(test.out)
endif()