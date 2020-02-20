# Purpose

Experimenting C++ compilation and linking with the MSYS2/mingw-w64 toolchain on Windows. 

# Setup

* Windows 7 SP1 64 bit
* [MSYS2 x86_64](https://www.msys2.org/)  
   * packages base, base-devel, gcc, mingw-w64-x86_64-toolchain

* Environment: PATH  
   * mingw-w64 in path e.g C:\msys64\mingw64\bin
   * GCC 9.2.0, check from Windows Command Prompt: ```g++ -v```

# Using the command-line

Debug: 
```
> build_debug.bat
```
Release:
```
> build_release.bat
```
The exact command-line is in the .bat files.
