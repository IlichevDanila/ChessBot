CC=g++
CFLAGS=-std=c++14 -Iheaders -g3 -O0
LFLAGS=

SOURCES=$(wildcard sources/*.cpp)
OBJS=$(patsubst sources/%.cpp, objs/%.o, $(SOURCES))

all: uci.o main.o $(OBJS)
	$(CC) $(LFLAGS) main.o $(OBJS) -o test
	$(CC) $(LFLAGS) uci.o $(OBJS) -o uci

uci.o: uci.cpp
	$(CC) $(CFLAGS) uci.cpp -c -o uci.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -c -o main.o

objs/%.o: sources/%.cpp headers/%.hpp
	$(CC) $(CFLAGS) $< -c -o $@

clear:
	rm -f test
	rm -f main.o
	cd objs; rm -f *.o
