# Building on Windows

### LLVM Release 9.0 (Clang, lld, libc++) for Windows x64

Debug builds: batch file [build_x64_debug.bat](./build_x64_debug.bat)  
Release builds: batch file [build_x64_release.bat](./build_x64_release.bat)  
The exact command-lines are in the .bat files. They need the LLVM binaries in PATH and the library path of **libc++** (*c++.dll*) is given. 
For building libc++ on Windows, see the other [project](../../C++_perusteet_2008/KingsPath_EclipseCDT_Windows).

### Visual Studio Community 2019

The solution file is in the folder **Visual_Studio_2019**.

### MSYS2 / mingw-w64 GCC 9.2.0

Look in the folder **MSYS2**.

