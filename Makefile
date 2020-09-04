PROGRAM = scena
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include -std=c99
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): scena.o funkcije.o objekti.o pozivnefunkcije.o image.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) scena.o funkcije.o funkcije.h objekti.o objekti.h pozivnefunkcije.o pozivnefunkcije.h image.o image.h makroipromenljive.h $(LDLIBS)

.PHONY: beauty clean dist

beauty:
	-indent -nut -kr scena.c
	-rm *~ *BAK

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
