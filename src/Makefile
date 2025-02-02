# $ID:$
# -*- coding:utf-8

CC = g++
TARGET = main
GTK4FLAGS = `pkg-config gtk4 --cflags`
GTK4LIBS = `pkg-config gtk4 --libs`

$(TARGET):main.o main_frame.o data.o my_cv.o
	$(CC) -o main main.o main_frame.o data.o my_cv.o $(GTK4LIBS)
main.o: main.cpp main_frame.hpp
	$(CC) -c main.cpp $(GTK4FLAGS)
main_frame.o: main_frame.cpp main_frame.hpp
	$(CC) -c main_frame.cpp $(GTK4FLAGS)
data.o: ../../CV/src/data.cpp ../../CV/src/data.hpp
	$(CC) -c ../../CV/src/data.cpp
my_cv.o: ../../CV/src/my_cv.cpp ../../CV/src/my_cv.hpp
	$(CC) -c ../../CV/src/my_cv.cpp

.PHONY: clean

clean:
	rm *.o
