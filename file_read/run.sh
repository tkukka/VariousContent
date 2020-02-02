#/bin/sh -e
echo "First building Java, C & C++ code"
echo
make BUILD=Release
echo
echo "Build done!"
echo
./file_read_c
./file_read_cxx
java JavaFileRead
python3 ./file_read.py
./file_read.R
echo "Shell script reads..."
./file_read_shell.sh
echo "Script done."
echo
echo 'Execute "make clean" to clean up.'


