#***********************************************#
#* Stephen Andersen                    ECE 492 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
DIR = ./src/
CFLAGS = -g -I/src -fopenmp #-Wall
DEPS = Overhead.h ai_shell.h critic_shell.h sd.h python3_to_cpp_converter.h song_structs.h frequencies.h
OBJ = ai_shell.o critic_shell.o sd.o python3_to_cpp_converter.o song_structs.o frequencies.o

%.0: %.cpp #$(DIR)$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

EvoMusic: $(DIR)$(OBJ)
	g++ $(CFLAGS) -o $@ $^

clean: 
	rm -rf *.o

delete: clean
	rm -rf EvoMusic
	rm -rf *~

help: 
	@echo 'RULES: EvoMusic, clean, delete'
