#!/bin/sh
# won't work:
#scan-build-10 -v --use-c++=/usr/bin/g++ --use-cc=/usr/bin/gcc make

# works:
scan-build-10 -v --use-c++=/usr/bin/clang --use-cc=/usr/bin/clang make

# also ok
#scan-build-10 --keep-cc -v make
