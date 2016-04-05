#!/bin/bash
# Runs All Of EvoMusic In One Go

if [ $# -lt 2 ]; then
  echo "Usages: $0 [print|supress] RandomSeed NumIterations"
  echo "        $0 [continue] NumIterations"
  exit
fi

chmod 0700 ./wav.sh
make -f Makefile

cnt=`ps -eaflc --sort stime | grep UI.jar |grep -v grep | wc -l`
if [ "$1" = "-p" ] || [ "$1" = "p" ] || [ "$1" = "print" ]; then
  if [ $# -lt 3 ]; then
    echo "Usage: $0 [-p|p|print] RandomSeed NumIterations"
    exit
  fi
  if(test $cnt -lt 1) ; then
    java -jar UI.jar $1 &
  fi
  
  if hash python3 2>/dev/null; then
      ./EvoMusic $1 $2 $3
  elif hash scl 2>/dev/null; then
      scl enable python33 "./EvoMusic $1 $2 $3"
  else
      echo "neither python3 nor scl are commands in your environment"
      exit
  fi
  
elif [ "$1" = "-s" ] || [ "$1" = "s" ] || [ "$1" = "supress" ]; then
  if [ $# -lt 3 ]; then
    echo "Usage: $0 [-s|s|supress] RandomSeed NumIterations"
    exit
  fi
  if hash python3 2>/dev/null; then
      ./EvoMusic $2 $3
  elif hash scl 2>/dev/null; then
      scl enable python33 "./EvoMusic $2 $3"
  else
      echo "neither python3 nor scl are commands in your environment"
      exit
  fi
  
elif [ "$1" = "-c" ] || [ "$1" = "c" ] || [ "$1" = "continue" ]; then
  if [ $# -lt 2 ]; then
    echo "Usage: $0 [-c|c|continue] NumIterations"
    exit
  fi
  if(test $cnt -lt 1) ; then
    java -jar UI.jar -r &
  fi
  
  if hash python3 2>/dev/null; then
      ./EvoMusic $1 $2
  elif hash scl 2>/dev/null; then
      scl enable python33 "./EvoMusic $1 $2"
  else
      echo "neither python3 nor scl are commands in your environment"
      exit
  fi
  
else
  if(test $cnt -lt 1) ; then
    java -jar UI.jar &
  fi
  
  if hash python3 2>/dev/null; then
      ./EvoMusic $1 $2
  elif hash scl 2>/dev/null; then
      scl enable python33 "./EvoMusic $1 $2"
  else
      echo "neither python3 nor scl are commands in your environment"
      exit
  fi
  
fi
