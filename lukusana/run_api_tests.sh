#!/bin/sh -e
lib_folder=./lib-Debug
lib_file=${lib_folder}/liblukusana.so

if [ ! -f ${lib_file} ]; then 
  echo ${lib_file} missing
  exit 0
fi
echo Running tests...
echo
cd test && python3 -m unittest -v



