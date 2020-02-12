# Test Coverage Instrumentation (C++)
Assuming the upper level coverage instrumentation done, then

for **g++** (8.3)

```Shell Session
$ make CC=gcc-8 CXX=g++-8 BUILD=Debug coverage
$ cd Debug
$ ./test_lukusana
$ cd ../..
$ gcov-8 -d -b -k -m -r cplusplus/*.cpp  --object-directory Debug/ > gcov_coverage_report.txt
```
For **Clang** (8.0)

```Shell Session
$ make CC=clang-8 CXX=clang++-8 BUILD=Debug coverage
$ LLVM_PROFILE_FILE="./lukusana.profraw" ./Debug/test_lukusana
$ llvm-profdata-8 merge -sparse ./lukusana.profraw -o ./lukusana.profdata
$ llvm-cov-8 report ./Debug/test_lukusana -instr-profile=lukusana.profdata > llvm_coverage_report.txt
```

# Third Party Components
- File **catch.hpp**: [Catch2](https://github.com/catchorg/Catch2) version 2.11.1. Licensed under [The Boost Software License](./LICENSE_1_0.txt). 
- File **doctest.h**: [doctest](https://github.com/onqtam/doctest) version 2.3.6. Licensed under [The MIT License](https://github.com/onqtam/doctest/blob/master/LICENSE.txt).

# Verdict

**doctest** is better: quicker builds, detected missing header files.
 

