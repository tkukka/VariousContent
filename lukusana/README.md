# Source C/C++ Dialect
* **C**: C11 (compiler: -std=c11)
* **C++**: C++17 (compiler: -std=c++17)
# Build Platform
- Ubuntu 18.04 LTS
- GNU Make 4.1
- C library: **GNU libc 2.27**
- **GCC 8.3**, linker: GNU gold 1.15 (ld.gold), libstdc++ (libstdc++.so.6.0.25, GLIBCXX_3.4.25, CXXABI_1.3.11)
- **Clang 8.0**, linker: LLD 8.0  (ld.lld-8) + libc++ 8.0
- optional: CodeLite 13.x IDE

# Build Flags for Makefile

Flag |Compile C Sources | Compile C++ Sources
----|----|----
**USE_CXX_SOURCES**  |  < undefined >  |  1 


Flag |Use Clang | Use GCC
----|----|----
**CC**  |  < undefined > or **clang** |  gcc
**CXX**  |  < undefined > or **clang** |  g++ 

Flag | Debug Build | Release Build
----|----|----
**BUILD**  |  < undefined > or **Debug** |  Release

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