## H62PEP Computing Project

# Group 38 - modelViewer

[![Build Status](https://travis-ci.com/So-Lok/2019_Group_38.svg?token=Dw1Hp9TfHVSn6gfad5JW&branch=master)]

# Doxygen Documentation
https://so-lok.github.io/2019_Group_38/html

## (MARKER) PLEASE READ ON FOR FEATURES AND THINGS TO TAKE NOTE OF 

## Running Semester 2 program ~~05/03~~ 3rd May update 

Navgigate to the modelViewer directory, create a build folder and in the build folder create generate the files with the following code.
The following may differ depending on the location of your vtk and qt files.

```
set PATH=%PATH%;C:\VTK\MSVC2017_64\bin;C:\Qt\5.12.5\msvc2017_64\bin // ignore this line if you have already setup the path
cmake -DCMAKE_PREFIX_PATH="C:\VTK\MSVC2017_64\bin;C:\Qt\5.12.5\msvc2017_64\bin" -G"Visual Studio 16 2019" ..
// use the compiler for the version of visual studio which you have installed.

// building the code
msbuild modelViewer.sln

// if build is successful 
Debug\modelViewer.exe


```

# Building the installer/package 

build the code like above.

If you are using Visual studio, you can open the modelViewer.sln and build the PACKAGE on the right. make sure you are in Debug mode, though this should be default. 

This will create an installer in the build folder.

## Features

# Open/import STL files and .mod files from semester 1

# Filters
- Clip filter, clipping plane can be set with edit filters window. The default could clip an entire model so be sure to change the settings in edit filter if it does.
- Shrink filter, shrinks the model's individual cells by a scale factor which can be changed in edit filters

Can only be used one at a time
compatible with wireframe, graphical changes such as colour, lighting, opacity

# Widgets
- box widget, allows the user to transform the model, in widgets tab  
- axis widget, displays axis on screen, in widgets tab
- Ruler widget on mainwindow
# Colour 
The colour of the model and the background can be changed
# Statistics 
Shows the number of cells and vertices/ points of each model
# Other
- Wireframe representation
- Opacity slider
- Light intensity slider and toggleable light
# Models are installed alongside the program in models folder in bin

# Please take note, some known issues
- at start up if no model has been imported in the program will crash if the user attempts to apply a filter to nothing. 
- box widget will reset if enabled after disabling.
- box widget will make the models retain the transform even after importing new model (permanent tranform to models)
  A restart of the program fixes this
- axis widget has some lighting issues
- some problems with mixing widgets with filters
- warning about window geometry when using colour buttons, has no effect on actual program however
- there may be other issues which have not been found yet or ignored as not significant enough to affect the program massively

## GROUP MEMBERS PLEASE READ

Please comment all of the features that you make using doxygen style in the .h file. As we are short on time I will not have any time to comment on your code in addition to the code in the main repo already. 

Furthermore, please make sure that you are up to date with the main repo before applying for a pull request as I will not merge it if it is not.

In addition to this, could you try to solve any conflicts with the main repo code on your side as going through multiple files and solving conflicts can take a lot of time especially since some of you are in a different time zone.

Therefore, if your code is not up to date, not commented or has a lot of conflicts I will **NOT** merge the pull so that the repo can be kept consistent and bug free.  

Thanks 

So-Lok





## How to run Semester 1 program

Navigate to the root directory in cmd and use the following commands to create a build folder
```
mkdir build
cd build
```
# Using minGW

Whilst in the empty build file do the following 

```
cmake -G "MinGW Makefiles" ..
mingw32-make
modelTest.exe
```

# Using Visual Studio Compiler

Please note that depending on the version of Visual Studio you are using the code may differ slightly.
You can use ```cmake --help``` to find the **generator** code that you need.

IMPORTANT: Make sure you have started up the Visual Stuido Environment for this to work
To do this you will need to navigate to the vcvarsall.bat file and run the .bat through cmd, using amd64 after the path.
The path should be similar to the following

```C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build```

Running the code

```"C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64```

Whilst in the empty build folder do the following

```
cmake -G "Visual Studio 16 2019" ..
msbuild model.sln
Debug\modelTest.exe
```




 
