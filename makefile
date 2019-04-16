CC=gcc
CFLAGS=-c

LIBSRC=./lib/src/
LIB=./lib/

OBJECTS=main.o term.o lbrnth.o
EXECUTABLE=a.exe

all: $(EXECUTABLE)

clean:
	DEL *.o
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

term.o: $(LIBSRC)term.c
	$(CC) $(CFLAGS) $(LIBSRC)term.c

lbrnth.o: $(LIBSRC)lbrnth.c
	$(CC) $(CFLAGS) $(LIBSRC)lbrnth.c
