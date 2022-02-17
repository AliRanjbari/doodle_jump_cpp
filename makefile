CC := g++ -std=c++11
CCFLAG += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: doodleJump.out

doodleJump.out: main.o rsdl.o class.o
	$(CC) main.o rsdl.o class.o $(CCFLAG) -o doodleJump.out

main.o: main.cpp class.hpp
	$(CC) -c main.cpp -o main.o

class.o: class.cpp src/rsdl.hpp class.hpp
	$(CC) -c class.cpp -o class.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o *.out
