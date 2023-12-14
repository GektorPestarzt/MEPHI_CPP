CC=g++

SRC_LIBS_DIR=libs

SRC_LIBS := $(shell find ${SRC_LIBS_DIR} -name "*.cpp" | sed -e 's/\.\///')

all: test clean

test: 
	$(CC) $(SRC_LIBS) test.cpp -o test.out
	./test.out

clean:
	rm -rf *.out *.o
