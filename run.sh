#!/bin/bash
# Runs All Of EvoMusic In One Go


echo "make"
make -f Makefile

if [ "$1" = "-p" ] || [ "$1" = "p" ] || [ "$1" = "print" ] || [ "$1" = "-c" ]; then
  echo "UI"
  java -jar UI.jar $1 &
  
  echo "./EvoMusic"
  #  echo "scl enable python33 bash"
  scl enable python33 "./EvoMusic $1 $2 $3"
else
  echo "UI"
  java -jar UI.jar &
  
  echo "./EvoMusic"
  #  echo "scl enable python33 bash"
  scl enable python33 "./EvoMusic $1 $2"
fi
