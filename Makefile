#***********************************************#
#* Stephen Andersen                    ECE 492 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
CFLAGS = -g -I/src #-Wall
DEPS = Overhead.h ai_shell.h critic.h sd.h song_structs.h frequencies.h python3_to_cpp_converter.h
OBJ =  Overhead.o ai_shell.o critic.o sd.o song_structs.o frequencies.o python3_to_cpp_converter.o

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
