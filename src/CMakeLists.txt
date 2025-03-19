cmake_minimum_required(VERSION 3.16)

project(RayTracer)

find_package(OpenMP REQUIRED)
find_package(OpenGL REQUIRED)

set(
    SOURCES
    canvas.cpp
    tuple.cpp
    color.cpp
    matrix.cpp
    transform.cpp
    ray.cpp
    intersection.cpp
    intersections.cpp
    lights.cpp
    material.cpp
    world.cpp
    computation.cpp
    camera.cpp
    obj_loader.cpp
    # patterns folder
    patterns/pattern.cpp
    # shapes folder
    shapes/shape.cpp
    shapes/sphere.cpp
    shapes/plane.cpp
    shapes/cube.cpp
    shapes/cylinder.cpp
    shapes/cone.cpp
    shapes/group.cpp
    shapes/triangle.cpp
)

add_library(raytracer_lib ${SOURCES})

message("Raytracer current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")
# Link OpenMP libraries
if(OpenMP_CXX_FOUND)
    target_link_libraries(raytracer_lib PUBLIC OpenMP::OpenMP_CXX)
endif()
target_include_directories(
    raytracer_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/shapes
)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${EIGEN_INCLUDE_DIR})

target_link_libraries(raytracer_lib PUBLIC Eigen3::Eigen)
