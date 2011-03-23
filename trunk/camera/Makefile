INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib/

COMPILERFLAGS = -Wall -g
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
OBJS = cameratest.o camera.o

all: cameratest

.depend: $(OBJS:.o=.cpp) $(wildcard *.h) Makefile
Print out some helpful information here.

	rm -f .depend
	$(CC) $(CFLAGS) -MM $(OBJS:.o=.cpp) >> ./.depend

include .depend

cameratest: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^  $(LIBDIR) $(LIBRARIES)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY : clean clean-all

clean:
	rm -rf *~ *.o

clean-all: clean
	rm -rf bank
