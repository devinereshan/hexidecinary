CC=gcc
CFLAGS=-ansi -pedantic -Wall

bin/num_convert: num_convert.o
	$(CC) $(CFLAGS) -o $@ $^

num_convert.o: num_convert.c

clean:
	$(RM) bin/* *.o
