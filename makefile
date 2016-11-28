all: encode decode huffman.o

encode: encode.c huffman.o
	gccx -o encode huffman.o encode.c
decode: decode.c huffman.o
	gccx -o decode huffman.o decode.c
huffman.o: huffman.c huffman.h
	gccx -c huffman.c
clean:
	rm -f encode decode huffman.o
