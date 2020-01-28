#!/bin/bash
# Usage:
#        to run the tests                        ./run_linking_test.sh
#        to clean up files created by tests      ./run_linking_test.sh clean
set -e
lib_path_debug=lib-Debug
lib_path_release=lib-Release
lib_path_debug_gcc=${lib_path_debug}-gcc
lib_path_release_gcc=${lib_path_release}-gcc
lib_path_debug_clang=${lib_path_debug}-clang
lib_path_release_clang=${lib_path_release}-clang
# two bash arrays:
flags_debug=(-Wl,--enable-new-dtags,-z,relro,-z,now,-z,defs,-z,noexecstack -g -Wall)
flags_release=(-Wl,--enable-new-dtags,-z,relro,-z,now,-z,notext,-z,noexecstack,-z,defs,-pie,-s -O2 -Wall -march=native -fPIE -pie)
link_dir=link-test
outfile=linking_test_out.txt

if [ "$1" = "clean" ]; then
  set -v
  echo "cleaning up..."
  rm -fr ${lib_path_debug_gcc} || true
  rm -fr ${lib_path_release_gcc} || true
  rm -fr ${lib_path_debug_clang} || true
  rm -fr ${lib_path_release_clang} || true
  rm -fr ${link_dir} || true
  rm -f  ${outfile} || true
  echo "done."
  exit 0
fi 


if test ! -d "${lib_path_debug_gcc}" && test ! -d "${lib_path_release_gcc}" ; then
  set +v
  make distclean
  make BUILD=Release distclean
  make CC=gcc-8 CXX=g++-8
  make CC=gcc-8 CXX=g++-8 BUILD=Release
  echo
  echo
  set -v
  cp -rav ${lib_path_debug} ${lib_path_debug_gcc}
  cp -rav ${lib_path_release} ${lib_path_release_gcc}
  test -d ${lib_path_debug_gcc} || exit 1
  test -d ${lib_path_release_gcc} || exit 1
fi

if test ! -d "${lib_path_debug_clang}" && test ! -d "${lib_path_release_clang}" ; then
  set +v
  make distclean
  make BUILD=Release distclean
  make
  make BUILD=Release
  echo
  echo
  set -v
  cp -rav ${lib_path_debug} ${lib_path_debug_clang}
  cp -rav ${lib_path_release} ${lib_path_release_clang}
  test -d ${lib_path_debug_clang} || exit 1
  test -d ${lib_path_release_clang} || exit 1
fi

echo
set -v
test -f ${outfile} && rm ${outfile}
test -d ${link_dir} || mkdir ${link_dir}
gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_debug_gcc}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-1" lukusana_main.c -L"./${lib_path_debug_gcc}" -llukusana
gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_release_gcc}"  "${flags_release[@]}"  -std=c11 -o "${link_dir}/test-2" lukusana_main.c -L"./${lib_path_release_gcc}" -llukusana
echo
cd ${link_dir} || exit 1
./test-1 946909 && echo '[1] link gcc - gcc-lib debug OK' >> "../${outfile}"
./test-2 946909 && echo '[2] link gcc - gcc-lib release OK' >> "../${outfile}"
cd ..
test -f ${outfile} || exit 1
echo
clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_debug_clang}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-3" lukusana_main.c -L"./${lib_path_debug_clang}" -llukusana
clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_release_clang}" "${flags_release[@]}" -std=c11 -o "${link_dir}/test-4" lukusana_main.c -L"./${lib_path_release_clang}" -llukusana
cd ${link_dir}
./test-3 946909 && echo '[3] link clang - clang-lib debug OK' >> "../${outfile}"
./test-4 946909 && echo '[4] link clang - clang-lib release OK' >> "../${outfile}"
cd ..
echo 'Cross linkings:'
gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_debug_clang}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-5" lukusana_main.c -L"./${lib_path_debug_clang}" -llukusana
gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_release_clang}" "${flags_release[@]}" -std=c11 -o "${link_dir}/test-6" lukusana_main.c -L"./${lib_path_release_clang}" -llukusana
echo
clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_debug_gcc}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-7" lukusana_main.c -L"./${lib_path_debug_gcc}" -llukusana
clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_release_gcc}" "${flags_release[@]}" -std=c11 -o "${link_dir}/test-8" lukusana_main.c -L"./${lib_path_release_gcc}" -llukusana
cd ${link_dir}
./test-5 946909 && echo '[5] link gcc - clang-lib debug OK' >> "../${outfile}"
./test-6 946909 && echo '[6] link gcc - clang-lib release OK' >> "../${outfile}"
echo
./test-7 946909 && echo '[7] link clang - gcc-lib debug OK' >> "../${outfile}"
./test-8 946909 && echo '[8] link clang - gcc-lib release OK' >> "../${outfile}"
cd ..
set +v
# ---------- C++ ---------
cxx_main=./cplusplus/lukusana_main.cpp
echo '---------------- C++ --------------------'
echo 'C stuff cleaning up...'
rm -fr ${lib_path_debug_gcc} || true
rm -fr ${lib_path_release_gcc} || true
rm -fr ${lib_path_debug_clang} || true
rm -fr ${lib_path_release_clang} || true
echo 'C stuff cleaning done.'
make distclean
make BUILD=Release distclean
make USE_CXX_SOURCES=1 CC=gcc-8 CXX=g++-8
make USE_CXX_SOURCES=1 CC=gcc-8 CXX=g++-8 BUILD=Release
echo
echo
set -v
cp -rav ${lib_path_debug} ${lib_path_debug_gcc}
cp -rav ${lib_path_release} ${lib_path_release_gcc}
test -d ${lib_path_debug_gcc} || exit 1
test -d ${lib_path_release_gcc} || exit 1
echo
set +v
make distclean
make BUILD=Release distclean
make USE_CXX_SOURCES=1
make USE_CXX_SOURCES=1 BUILD=Release
echo
echo
set -v
cp -rav ${lib_path_debug} ${lib_path_debug_clang}
cp -rav ${lib_path_release} ${lib_path_release_clang}
test -d ${lib_path_debug_clang} || exit 1
test -d ${lib_path_release_clang} || exit 1
echo
echo 'C++ linkings'
g++-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_debug_gcc}" "${flags_debug[@]}" -std=c++17 -o "${link_dir}/test-9" "${cxx_main}" -L"./${lib_path_debug_gcc}" -llukusana
g++-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_release_gcc}"  "${flags_release[@]}" -std=c++17 -o "${link_dir}/test-10" "${cxx_main}" -L"./${lib_path_release_gcc}" -llukusana
echo
cd ${link_dir} || exit 1
./test-9 946909 && echo '[9] link g++ - gcc-lib debug OK' >> "../${outfile}"
./test-10 946909 && echo '[10] link g++ - gcc-lib release OK' >> "../${outfile}"
cd ..
echo
clang++-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_debug_clang}" "${flags_debug[@]}" -std=c++17 -stdlib=libstdc++ -o "${link_dir}/test-11" "${cxx_main}" -L"./${lib_path_debug_clang}" -llukusana -lstdc++
clang++-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_release_clang}" "${flags_release[@]}" -std=c++17 -stdlib=libstdc++ -o "${link_dir}/test-12" "${cxx_main}" -L"./${lib_path_release_clang}" -llukusana -lstdc++
cd ${link_dir}
./test-11 946909 && echo '[11] link clang++ - clang-lib debug OK' >> "../${outfile}"
./test-12 946909 && echo '[12] link clang++ - clang-lib release OK' >> "../${outfile}"
cd ..
echo 'C++ Cross linkings:'
g++-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_debug_clang}" "${flags_debug[@]}" -std=c++17 -o "${link_dir}/test-13" "${cxx_main}" -L"./${lib_path_debug_clang}" -llukusana
g++-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_release_clang}" "${flags_release[@]}" -std=c++17 -o "${link_dir}/test-14" "${cxx_main}" -L"./${lib_path_release_clang}" -llukusana
echo
clang++-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_debug_gcc}" "${flags_debug[@]}" -std=c++17 -stdlib=libstdc++ -o "${link_dir}/test-15" "${cxx_main}" -L"./${lib_path_debug_gcc}" -llukusana -lstdc++
clang++-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_release_gcc}" "${flags_release[@]}" -std=c++17 -stdlib=libstdc++ -o "${link_dir}/test-16" "${cxx_main}" -L"./${lib_path_release_gcc}" -llukusana -lstdc++
cd ${link_dir}
./test-13 946909 && echo '[13] link g++ - clang-lib debug OK' >> "../${outfile}"
./test-14 946909 && echo '[14] link g++ - clang-lib release OK' >> "../${outfile}"
echo
./test-15 946909 && echo '[15] link clang++ - gcc-lib debug OK' >> "../${outfile}"
./test-16 946909 && echo '[16] link clang++ - gcc-lib release OK' >> "../${outfile}"
cd ..

