#!/bin/bash
# Runs All Of EvoMusic In One Go

echo "scl enable python33 bash"
scl enable python33 bash &

echo "make"
make -f Makefile

echo "UI"
java -jar UI.jar &

echo "./EvoMusic"
./EvoMusic $1 $2