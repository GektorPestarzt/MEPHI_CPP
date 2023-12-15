CC=g++

SRC_LIBS_DIR=libs
SRC_TEST_DIR=.

SRC_LIBS := $(shell find ${SRC_LIBS_DIR} -name "*.cpp" | sed -e 's/\.\///')
SRC_TEST := $(SRC_TEST_DIR)/test.cpp

all: test clean

test: 
	$(CC) $(SRC_LIBS) $(SRC_TEST) -o test.out
	./test.out

main:
	$(CC) $(SRC_LIBS) main.cpp -o main.out
	./main.out

clean:
	rm -rf *.out *.o