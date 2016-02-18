#***********************************************#
#* Stephen Andersen                    ECE 420 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
INC_DIR = ../../..
CFLAGS = -g -I$(INC_DIR)/.. #-Wall
DEPS = AGIbase.h $(INC_DIR)/CogServer.h $(INC_DIR)/Factory.h $(INC_DIR)/Logger.h $(INC_DIR)/SimpleTruthValue.h song_structs.h frequencies.h
OBJ = AGIbase.o CogServer.o 

%.0: %.cpp #$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

AGIbase: $(OBJ)
	g++ $(CFLAGS) -o $@ $^

clean: 
	rm -rf *.o

delete: clean
	rm -rf AGIbase
	rm -rf *~

help: 
	@echo 'RULES: AGIbase, clean, delete'
