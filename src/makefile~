#***********************************************#
#* Stephen Andersen                    ECE 420 *#
#* 011363024                                   *#
#***********************************************#

CC = g++
INC_DIR = ../../..
DIR = opencog/opencog/cogserver/server cogutils/opencog/util atomspace/opencog/atomspace
CFLAGS = -I/. $(foreach d, $(DIR), -I/$(INC_DIR)/$$i) #-g -Wall
DEPS = AGIbase.h song_structs.h frequencies.h
OBJ = AGIbase.o song_structs.o frequencies.o
MAKEFILE = build/Makefile
MAKE1 = opencog/$(MAKEFILE)
MAKE2 = cogutils/$(MAKEFILE)
MAKE3 = atomspace/$(MAKEFILE)

include $(INC_DIR)/$(MAKE1) $(INC_DIR)/$(MAKE2) $(INC_DIR)/$(MAKE3)

%.0: %.cpp #$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

AGIbase: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -rf *.o

delete: clean
	rm -rf AGIbase
	rm -rf *~

help:   
	@echo 'Directories:'; 
	@for i in $(DIR); do \
		echo $(INC_DIR)$$i; \
	done;
	@echo '';
	@echo 'RULES: AGIbase, clean, delete';
	@echo ''

