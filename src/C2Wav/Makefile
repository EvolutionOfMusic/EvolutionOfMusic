#***********************************************#
#* Stephen Andersen                    ECE 420 *#
#* 011363024                                   *#
#***********************************************#
CC = g++
CFLAGS = -lm -g -Wall
DEPS = main.h C2Wav.h make_wav.h \
	../python3_to_cpp_converter.h \
	../song_structs.h ../frequencies.h
OBJ = main.o C2Wav.o make_wav.o \
	../python3_to_cpp_converter.o \
	../frequencies.o

%.o: %.cpp #$(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
#$@ is rule name, $< is first arg after

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o
	rm -rf ../*.o
	rm -rf ../../*.o

delete: clean
	rm -rf main
	rm -rf *~

help:
	@echo 'RULES: main, clean, delete'
