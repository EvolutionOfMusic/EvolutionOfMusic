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
Enables Python
   `scl enable python33 bash`

##All At Once
Run
   `chmod 0700 run.sh`
   `./run.sh [-p] RandomSeed NumIterations`

  - `-p | p | print`: Print information into the terminal

##Separately
###Makefile
Run
   `make`
to make the C++ executable `EvoMusic`

###UI
You can run the UI with
    `java -jar UI.jar [-r|r|RUNNING]`

  - `-r | r | running`: Non-destructively opens graphing UI
    
###Overhead(Actual Program)
Then run
    `./EvoMusic RandomSeed NumGenerations`
    
And watch it go.

###Alternates
You can also run
      `./EvoMusic` and it's arguments `RandomSeed` and `NumGenerations` with newlines in between.
