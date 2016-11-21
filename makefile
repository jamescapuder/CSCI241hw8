all: encode huffman.o

encode: encode.c huffman.o
	gccx -o encode huffman.o encode.c

huffman.o: huffman.c huffman.h
	gccx -c huffman.c
