add_library(
    src
    canvas.cpp
    tuple.cpp
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
)
 
message("Raytracer current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")
 
target_include_directories( src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})