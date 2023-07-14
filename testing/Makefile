CC=g++
CFLAGS=-std=c++14 -I../headers
LFLAGS=

SOURCES=$(wildcard sources/*.cpp)
OBJS=$(wildcard ../objs/*.o)
EXE=$(patsubst sources/%.cpp, %.exe, $(SOURCES))

all: $(EXE)

%.exe: sources/%.cpp
	$(CC) $(CFLAGS) $< -c -o temp.o
	$(CC) $(LFLAGS) temp.o $(OBJS) -o $@

clear:
	rm -f *.exe