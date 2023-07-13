CC=g++
CFLAGS=-std=c++14 -Iheaders
LFLAGS=

SOURCES=$(wildcard sources/*.cpp)
OBJS=$(patsubst sources/%.cpp, objs/%.o, $(SOURCES))

all: main.o $(OBJS)
	$(CC) $(LFLAGS) objs/main.o $(OBJS) -o test

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -c -o objs/main.o

objs/%.o: sources/%.cpp headers/%.hpp
	$(CC) $(CFLAGS) $< -c -o $@

clear:
	rm -f test
	cd objs; rm -f *.o
