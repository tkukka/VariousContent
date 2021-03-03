# Sisältö / Contents

**cplusplus**: modernisoitu versio (C++17). Modern C++17 implementation.

**original**: alkuperäiset C99-lähdekoodit (v.2005, Windows XP). The original C-sources (C99, year 2005, Windows XP).

**test**: C11- ja C++17 -totetutusten testejä. Some tests for C11 and C++17 implementations.

# Source C/C++ Dialect
* **C**: C11 (compiler: -std=c11)
* **C++**: C++17 (compiler: -std=c++17)

# Käännösympäristöt / Build Platforms
### Linux (development platform)
- Ubuntu 18.04 LTS
- GNU Make 4.1
- C library: **GNU libc 2.27**
- **GCC 8.3**, linker: GNU gold 1.15 (ld.gold), libstdc++ (libstdc++.so.6.0.25, GLIBCXX_3.4.25, CXXABI_1.3.11)
- **Clang 8.0**, linker: LLD 8.0  (ld.lld-8) + libc++ 8.0
- optional: CodeLite 13.x IDE. Using Custom Makefile Project (the files lukusana.workspace, *.project).

### Windows 7 SP 1 x64

Just experimenting how it builds with  
   1) LLVM Release 9.0
   2) Microsoft Visual Studio Community 2019.  
   3) Mingw-w64/MSYS2

See the folder **cplusplus**.

# Linux: Build Flags for Makefile

Flag |Compile C Sources | Compile C++ Sources
----|----|----
**USE_CXX_SOURCES**  |  < undefined >  |  1 


Flag |Use Clang | Use GCC
----|----|----
**CC**  |  < undefined > or clang-8 |  gcc-8
**CXX**  |  < undefined > or clang++-8 |  g++-8

Flag | Debug Build, the default | Release Build
----|----|----
**BUILD**  |  < undefined > or Debug |  Release

#### Examples
1. Build with C sources, targeting Debug, use Clang
```Shell Session
$ make
```

2. Build with C++ sources, targeting Debug, use Clang
```Shell Session
$ make USE_CXX_SOURCES=1
```

3. Build with C++ sources, targeting Release, use Clang
```Shell Session
$ make USE_CXX_SOURCES=1 BUILD=Release
```

4. Build with C sources, targeting Release, use gcc / g++
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
# Linux: Test Coverage Instrumentation (C++)

For **g++**

```Shell Session
$ make USE_CXX_SOURCES=1 CC=gcc-8 CXX=g++-8 BUILD=Debug coverage
```
For **Clang**

```Shell Session
$ make USE_CXX_SOURCES=1 CC=clang-8 CXX=clang++-8 BUILD=Debug coverage
```


