# Huffman Encoding

The algorithm is divided into the following steps:
- Stream in data from a text file and record a map of symbols with their number of occurences (e.g. map<char,int>)
- Create Binary Tree nodes for each of the symbols as leaves with their respective frequencies and store them
in a priority queue where they are arranged with lowest frequency --> highest priority.
- Pop two nodes from the queue and create an internal node for them with the frequency being the sum of the two
nodes. Add the internal node back into the priority queue.
- Have the two nodes point to the internal node as its children (left and right). Repeat this procedure until there is just one node (root) left.

## Compiling
Until we have a Makefile:
```sh
$ g++ -c HuffmanBinaryTree.cpp
$ g++ -c processing.cpp
$ g++ HuffmanBinaryTree.o processing.o -o out
```

## Running
After building:
```sh
$ ./out
```