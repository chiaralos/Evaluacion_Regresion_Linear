# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation

CC=g++
#-ansi -pedantic -std=c++11
CFLAGS=-c -Wall 

all: examen_final

examen_final: main.o linearregression.o extractiondata.o
	$(CC) main.o linearregression.o extractiondata.o -o examen_final

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

linearregression.o: LinearRegression/linearregression.h LinearRegression/linearregression.cpp
	$(CC) $(CFLAGS) LinearRegression/linearregression.cpp

extractiondata.o: ExtractionData/extractiondata.h ExtractionData/extractiondata.cpp
	$(CC) $(CFLAGS) ExtractionData/extractiondata.cpp

clean:
	rm -rf *o examen_final
