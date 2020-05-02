cmake_minimum_required( VERSION 2.8 )

foreach(p
    CMP0071 # 3.10, let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()


PROJECT( modelViewer )

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.

set( CMAKE_INCLUDE_CURRENT_DIR ON )

# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

# cpack config
#include(InstallRequiredSystemLibraries)

# choose cpack generator for windows
IF(WIN32)
  set(CPACK_GENERATOR "NSIS")
endif()
include(CPack)


# Find the Qt widgets package. This locates the relevant include and
# lib directories, and the necessary static libraries for linking.
find_package( Qt5Widgets )

# set UIs to be used
set( UIS mainwindow.ui optionsfilter.ui)
qt5_wrap_ui( UI_Srcs ${UIS} )

# link icons
set( ICONS Icons/icons.qrc )
qt5_add_resources( QRC_Srcs ${ICONS} )


# Also link to VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

####################################
# add all source files

include_directories( modelReader/src )
include_directories( modelReader/inc )

# Define the executable output and its sources
add_executable( modelViewer MACOSX_BUNDLE
                main.cpp
                mainwindow.cpp mainwindow.h
                optionsfilter.cpp optionsfilter.h
                mainwindow.ui optionsfilter.ui
                modelReader/src/model.cpp modelReader/inc/model.h
                modelReader/src/cell.cpp modelReader/inc/cell.h
                modelReader/src/vectorClass.cpp modelReader/inc/vectorClass.h
                modelReader/src/material.cpp modelReader/inc/material.h
                ${UI_Srcs}
                ${QRC_Srcs}
                )


# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( modelViewer Qt5::Widgets )
# Tell CMake that the executable depends on the VTK libraries

target_link_libraries( modelViewer ${VTK_LIBRARIES} )

#########################################################
# Installation
# tell cmake to install debug libraries and ucrt libraries, program requires them to run
set( CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
set( CMAKE_INSTALL_DEBUG_LIBRARIES TRUE)
include(InstallRequiredSystemLibraries)

install(TARGETS modelViewer
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib/static)

# get location of qt and vtk files, add to a list called LIBS_PATH
# and then install all files from those locations
get_target_property(QT_CORE_LIB Qt5::Core LOCATION)
get_filename_component(QT_RUNTIME_DIR "${QT_CORE_LIB}" DIRECTORY)
list(APPEND LIBS_PATH "${QT_RUNTIME_DIR}")

list(APPEND LIBS_PATH "${VTK_RUNTIME_LIBRARY_DIRS}")
# install using fixup bundle so that only required vtk and qt libraries are downloaded
install(CODE
"
    include(BundleUtilities)
    fixup_bundle(\"\${CMAKE_INSTALL_PREFIX}/bin/modelViewer.exe\" \"\" \"${LIBS_PATH}\")
"
DESTINATION .
COMPONENT RUNTIME
)
# install qt5 plugins , is required to run
install(FILES  $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> 
		DESTINATION bin/platforms)
# install the models files both .stl and .mod
install(DIRECTORY models 
		DESTINATION bin)
