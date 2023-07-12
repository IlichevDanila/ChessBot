CC=g++
CFLAGS=-std=c++14 -Iheaders
LFLAGS=

SOURCES=$(wildcard sources/*.cpp)
OBJS=$(patsubst sources/%.cpp, objs/%.o, $(SOURCES))

all: main.cpp $(OBJS)
	$(CC) $(CFLAGS) main.cpp -c -o objs/main.o
	$(CC) $(LFLAGS) objs/main.o $(OBJS) -o test

objs/%.o: sources/%.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clear:
	rm -f test
	cd objs; rm -f *.o
