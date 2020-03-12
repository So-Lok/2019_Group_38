# calc_cmake/CMakeLists.txt
cmake_minimum_required( VERSION 3.16 )

project( material )

# This project contains a library

add_library( material Material.cpp )


add_executable( testmat main.cpp )
# The executable uses the library

target_link_libraries( testmat material )
