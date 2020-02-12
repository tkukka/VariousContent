#!/bin/sh -e
set +v
cd test && make clean
cd ..
make distclean && make CC=gcc-8 CXX=g++-8 > /dev/null
echo
echo "Now running C tests [gcc]."
echo
cd test && python3 -m unittest -v
cd ..
echo
echo
echo "Waiting 5 secs before C++ part [g++]."
echo
sleep 5
make distclean && make USE_CXX_SOURCES=1 CC=gcc-8 CXX=g++-8 > /dev/null
cd test
make CC=gcc-8 CXX=g++-8 && ./Debug/test_lukusana
make clean
cd ..
make distclean && make CC=clang-8 CXX=clang++-8 > /dev/null
echo
echo "Now running C tests [clang]."
echo
cd test && python3 -m unittest -v
cd ..
echo
echo
echo "Waiting 5 secs before C++ part [clang]."
echo
sleep 5
make distclean && make USE_CXX_SOURCES=1 CC=clang-8 CXX=clang++-8 > /dev/null
cd test
make CC=clang-8 CXX=clang++-8 && ./Debug/test_lukusana
make clean
cd ..

