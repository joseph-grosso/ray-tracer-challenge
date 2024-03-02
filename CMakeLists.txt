cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(ray_tracer_challenge VERSION 1.0)

# specify the C++ standard
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the name of the chapter to be built
set(MAIN_FILE_NAME "ch1.cpp")

# add subdirectories
add_subdirectory(challenges)
add_subdirectory(src)
