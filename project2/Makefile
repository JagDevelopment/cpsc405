#----------------------------------------------
#    Example Makefile for compiling a program that uses
#    the Vector classes
#----------------------------------------------
#
#  Programmer: Donald House
#  Date: March 8, 1999
#
#  Copyright (C) - Donald H. House. 2005
#

CC      = g++
C	= cpp
H	= h
CFLAGS 	= -g `Magick++-config --cppflags`
LFLAGS	= -g `Magick++-config --ldflags`
LDFLAGS = -lglut -lGL -lGLU -lMagick++ -lm
HFILES 	= Vector.${H} Utility.${H} ViewScreen.${H} SceneObj.${H} Scene.${H} Sphere.${H}
OFILES 	= Vector.o Utility.o ViewScreen.o SceneObj.o Scene.o Sphere.o
PROJECT = Raycast
PNAME   = raycast

${PROJECT}:	${PROJECT}.o $(OFILES)
	${CC} $(CFLAGS) -o ${PNAME} ${PROJECT}.o $(OFILES) $(LDFLAGS)

${PROJECT}.o: ${PROJECT}.${C} $(HFILES)
	${CC} $(CFLAGS) -c ${PROJECT}.${C}

Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} $(CFLAGS) -c Utility.${C}

ViewScreen.o: ViewScreen.${C} ViewScreen.${H}
	${CC} $(CFLAGS) -c ViewScreen.${C}

Sphere.o: Sphere.${C} Sphere.${H}
	${CC} $(CFLAGS) -c Sphere.${C}



debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm -f core.* *.o *~ ${PNAME} core.*
