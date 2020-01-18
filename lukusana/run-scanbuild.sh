#!/bin/sh
# won't work:
#scan-build-8 -v --use-c++=/usr/bin/g++-8 --use-cc=/usr/bin/gcc-8 make

# works:
scan-build-8 -v --use-c++=/usr/bin/clang-8 --use-cc=/usr/bin/clang-8 make

# also ok
#scan-build-8 --keep-cc -v make
