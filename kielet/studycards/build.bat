md bin
javac -encoding UTF-8 -Werror -Xlint:all -Xdiags:verbose *.java -d bin
cd bin
jar --verbose --create --manifest ..\Manifest.txt --file StudyCards.jar *.class

