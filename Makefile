OUT=binarnic
CC=gcc
CFLAGS=-c -std=c11 -O2
OBJS=main.o lexer.o parser.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

lexer.o: lexer.c
	$(CC) $(CFLAGS) lexer.c

parser.o: parser.c
	$(CC) $(CFLAGS) parser.c

build: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) 

run: build
	./$(OUT)