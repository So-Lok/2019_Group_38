cmake_minimum_required( VERSION 2.8 )


project( modelViewerTests)
include(CTest)


set( CMAKE_INCLUDE_CURRENT_DIR ON )

include_directories( modelViewer/tests )
include_directories( modelViewer/modelReader/src )
include_directories( modelViewer/modelReader/inc )
include_directories( modelFiles )

add_library(modelLib
            modelViewer/modelReader/src/model.cpp modelViewer/modelReader/inc/model.h
            modelViewer/modelReader/src/cell.cpp modelViewer/modelReader/inc/cell.h
            modelViewer/modelReader/src/vectorClass.cpp modelViewer/modelReader/inc/vectorClass.h
            modelViewer/modelReader/src/material.cpp modelViewer/modelReader/inc/material.h
            )

add_executable(testModel modelViewer/tests/modelTest.cpp)
add_executable(testVector modelViewer/tests/vectorTest.cpp)

target_link_libraries(testModel modelLib)
target_link_libraries(testVector modelLib)

add_test(testModel testModel)
add_test(testVector testVector) 

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/modelFiles/ExampleModel1.mod	
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})