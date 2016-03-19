#!/bin/bash
# Runs All Of EvoMusic In One Go

echo "scl enable python33 bash"
scl enable python33 bash &

echo "make"
make -f Makefile

if ["$1" = "-p"] && ["$2" = "-r"]; then
  echo "UI"
  java -jar UI.jar $1 $2 &
  
  echo "./EvoMusic"
  ./EvoMusic $1 $3 $4
elif ["$2" = "-p"] && ["$1" = "-r"]; then
  echo "UI"
  java -jar UI.jar $1 $2 &
  
  echo "./EvoMusic"
  ./EvoMusic $2 $3 $4
elif ["$1" = "-p"]; then
  echo "UI"
  java -jar UI.jar $1 &
  
  echo "./EvoMusic"
  ./EvoMusic $1 $2 $3
elif ["$1" = "-r"]; then
  echo "UI"
  java -jar UI.jar $1 &
  
  echo "./EvoMusic"
  ./EvoMusic $2 $3
else
    echo "UI"
  java -jar UI.jar &
  
  echo "./EvoMusic"
  ./EvoMusic $1 $2
fi
