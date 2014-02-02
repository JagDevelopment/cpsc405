#--------------------------------------------------------------
#    Example Makefile for compiling programs that use
#    the Matrix and Vector classes.
#
#    The setup is to compile both example, and exampleSVD
#    example uses only the Vector classes
#    exampleSVD uses both Matrix and Vector classes
#
#    For a project using only Vector classes, all the
#    lines referring to Matrix can be omitted
#
#--------------------------------------------------------------
#
#  Programmer: Donald House
#  Date: March 8, 1999
#
#  Copyright (C) - Donald H. House. 2005
#

CC  = g++
C	= cpp
H	= h
CFLAGS 	= -g
LDFLAGS = -lm
HFILES 	= Vector.${H} Utility.${H}
OFILES 	= Vector.o Utility.o
PROJECT = example

${PROJECT}:	${PROJECT}.o $(OFILES)
	${CC} $(CFLAGS) -o ${PROJECT} ${PROJECT}.o $(OFILES) $(LDFLAGS)

${PROJECT}.o: ${PROJECT}.${C} $(HFILES)
	${CC} $(CFLAGS) -c ${PROJECT}.${C}

exampleSVD:	exampleSVD.o Matrix.o $(OFILES) 
	${CC} $(CFLAGS) -o exampleSVD exampleSVD.o Matrix.o $(OFILES) $(LDFLAGS)

exampleSVD.o: exampleSVD.${C} Matrix.${H} $(HFILES)  
	${CC} $(CFLAGS) -c exampleSVD.${C}

Matrix.o: Matrix.${C} Matrix.${H} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Matrix.${C}

Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} $(CFLAGS) -c Utility.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm -f *.o *~ ${PROJECT} exampleSVD

