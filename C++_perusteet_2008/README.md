# Sisältö / Contents

Modernisoitu versio (C++17) alkuperäisistä tiedostoista. 
Modern C++17 implementation basing on the original files.

**KingsPath_EclipseCDT_Windows** Eclipse CDT (C/C++ Development Tooling) -projektitiedostot. LLVM 9.0 (Clang, lld, libc++, C++17).
Eclipse CDT project using LLVM 9.0 tools, libc++ and C++17.

**MSYS2** MSYS2/mingw-w64 kääntö ja linkitys komentoriviltä. A command-line build with the MSYS2/mingw-w64.

**original**: tehtävänanto, alkuperäiset C++98-lähdekoodit (kevät v.2008, Windows XP). 
The assignment, the original C++-sources (C++98, spring 2008, Windows XP).

**VStudio_2019** C++17 toteutuksen Visual Studio -projekti. 
Visual Studio 2019 solution & project files for the new C++17 implementation.

# Source C++ Dialect

**C++**: C++17 (compiler: -std=c++17)

# Build Platforms
### Linux (development platform)
- Ubuntu 18.04 LTS
- GNU Make 4.1
- **GCC 8.3**, linker: GNU gold 1.15 (ld.gold), libstdc++ (libstdc++.so.6.0.25, GLIBCXX_3.4.25, CXXABI_1.3.11)
- **Clang 8.0**, linker: LLD 8.0  (ld.lld-8) + libc++ 8.0

### Windows 7 SP 1 x64

Just experimenting how it builds with  
   1) LLVM Release 9.0
   2) Microsoft Visual Studio Community 2019.  
   3) MSYS2/mingw-w64 GCC 9.2.0  

See the folders **KingsPath_EclipseCDT_Windows**, **MSYS2** and **VStudio_2019**.

# Linux: Build Flags for Makefile


Flag |Use Clang | Use GCC
----|----|----
**CC**  | clang-8 | < undefined > or gcc-8
**CXX**  | clang++-8 | < undefined > or g++-8

Flag | Debug Build, the default | Release Build
----|----|----
**BUILD**  |  < undefined > or Debug |  Release

#### Examples
1. Build targeting Debug, use g++
```Shell Session
$ make
```

2. Build targeting Debug, use Clang
```Shell Session
$ make CC=clang-8 CXX=clang++-8
```

3. Build targeting Release, use Clang
```Shell Session
$ make CC=clang-8 CXX=clang++-8 BUILD=Release
```

4. Build targeting Release, use g++
```Shell Session
$ make CC=gcc-8 CXX=g++-8 BUILD=Release
```
#### Cleaning up [Debug | Release]
1. Cleaning up Debug builds:
```Shell Session
$ make clean
```

2. Cleaning up Release builds:
```Shell Session
$ make BUILD=Release clean
```
#### Totally cleaning up all [Debug | Release]
1. Cleaning up **all** generated files for Debug builds:
```Shell Session
$ make distclean
```

2. Cleaning up **all** generated files for Release builds:
```Shell Session
$ make BUILD=Release distclean
```

