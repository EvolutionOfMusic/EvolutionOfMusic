#!/bin/bash
# Creates and plays wavs

if [ $# -lt 1 ]; then
  echo "Usages: $0 [ACCORDIAN|BASSOON|BELL|BRASS|GUITAR|ORGAN|WOODBLOCK|AM|FM] sample_generation"
  exit
fi

#Make C2Wav
make -f src/C2Wav/Makefile

#Create Wavs
if [ $# -gt 1 ];then
src/C2Wav/main $1 $2
else
src/C2Wav/main $1
fi

aplay `ls -Art *.wav | tail -n 1`
