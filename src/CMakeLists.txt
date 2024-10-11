add_library(
    src
    canvas.cpp
    tuple.cpp
    color.cpp
    matrix.cpp
    transform.cpp
    ray.cpp
    sphere.cpp
    intersection.cpp
    intersections.cpp
    lights.cpp
    material.cpp
    world.cpp
    computation.cpp
    camera.cpp
    shape.cpp
    plane.cpp
    stripe_pattern.cpp
)
 
message("Raytracer current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")
 
target_include_directories( src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})