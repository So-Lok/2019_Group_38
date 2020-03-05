# specify the minimum required cmake version
cmake_minimum_required( VERSION 2.8 )

# Name of the project
project( model )



# include directories to look into

include_directories( inc )
include_directories( src )
include_directories( modelFiles )

# add a library (model.cpp)
# library name and then the file to make into a library
add_library( model src/model.cpp inc/model.h 
 		   src/cell.cpp inc/cell.h
		   src/vectorClass.cpp inc/vectorClass.h
		   src/material.cpp inc/material.h)

# create the execuatable using the test main

add_executable( modelTest src/main.cpp )

target_link_libraries( modelTest model )


# copy example model files to the build folder so that executable 
# can use the files

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/modelFiles/ExampleModel1.mod
	  ${CMAKE_CURRENT_SOURCE_DIR}/modelFiles/ExampleModel2.mod
	  ${CMAKE_CURRENT_SOURCE_DIR}/modelFiles/ExampleModel3.mod	
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



