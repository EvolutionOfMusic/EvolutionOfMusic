#***********************************************#
#* Stephen Andersen                    ECE 492 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
DIR = ./src/
CFLAGS = -g -Wall -I/src -fopenmp
DEPS = Overhead.h ai_shell.h critic_shell.h sd.h python3_to_cpp_converter.h song_structs.h frequencies.h
OBJ = Overhead.o ai_shell.o critic_shell.o sd.o python3_to_cpp_converter.o song_structs.o frequencies.o

%.0: %.cpp #$(DIR)$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

EvoMusic: $(DIR)$(OBJ)
	g++ $(CFLAGS) -o $@ $^

Overhead.o: Overhead.h critic_shell.h ai_shell.h
ai_shell.o: python3_to_cpp_converter.h sd.h song_structs.h
critic_shell.o: song_structs.h frequencies.h
sd.o: song_structs.h
python3_to_cpp_converter.o: song_structs.h
song_structs.o: frequencies.h
#frequencies.o: NOTHING

clean: 
	rm -rf *.o

delete: clean
	rm -rf EvoMusic
	rm -rf *~

help: 
	@echo 'RULES: EvoMusic, clean, delete'
