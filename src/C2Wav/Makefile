#***********************************************#
#* Stephen Andersen                    ECE 420 *#
#* 011363024                                   *#
#***********************************************#
CC = gcc
CFLAGS = -g -Wall -lm
DEPS = main.h C2Wav.h make_wav.h ../song_structs.h ../frequencies.h
OBJ = main.o C2Wav.o make_wav.o ../frequencies.o

%.o: %.c #$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o

delete: clean
	rm -rf main
	rm -rf *~

help:
	@echo 'RULES: main, clean, delete'
