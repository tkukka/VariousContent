# Sisältö / Contents

Modernisoitu versio (C++17) alkuperäisistä tiedostoista. 
Modern C++17 implementation basing on the original files.

**original**: tehtävänanto, alkuperäiset C++98-lähdekoodit (kevät v.2008, Windows XP). 
The assignment, the original C++-sources (C++98, spring 2008, Windows XP).

# Source C++ Dialect

**C++**: C++17 (compiler: -std=c++17)

# Build Platform
- Ubuntu 18.04 LTS
- GNU Make 4.1
- **GCC 8.3**, linker: GNU gold 1.15 (ld.gold), libstdc++ (libstdc++.so.6.0.25, GLIBCXX_3.4.25, CXXABI_1.3.11)
- **Clang 8.0**, linker: LLD 8.0  (ld.lld-8) + libc++ 8.0


# Build Flags for Makefile


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

