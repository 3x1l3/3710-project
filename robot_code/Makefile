INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib/

COMPILERFLAGS = -Wall
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

All: robot

robot: robot.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)

