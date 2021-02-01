CC=gcc
DEBUG=-g3
CFLAGS=-ansi -pedantic -Wall
OUTDIR=./bin
PROGNAME=hexidecinary

$(OUTDIR)/$(PROGNAME): $(PROGNAME).o
	$(CC) $(CFLAGS) -o $@ $^

debug: $(PROGNAME).o
	$(CC) $(DEBUG) $(CFLAGS) -o $(OUTDIR)/$(PROGNAME)_debug $^

$(PROGNAME).o: $(PROGNAME).c

clean:
	$(RM) $(OUTDIR)/* *.o
