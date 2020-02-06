#!/bin/sh -e
set +v
if  [ "${1}" != "gcc" -a "${1}" != "llvm" ] ; then
   echo "Usage: ""${0}"" <gcc | llvm>"
   exit 0
fi
if  [ "${1}" = "gcc" ] ; then
  make BUILD=Debug distclean
  make USE_CXX_SOURCES=1 CC=gcc-8 CXX=g++-8 BUILD=Debug coverage
  cd test
  make BUILD=Debug distclean
  make CC=gcc-8 CXX=g++-8 BUILD=Debug coverage
  cd Debug && ./test_lukusana
  cd ../..
  echo
  echo "Creating GCOV coverage report"
  echo
  gcov-8 -d -b -k -m -r cplusplus/*.cpp  --object-directory Debug/ > gcov_coverage_report.txt
  echo
  echo GCOV done.
  echo
fi
if  [ "${1}" = "llvm" ] ; then
  make BUILD=Debug distclean
  make USE_CXX_SOURCES=1 CC=clang-8 CXX=clang++-8 BUILD=Debug coverage
  cd test
  make BUILD=Debug distclean
  make CC=clang-8 CXX=clang++-8 BUILD=Debug coverage
  echo
  echo "Creating LLVM coverage report"
  echo
  LLVM_PROFILE_FILE="./lukusana.profraw" ./Debug/test_lukusana
  llvm-profdata-8 merge -sparse ./lukusana.profraw -o ./lukusana.profdata
  llvm-cov-8 report ./Debug/test_lukusana -instr-profile=lukusana.profdata > llvm_coverage_report.txt
  echo
  echo LLVM done.
  echo
fi


