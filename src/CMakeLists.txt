add_library(src canvas.cpp tuple.cpp)
# add_library(src tuple.cpp)
 
message("Raytracer current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")
 
target_include_directories( src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})