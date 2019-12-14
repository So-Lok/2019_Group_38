## H62PEP Computing Project

# Group 38  

## How to run the program

Navigate to the root directory in cmd and use the following commands to create a build folder
```
mkdir build
cd build
```
# Using minGW

Whilst in the empty build file do the following 

```
cmake -G "MinGW Makefiles" ..
mingw-make
modelTest.exe
```

# Using Visual Studio Compiler

Please note that depending on the version of Visual Studio you are using the code may differ slightly.
You can use ```cmake --help``` to find the *generator* code that you need.

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



 
