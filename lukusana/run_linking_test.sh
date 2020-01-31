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

set -v
test -f ${outfile} && rm ${outfile}
set +v
make distclean
make BUILD=Release distclean
make CC=gcc-8 CXX=g++-8
make CC=gcc-8 CXX=g++-8 BUILD=Release
echo
echo
set -v
cd Debug || exit 1
./lukusana 946909 && echo '[1] [C prepare 1] gcc executable debug OK' >> "../${outfile}"
cd ..
cd Release || exit 1
./lukusana 946909 && echo '[2] [C prepare 2] gcc executable release OK' >> "../${outfile}"
cd ..
cp -rv ${lib_path_debug} ${lib_path_debug_gcc}
cp -rv ${lib_path_release} ${lib_path_release_gcc}
test -d ${lib_path_debug_gcc} || exit 1
test -d ${lib_path_release_gcc} || exit 1
cp -v Debug/*.a ${lib_path_debug_gcc}/
cp -v Release/*.a ${lib_path_release_gcc}/
set +v
make distclean
make BUILD=Release distclean
make
make BUILD=Release
echo
echo
set -v
cd Debug || exit 1
./lukusana 946909 && echo '[3] [C prepare 3] clang executable debug OK' >> "../${outfile}"
cd ..
cd Release || exit 1
./lukusana 946909 && echo '[4] [C prepare 4] clang executable release OK' >> "../${outfile}"
cd ..
cp -rav ${lib_path_debug} ${lib_path_debug_clang}
cp -rav ${lib_path_release} ${lib_path_release_clang}
test -d ${lib_path_debug_clang} || exit 1
test -d ${lib_path_release_clang} || exit 1
cp -v Debug/*.a ${lib_path_debug_clang}/
cp -v Release/*.a ${lib_path_release_clang}/
echo
test -d ${link_dir} || mkdir ${link_dir}
gcc-8 -fuse-ld=gold  "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-1" lukusana_main.c "./${lib_path_debug_gcc}/liblukusana.a"
gcc-8 -fuse-ld=gold  "${flags_release[@]}" -std=c11 -o "${link_dir}/test-2" lukusana_main.c "./${lib_path_release_gcc}/liblukusana.a"

gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_debug_gcc}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-3" lukusana_main.c -L"./${lib_path_debug_gcc}" -llukusana
gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_release_gcc}"  "${flags_release[@]}"  -std=c11 -o "${link_dir}/test-4" lukusana_main.c -L"./${lib_path_release_gcc}" -llukusana
echo
cd ${link_dir} || exit 1
./test-1 946909 && echo '[5] [test-1] static link gcc - gcc-lib debug OK' >> "../${outfile}"
./test-2 946909 && echo '[6] [test-2] static link gcc - gcc-lib release OK' >> "../${outfile}"
./test-3 946909 && echo '[7] [test-3] .so link gcc - gcc-lib debug OK' >> "../${outfile}"
./test-4 946909 && echo '[8] [test-4] .so link gcc - gcc-lib release OK' >> "../${outfile}"
cd ..
test -f ${outfile} || exit 1
echo
clang-8 -fuse-ld=lld-8 "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-5" lukusana_main.c "./${lib_path_debug_clang}/liblukusana.a"
clang-8 -fuse-ld=lld-8 "${flags_release[@]}" -std=c11 -o "${link_dir}/test-6" lukusana_main.c "./${lib_path_release_clang}/liblukusana.a"

clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_debug_clang}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-7" lukusana_main.c -L"./${lib_path_debug_clang}" -llukusana
clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_release_clang}" "${flags_release[@]}" -std=c11 -o "${link_dir}/test-8" lukusana_main.c -L"./${lib_path_release_clang}" -llukusana
cd ${link_dir}
./test-5 946909 && echo '[9] [test-5] static link clang - clang-lib debug OK' >> "../${outfile}"
./test-6 946909 && echo '[10] [test-6] static link clang - clang-lib release OK' >> "../${outfile}"
./test-7 946909 && echo '[11] [test-7] .so link clang - clang-lib debug OK' >> "../${outfile}"
./test-8 946909 && echo '[12] [test-8] .so link clang - clang-lib release OK' >> "../${outfile}"
cd ..
echo 'Cross linkings:'
gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_debug_clang}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-9" lukusana_main.c -L"./${lib_path_debug_clang}" -llukusana
gcc-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_release_clang}" "${flags_release[@]}" -std=c11 -o "${link_dir}/test-10" lukusana_main.c -L"./${lib_path_release_clang}" -llukusana
echo
clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_debug_gcc}" "${flags_debug[@]}" -std=c11 -o "${link_dir}/test-11" lukusana_main.c -L"./${lib_path_debug_gcc}" -llukusana
clang-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_release_gcc}" "${flags_release[@]}" -std=c11 -o "${link_dir}/test-12" lukusana_main.c -L"./${lib_path_release_gcc}" -llukusana
cd ${link_dir}
./test-9 946909 && echo '[13] [test-9] .so link gcc - clang-lib debug OK' >> "../${outfile}"
./test-10 946909 && echo '[14] [test-10] .so link gcc - clang-lib release OK' >> "../${outfile}"
echo
./test-11 946909 && echo '[15] [test-11] .so link clang - gcc-lib debug OK' >> "../${outfile}"
./test-12 946909 && echo '[16] [test-12] .so link clang - gcc-lib release OK' >> "../${outfile}"
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
cd Debug || exit 1
./lukusana 946909 && echo '[17] [C++ prepare 1] g++ executable debug OK' >> "../${outfile}"
cd ..
cd Release || exit 1
./lukusana 946909 && echo '[18] [C++ prepare 2] g++ executable release OK' >> "../${outfile}"
cd ..
cp -rav ${lib_path_debug} ${lib_path_debug_gcc}
cp -rav ${lib_path_release} ${lib_path_release_gcc}
test -d ${lib_path_debug_gcc} || exit 1
test -d ${lib_path_release_gcc} || exit 1
cp -v Debug/*.a ${lib_path_debug_gcc}/
cp -v Release/*.a ${lib_path_release_gcc}/
echo
set +v
make distclean
make BUILD=Release distclean
make USE_CXX_SOURCES=1
make USE_CXX_SOURCES=1 BUILD=Release
echo
echo
set -v
cd Debug || exit 1
./lukusana 946909 && echo '[19] [C++ prepare 3] clang++ executable debug OK' >> "../${outfile}"
cd ..
cd Release || exit 1
./lukusana 946909 && echo '[20] [C++ prepare 4] clang++ executable release OK' >> "../${outfile}"
cd ..
cp -rav ${lib_path_debug} ${lib_path_debug_clang}
cp -rav ${lib_path_release} ${lib_path_release_clang}
test -d ${lib_path_debug_clang} || exit 1
test -d ${lib_path_release_clang} || exit 1
cp -v Debug/*.a ${lib_path_debug_clang}/
cp -v Release/*.a ${lib_path_release_clang}/
echo
echo 'C++ linkings'
g++-8 -fuse-ld=gold "${flags_debug[@]}" -std=c++17 -o "${link_dir}/test-13" "${cxx_main}" "./${lib_path_debug_gcc}/liblukusana.a"
g++-8 -fuse-ld=gold "${flags_release[@]}" -std=c++17 -o "${link_dir}/test-14" "${cxx_main}" "./${lib_path_release_gcc}/liblukusana.a"
g++-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_debug_gcc}" "${flags_debug[@]}" -std=c++17 -o "${link_dir}/test-15" "${cxx_main}" -L"./${lib_path_debug_gcc}" -llukusana
g++-8 -fuse-ld=gold -Wl,-rpath="../${lib_path_release_gcc}"  "${flags_release[@]}" -std=c++17 -o "${link_dir}/test-16" "${cxx_main}" -L"./${lib_path_release_gcc}" -llukusana
echo
cd ${link_dir} || exit 1
./test-13 946909 && echo '[21] [test-13] static link g++ - g++-lib debug OK' >> "../${outfile}"
./test-14 946909 && echo '[22] [test-14] static link g++ - g++-lib release OK' >> "../${outfile}"
./test-15 946909 && echo '[23] [test-15] .so link g++ - g++-lib debug OK' >> "../${outfile}"
./test-16 946909 && echo '[24] [test-16] .so link g++ - g++-lib release OK' >> "../${outfile}"
cd ..
echo
clang++-8 -fuse-ld=lld-8 "${flags_debug[@]}" -std=c++17 -stdlib=libc++ -o "${link_dir}/test-17" "${cxx_main}" "./${lib_path_debug_clang}/liblukusana.a" -lc++
clang++-8 -fuse-ld=lld-8 "${flags_release[@]}" -std=c++17 -stdlib=libc++ -o "${link_dir}/test-18" "${cxx_main}" "./${lib_path_release_clang}/liblukusana.a" -lc++
clang++-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_debug_clang}" "${flags_debug[@]}" -std=c++17 -stdlib=libc++ -o "${link_dir}/test-19" "${cxx_main}" -L"./${lib_path_debug_clang}" -llukusana -lc++
clang++-8 -fuse-ld=lld-8 -Wl,-rpath="../${lib_path_release_clang}" "${flags_release[@]}" -std=c++17 -stdlib=libc++ -o "${link_dir}/test-20" "${cxx_main}" -L"./${lib_path_release_clang}" -llukusana -lc++
cd ${link_dir}
./test-17 946909 && echo '[25] [test-17] static link clang++ - clang++-lib debug OK' >> "../${outfile}"
./test-18 946909 && echo '[26] [test-18] static link clang++ - clang++-lib release OK' >> "../${outfile}"
./test-19 946909 && echo '[27] [test-19] .so link clang++ - clang++-lib debug OK' >> "../${outfile}"
./test-20 946909 && echo '[28] [test-20] .so link clang++ - clang++-lib release OK' >> "../${outfile}"
cd ..
set +v
echo
echo
if (( $(cat ${outfile}|wc -l) == 28 )); then
  echo 'All tests OK.'
else
  echo '**** One or more tests failed.  ****'
fi

