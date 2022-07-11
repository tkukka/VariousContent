# Sisältö / Contents

Modernisoitu versio (C++17) alkuperäisistä tiedostoista. 
Modern C++17 implementation basing on the original files.

**Clang_Windows** LLVM 9.0 (Clang, lld, libc++, C++17).
Using Clang 9.0, lld, libc++ and C++17.

**MSYS2** MSYS2/mingw-w64 kääntö ja linkitys komentoriviltä. A command-line build with the MSYS2/mingw-w64.

**original**: tehtävänanto, alkuperäiset C++98-lähdekoodit (kevät v.2008, Windows XP). 
The assignment, the original C++-sources (C++98, spring 2008, Windows XP).

**VStudio_2019** C++17 toteutuksen Visual Studio -projekti. 
Visual Studio 2019 solution & project files for the new C++17 implementation.

# Source C++ Dialect

**C++**: C++17 (compiler: -std=c++17)

# Build Platforms
### Linux (development platform)
- Ubuntu 20.04 LTS
- GNU Make 4.2.1
- **GCC 9.3**, linker: GNU gold 1.16 (ld.gold), libstdc++
- **Clang 10.0**, linker: LLD 10.0 (ld.lld), libc++

### Windows 7 SP 1 x64

Just experimenting how it builds with  
   1) LLVM Release 9.0
   2) Microsoft Visual Studio Community 2019.  
   3) MSYS2/mingw-w64 GCC 9.2.0  

See the folders **Clang_Windows**, **MSYS2** and **VStudio_2019**.

# Linux: Build Flags for Makefile


Flag |Use Clang | Use GCC
----|----|----
**CC**  | clang | < undefined > or gcc
**CXX**  | clang++ | < undefined > or g++

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
$ make CC=clang CXX=clang++
```

3. Build targeting Release, use Clang
```Shell Session
$ make CC=clang CXX=clang++ BUILD=Release
```

4. Build targeting Release, use g++
```Shell Session
$ make CC=gcc CXX=g++ BUILD=Release
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

