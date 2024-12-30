# Create an executable from an executable main function
# add_executable([exec_name] [chapter_file])
add_executable(challenge.out ${MAIN_FILE_NAME})
# Link the executable to a library
# target_link_libraries([exec_name] [library_name])
target_link_libraries(challenge.out raytracer_lib)
