#!/bin/bash
set -e
LIB_PATH_DEBUG=lib-Debug
LIB_PATH_RELEASE=lib-Release
FLAGS_DEBUG=(-Wl,--enable-new-dtags,-z,now,-z,defs -Wl,-rpath="../${LIB_PATH_DEBUG}" -g -Wall) 
FLAGS_RELEASE=(-Wl,--enable-new-dtags,-z,now,-z,defs -Wl,-rpath="../${LIB_PATH_RELEASE}"  -O2 -Wall)
LINK_DIR=link-test
OUTFILE=test.out

make distclean
make BUILD=Release distclean
make CC=gcc-8 CXX=g++-8
make CC=gcc-8 CXX=g++-8 BUILD=Release
sleep 2
echo
echo
set -v
test -f ${OUTFILE} && rm ${OUTFILE}
test -d ${LINK_DIR} || mkdir ${LINK_DIR}
gcc-8 -fuse-ld=gold "${FLAGS_DEBUG[@]}"  -o "${LINK_DIR}/test-1" lukusana_main.c -L"./${LIB_PATH_DEBUG}" -llukusana
gcc-8 -fuse-ld=gold "${FLAGS_RELEASE[@]}"  -o "${LINK_DIR}/test-2" lukusana_main.c -L"./${LIB_PATH_RELEASE}" -llukusana
cd ${LINK_DIR}
./test-1 094690 && echo OK1 >> "../${OUTFILE}"
./test-2 094690 && echo OK2 >> "../${OUTFILE}"
cd ..
set +v
sleep 2
make distclean
make BUILD=Release distclean
make
make BUILD=Release
sleep 2
echo
echo
set -v
clang-8 -fuse-ld=lld-8 "${FLAGS_DEBUG[@]}" -o "${LINK_DIR}/test-3" lukusana_main.c -L"./${LIB_PATH_DEBUG}" -llukusana
clang-8 -fuse-ld=lld-8 "${FLAGS_RELEASE[@]}" -o "${LINK_DIR}/test-4" lukusana_main.c -L"./${LIB_PATH_RELEASE}" -llukusana
cd ${LINK_DIR}
./test-3 094690 && echo OK3 >> "../${OUTFILE}"
./test-4 094690 && echo OK4 >> "../${OUTFILE}"
./test-1 094690 && echo OK5 >> "../${OUTFILE}"
./test-2 094690 && echo OK6 >> "../${OUTFILE}"
cd ..
set +v
echo
echo
sleep 2
make distclean
make BUILD=Release distclean
make CC=gcc-8 CXX=g++-8
make CC=gcc-8 CXX=g++-8 BUILD=Release
echo 
echo
set -v
cd ${LINK_DIR}
./test-3 094690 && echo OK7 >> "../${OUTFILE}"
./test-4 094690 && echo OK8 >> "../${OUTFILE}"

