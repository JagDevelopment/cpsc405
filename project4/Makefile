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
HFILES 	= Vector.${H} Utility.${H} ViewScreen.${H} SceneObj.${H} Scene.${H} Sphere.${H} Plane.${H} Light.${H} PointLight.${H} ParallelLight.${H}
OFILES 	= Vector.o Utility.o ViewScreen.o SceneObj.o Scene.o Sphere.o Plane.o Light.o PointLight.o ParallelLight.o
PROJECT = Raycast
PNAME   = raytrace

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
	
Plane.o: Plane.${C} Plane.${H}
	${CC} $(CFLAGS) -c Plane.${C}
	
SceneObj.o: SceneObj.${C} SceneObj.${H}
	${CC} $(CFLAGS) -c SceneObj.${C}

Scene.o: Scene.${C} Scene.${H}
	${CC} $(CFLAGS) -c Scene.${C}
	
Light.o: Light.${C} Light.${H}
	${CC} $(CFLAGS) -c Light.${C}

PointLight.o: PointLight.${C} PointLight.${H}
	${CC} $(CFLAGS) -c PointLight.${C}
	
ParallelLight.o: ParallelLight.${C} ParallelLight.${H}
	${CC} $(CFLAGS) -c ParallelLight.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm -f core.* *.o *~ ${PNAME} core.*
