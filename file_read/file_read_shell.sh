#!/bin/sh
filename=./eng-uk_web_2002_1M-words.txt
echo "Now reading file ${filename}, please wait..."
n=0
while IFS= read -r line
do
  #echo "$line"
  n=$(expr ${n} + 1)
done < "${filename}"
echo "Lines: ${n}"

