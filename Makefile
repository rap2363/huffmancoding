CC=g++
CFLAGS=-c
BOOSTFLAG=-lboost_serialization

all: compress decompress

compress: datastructures/HuffmanBinaryTree.o datastructures/BinaryEncoder.o utilities.o compress.o
	$(CC) datastructures/HuffmanBinaryTree.o datastructures/BinaryEncoder.o utilities.o compress.o -o compress $(BOOSTFLAG)

decompress: datastructures/HuffmanBinaryTree.o datastructures/BinaryEncoder.o utilities.o decompress.o
	$(CC) datastructures/HuffmanBinaryTree.o datastructures/BinaryEncoder.o utilities.o decompress.o -o decompress $(BOOSTFLAG)

compress.o: compress.cpp
	$(CC) $(CFLAGS) compress.cpp

decompress.o: decompress.cpp
	$(CC) $(CFLAGS) decompress.cpp

utilities.o: utilities.cpp utilities.hpp
	$(CC) $(CFLAGS) utilities.cpp

datastructures/HuffmanBinaryTree.o: datastructures/HuffmanBinaryTree.cpp datastructures/HuffmanBinaryTree.hpp
	$(CC) $(CFLAGS) datastructures/HuffmanBinaryTree.cpp -o datastructures/HuffmanBinaryTree.o

datastructures/BinaryTree.o: datastructures/BinaryTree.cpp datastructures/BinaryTree.hpp
	$(CC) $(CFLAGS) datastructures/BinaryTree.cpp -o datastructures/BinaryTree.o

.PHONY: clean

clean:
	rm *.o bin/* datastructures/*.o