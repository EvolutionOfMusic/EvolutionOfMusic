#***********************************************#
#* Stephen Andersen                    ECE 420 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
CFLAGS = -g #-Wall
DEPS = Overhead.h ai_shell.h critic.h ethernet.h song_structs.h frequencies.h python3_to_cpp_converter.h
OBJ =  Overhead.o ai_shell.o critic.o ethernet.o song_structs.o frequencies.o python3_to_cpp_converter.o

%.0: %.cpp #$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

EvoMusic: $(OBJ)
	g++ $(CFLAGS) -o $@ $^

clean: 
	rm -rf *.o

delete: clean
	rm -rf EvoMusic
	rm -rf *~

help: 
	@echo 'RULES: EvoMusic, clean, delete'
