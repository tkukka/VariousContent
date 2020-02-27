#!/bin/sh -e
set -v
javac -cp ".:/usr/share/java/junit4.jar" -encoding UTF-8 -Werror -Xlint:all -Xdiags:verbose NumberTest.java
java -ea -cp ".:/usr/share/java/junit4.jar" org.junit.runner.JUnitCore NumberTest

