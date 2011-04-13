INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib/

COMPILERFLAGS = -Wall -g
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
OBJS = cameratest.o camera.o  building.o ConeBuilding.o SphereBuilding.o TorusBuilding.o SquareBuilding.o Pylon.o cityblock.o CityManager.o robot.o 

all: cameratest

.depend: $(OBJS:.o=.cpp) $(wildcard *.h) Makefile
	rm -f .depend
	$(CC) $(CFLAGS) -MM $(OBJS:.o=.cpp) >> ./.depend

include .depend

cameratest: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^  $(LIBDIR) $(LIBRARIES)

Pylon.o : building.o
SphereBuilding.o : building.o
TorusBuilding.o : building.o
ConeBuilding.o : building.o
SquareBuilding.o : building.o

cityblock.o : building.o
cityblock.o : ConeBuilding.o

CityManager.o : cityblock.o

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY : clean clean-all

clean:
	rm -rf *~ *.o

clean-all: clean
	rm -rf bank
