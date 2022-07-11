# Purpose

Experimenting C++ compilation and linkig with a pure LLVM toolchain on Windows. 
A pure Microsoft Visual C++ project is also [available](../VStudio_2019).

# Setup

* Windows 7 SP1 64 bit
* [Visual Studio Community 2019](https://visualstudio.microsoft.com/): Desktop development with C++ 
   * C++ Clang Compiler for Windows (9.0.0)
   * C++ Clang-cl for v142 build tools (x64/x86)
   * C++ CMake Tools for Windows
* [LLVM Release 9.0](http://releases.llvm.org/) (64 bit Clang compiler & tools for Windows x64)
* [Git](https://git-scm.com/) for Windows
* [LLVM Project sources](http://llvm.org/docs/GettingStarted.html#checkout)
* [Python 3.x](https://www.python.org/downloads/windows/)
* [Perl](http://strawberryperl.com/). (not sure whether it was needed)
* Environment: PATH, set by installation
   * Python e.g C:\Python38\Scripts\;C:\Python38\
   * Perl e.g C:\Perl-Strawberry\c\bin;C:\Perl-Strawberry\perl\site\bin;C:\Perl-Strawberry\perl\bin
   * Git e.g C:\Git\cmd
   * LLVM e.g C:\LLVM-9\bin

# Building libc++ 9.0 for Windows

Reference: [Building libc++](https://libcxx.llvm.org/docs/BuildingLibcxx.html). Note: "Experimental Support for Windows".

1. Software tools and Visual Studio are installed and set up
1. Git Bash: Clone the LLVM Project on the disk
2. Git Bash: In the *llvm-project* folder: checkout 9.0.1. 
3. Exit Git Bash

4. Hack needed for Windows 7: *llvm-project\libcxx\CMakeLists.txt*, line 560 - 561: add *add_definitions(-DWINVER=0x0601)*
 *add_definitions(-D_WIN32_WINNT=0x0601)*  
  Otherwise, the builds link to *kernel32.dll* of Windows 10. (Maybe Windows 8.1 needs similar hack?)

5. Create a new build directory in *llvm-project*
6. From Start Menu: start the *x64 Native Tools Command Prompt for VS 2019*
7. Change directory to the *build* directory
7. For Windows 7, x64 Debug:  
   Use CMake flags: -DCMAKE_SYSTEM_VERSION=7 -DCMAKE_BUILD_TYPE=Debug  
   Other CMake settings stay the same.  
   Example, builds *c++.dll*:
```
> cmake -G "Visual Studio 14 2015 Win64" -T "ClangCL" -DCMAKE_SYSTEM_VERSION=7 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER="C:/LLVM-9/bin/clang++.exe" -DCMAKE_C_COMPILER="C:/LLVM-9/bin/clang.exe"  -DLLVM_PATH="C:/workspace/github/llvm-project/llvm" -DLIBCXX_ENABLE_SHARED=YES -DLIBCXX_ENABLE_STATIC=NO -DLIBCXX_ENABLE_EXPERIMENTAL_LIBRARY=NO  ..\libcxx

> cmake --build .

> msbuild libcxx.sln -t:Build -p:Configuration=Debug;Platform=x64
```
  The CMake building actually required more fiddling than the LLVM reference instructed. Not so simple.

8. Windows 10 doesn't need -DCMAKE_SYSTEM_VERSION for CMake. How about Windows 8.1?
9. Release build: CMake needs -DCMAKE_BUILD_TYPE=Release and the final build uses -p:Configuration=Release;Platform=x64 
10. The resulting binaries (.dll, .lib) are located in *build\lib\Debug* and *build\lib\Release*:  
    c++.dll  
    c++.lib  
    c++.pdb

11. The Clang++ compilation needs include path: *llvm-project\libcxx\include*
12. The lld linker needs the library directory, where the .dll, .lib are, either Debug or Release (llvm-project\build\lib\Debug, -Release).
Or copy the files to other locations and give those directories.

13. The lld linker looks for *libc++.lib*. Must rename *c++.lib* to *libc++.lib* (or copy and rename the copied file).


### CMake Generator for Visual Studio 2019 - an experiment

Seems to work only for Windows 7, Debug:

```
> cmake -G "Visual Studio 16 2019" -A x64 -T "ClangCL" -DCMAKE_SYSTEM_VERSION=7 -DCMAKE_BUILD_TYPE=Debug ...

> ...

```
# Using Clang++ from the command-line

*Debug:*  
```
> build_x64_debug.bat
```
*Release:*  
```
> build_x64_release.bat
```
The exact command-line is in the .bat files.
The .exe file needs *c++.dll*. The right version is needed for Debug/Release, respectively.
