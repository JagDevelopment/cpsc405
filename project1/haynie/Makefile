# Makefile - imgview
# Name: Kevin Haynie
# Date: 1/18/2014
# Project: 1
# Filename: Makefile
#
# Adapted from Dr. Donald House's example makefile, given in the archive located
# at http://people.cs.clemson.edu/~dhouse/courses/405/examples/glmagick.zip
# Usage:
# make          -- build application binary
# make clean    -- clean binary and object files created by make

CC		= g++
C		= cpp

CFLAGS		= -g `Magick++-config --cppflags`
LFLAGS		= -g `Magick++-config --ldflags`

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lGLU -lMagick++ -lm
  endif
endif

PROJECT		= imgview

${PROJECT}:	${PROJECT}.o
	${CC} ${LFLAGS} -o ${PROJECT} ${PROJECT}.o ${LDFLAGS}

${PROJECT}.o:	${PROJECT}.${C}
	${CC} ${CFLAGS} -c ${PROJECT}.${C}

clean:
	rm -f core.* *.o *~ ${PROJECT}
