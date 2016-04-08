#***********************************************#
#* Stephen Andersen                    ECE 420 *#
#* 011363024                                   *#
#***********************************************#
CC = g++
DIR = src/C2Wav/
CFLAGS = -lm -g -Wall
DEPS = $(DIR)main.h $(DIR)C2Wav.h $(DIR)make_wav.h \
	$(DIR)../python3_to_cpp_converter.h \
	$(DIR)../song_structs.h $(DIR)../frequencies.h
OBJ = $(DIR)main.o $(DIR)C2Wav.o $(DIR)make_wav.o \
	$(DIR)../python3_to_cpp_converter.o \
	$(DIR)../frequencies.o

%.o: %.cpp #$(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
#$@ is rule name, $< is first arg after

main: $(OBJ)
	$(CC) $(CFLAGS) -o Synthesizer $^

clean:
	rm -rf $(DIR)*.o
	rm -rf $(DIR)../*.o
	rm -rf $(DIR)../../*.o

delete: clean
	rm -rf main
	rm -rf $(DIR)*~

help:
	@echo 'RULES: main, clean, delete'
