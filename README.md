# EvolutionOfMusic
Generations of Songs shall be born; Only the Best Shall Survive...
  
  
  
    Copyright 2016 Stephen Andersen, Lee Ingram, Aaron Schuman & Jonathan Peard

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

##Setup for the Lab Computers
This line enables Python 3 on lab computers
   `scl enable python33 bash`

##All At Once
Running on a bash-enabled system
   `chmod 0700 run.sh`
   `./run.sh [-s|-p] RandomSeed NumIterations`
   `./run.sh [-c] [-s] NumIterations`

  - `-p | p | print`: Print information into the terminal
  - `-s | s | supress`: Prevents User Interface from opening
  - `-c | c | continue`: Continues from the last generation; Does not initialize anything

##Synthesizer
To synthesize samples from a specific generation use
  `./wav.sh [AM|ACCORDIAN|BASSOON|BELL|BRASS|FM|GUITAR|HARP|ORGAN|WOODBLOCK] main_py_samples_generation_###`
  
  - `AM`: Amplitude Modulator
  - `FM`: Frequency Modulator
  - All instruments are hardcoded in `C2Wav.cpp` and all of them but the Organ were created with the Frequency Modulator

##Separately
###Makefile
Run
   `make`
to make the C++ executable `EvoMusic`

###UI
You can run the UI with
    `java -jar UI.jar [-r|r|RUNNING]`

  - `-r | r | running`: Non-destructively opens graphing UI (Normally the UI will empty the log and the graph)
    
###Overhead(Actual Program)
Then run
    `./EvoMusic RandomSeed NumGenerations`
    
And watch it go.

###Alternates
You can also run
      `./EvoMusic` and then its arguments `RandomSeed` and `NumGenerations` with newlines in between.
