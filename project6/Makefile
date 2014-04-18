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
LDFLAGS = -L/usr/local/lib/ -lglut -lGL -lGLU -lMagick++-6.Q16 -lm
HFILES 	= Vector.${H} Utility.${H} ViewScreen.${H} Scene.${H} Light.${H} PointLight.${H} Object.${H} AABBox.${H} BIHTree.${H} Collision.${H}\
	Color.${H} Face.${H} File.${H} Group.${H} ImageFile.${H} Material.${H} OBJFile.${H} Pixmap.${H} PolySurf.${H} MTLFile.${H} Line.${H} Matrix.${H} Ray.${H}
OFILES 	= Vector.o Utility.o ViewScreen.o Scene.o Light.o PointLight.o Object.o AABBox.o PolySurf.o BIHTree.o\
	Color.o Face.o File.o Group.o ImageFile.o Material.o OBJFile.o Pixmap.o MTLFile.o Line.o Matrix.o Ray.o
PROJECT = Raycast
PNAME   = objtrace

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

Scene.o: Scene.${C} Scene.${H}
	${CC} $(CFLAGS) -c Scene.${C}
	
Light.o: Light.${C} Light.${H}
	${CC} $(CFLAGS) -c Light.${C}

PointLight.o: PointLight.${C} PointLight.${H}
	${CC} $(CFLAGS) -c PointLight.${C}
	
Color.o: Color.${C} Color.${H}
	${CC} $(CFLAGS) -c Color.${C}

Face.o: Face.${C} Face.${H}
	${CC} $(CFLAGS) -c Face.${C}

File.o: File.${C} File.${H}
	${CC} $(CFLAGS) -c File.${C}

Group.o: Group.${C} Group.${H}
	${CC} $(CFLAGS) -c Group.${C}

ImageFile.o: ImageFile.${C} ImageFile.${H}
	${CC} $(CFLAGS) -c ImageFile.${C}

Material.o: Material.${C} Material.${H}
	${CC} $(CFLAGS) -c Material.${C}

OBJFile.o: OBJFile.${C} OBJFile.${H}
	${CC} $(CFLAGS) -c OBJFile.${C}

Pixmap.o: Pixmap.${C} Pixmap.${H}
	${CC} $(CFLAGS) -c Pixmap.${C}

Object.o: Object.${C} Object.${H}
	${CC} $(CFLAGS) -c Object.${C}

AABBox.o: AABBox.${C} AABBox.${H}
	${CC} $(CFLAGS) -c AABBox.${C}

PolySurf.o: PolySurf.${C} PolySurf.${H}
	${CC} $(CFLAGS) -c PolySurf.${C}

MTLFile.o: MTLFile.${C} MTLFile.${H}
	${CC} $(CFLAGS) -c MTLFile.${C}

Line.o: Line.${C} Line.${H}
	${CC} $(CFLAGS) -c Line.${C}

BIHTree.o: BIHTree.${C} BIHTree.${H}
	${CC} $(CFLAGS) -c BIHTree.${C}

Matrix.o: Matrix.${C} Matrix.${H}
	${CC} $(CFLAGS) -c Matrix.${C}
	
Ray.o: Ray.${C} Ray.${H}
	${CC} $(CFLAGS) -c Ray.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm -f core.* *.o *~ ${PNAME} core.*
