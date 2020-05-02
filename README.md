## H62PEP Computing Project

# Group 38

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

## Running Semester 2 program 05/03

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





 
