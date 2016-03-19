#!/bin/bash
# Runs All Of EvoMusic In One Go


echo "make"
make -f Makefile

if [ "$1" = "-p" ] || [ "$1" = "p" ] || [ "$1" = "print" ]; then
  #echo "PRINT"
  echo "UI"
  java -jar UI.jar $1 &
  
  echo "./EvoMusic"
  scl enable python33 "./EvoMusic $1 $2 $3"
elif [ "$1" = "-c" ] || [ "$1" = "c" ] || [ "$1" = "continue" ]; then
  #echo "CONTINUE"
  echo "UI"
  java -jar UI.jar -r &
  
  echo "./EvoMusic"
  scl enable python33 "./EvoMusic $1 $2 $3"
else
  #echo "ELSE"
  echo "UI"
  java -jar UI.jar &
  
  echo "./EvoMusic"
  scl enable python33 "./EvoMusic $1 $2"
fi
