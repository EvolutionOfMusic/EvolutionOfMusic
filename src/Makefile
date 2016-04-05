#***********************************************#
#* Stephen Andersen                    ECE 492 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
DIR = ./
CFLAGS = -g -Wall -I/src -fopenmp
DEPS = canon_in_d_test.cpp ai_shell.h critic_shell.h sd.h python3_to_cpp_converter.h song_structs.h frequencies.h
OBJ = canon_in_d_test.o ai_shell.o critic_shell.o sd.o python3_to_cpp_converter.o frequencies.o

%.o: $(DIR)%.cpp #$(DIR)$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

CanonInD: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -rf *.o

delete: clean
	rm -rf EvoMusic
	rm -rf *~
	rm -rf main_py_samples_generation_*

run:	java -jar UI.jar
	make
	./EvoMusic

help: 
	@echo 'RULES: EvoMusic, clean, delete'
