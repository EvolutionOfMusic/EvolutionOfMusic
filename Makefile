#***********************************************#
#* Stephen Andersen                    ECE 492 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
DIR = ./src/
CFLAGS = -g -Wall -I/src
DEPS = Overhead.h ai_shell.h critic_shell.h \
	python3_to_cpp_converter.h song_structs.h frequencies.h
OBJ = Overhead.o ai_shell.o critic_shell.o \
	python3_to_cpp_converter.o frequencies.o

%.o: $(DIR)%.cpp #$(DIR)$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

EvoMusic: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -rf *.o

delete: clean
	rm -rf EvoMusic
	rm -rf ave_fitness_graph
	rm -rf main_log.txt
	rm -rf *~
	rm -rf $(DIR)*~
	rm -rf main_py_*

help: 
	@echo 'RULES: EvoMusic, clean, delete'
