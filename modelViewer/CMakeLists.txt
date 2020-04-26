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

# Find the Qt widgets package. This locates the relevant include and
# lib directories, and the necessary static libraries for linking.

find_package( Qt5Widgets )

set( UIS mainwindow.ui )
qt5_wrap_ui( UI_Srcs ${UIS} )

# link icons
set( ICONS Icons/icons.qrc )
qt5_add_resources( QRC_Srcs ${ICONS} )


# Also link to VTK

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

# Define the executable output and its sources

add_executable( modelViewer MACOSX_BUNDLE
                main.cpp mainwindow.cpp
                mainwindow.h
                mainwindow.ui
                ${UI_Srcs}
                ${QRC_Srcs}
                )

# Tell CMake that the executable depends on the Qt::Widget libraries.

target_link_libraries( modelViewer Qt5::Widgets )
# Tell CMake that the executable depends on the VTK libraries

target_link_libraries( modelViewer ${VTK_LIBRARIES} )
