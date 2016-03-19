#!/bin/bash
# Runs All Of EvoMusic In One Go

echo "scl enable python33 bash"
scl enable python33 bash &

echo "make"
make -f Makefile

if [ $1 = "-p" ] || [ $1 = "-c" ]; then
  echo "UI"
  java -jar UI.jar $1 &
  
  echo "./EvoMusic"
  ./EvoMusic $1 $2 $3
else
    echo "UI"
  java -jar UI.jar &
  
  echo "./EvoMusic"
  ./EvoMusic $1 $2
fi
