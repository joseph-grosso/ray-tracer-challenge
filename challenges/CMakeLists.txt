# Create an executable from an executable main function
# add_executable([exec_name] [chapter_file])
add_executable(challenge.out ${MAIN_FILE_NAME})

# Add Eigen compiler flags
target_compile_definitions(challenge.out PRIVATE EIGEN_NO_DEBUG)

# Add the "-fno-math-errno" compiler flag
target_compile_options(challenge.out PRIVATE -fno-math-errno -march=native -DNDEBUG)

# Link the executable to a library
# target_link_libraries([exec_name] [library_name])
target_link_libraries(challenge.out raytracer_lib)
