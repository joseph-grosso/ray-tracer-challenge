add_library(
    src
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
    # patterns folder
    patterns/pattern.cpp
    patterns/stripe_pattern.cpp
    # shapes folder
    shapes/shape.cpp
    shapes/sphere.cpp
    shapes/plane.cpp
)

message("Raytracer current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")
 
target_include_directories(
    src PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/shapes
)

