add_library(
    src
    canvas.cpp
    tuple.cpp
    matrix.cpp
    transform.cpp
    ray.cpp
    sphere.cpp
    intersection.cpp
    lights.cpp
)
 
message("Raytracer current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")
 
target_include_directories( src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})