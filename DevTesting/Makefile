INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib/

COMPILERFLAGS = -Wall -g
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
OBJS = cameratest.o camera.o building.o cityblock.o robot.o

all: cameratest

.depend: $(OBJS:.o=.cpp) $(wildcard *.h) Makefile
	rm -f .depend
	$(CC) $(CFLAGS) -MM $(OBJS:.o=.cpp) >> ./.depend

include .depend

cameratest: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^  $(LIBDIR) $(LIBRARIES)

cityblock.o : building.o

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY : clean clean-all

clean:
	rm -rf *~ *.o

clean-all: clean
	rm -rf bank
