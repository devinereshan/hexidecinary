CC=gcc
CFLAGS=-ansi -pedantic -Wall
OUTDIR=./bin
PROGNAME=hexidecinary

$(OUTDIR)/$(PROGNAME): $(PROGNAME).o
	$(CC) $(CFLAGS) -o $@ $^

$(PROGNAME).o: $(PROGNAME).c

clean:
	$(RM) $(OUTDIR)/* *.o
