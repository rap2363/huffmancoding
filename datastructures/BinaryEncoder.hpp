#ifndef BINARYENCODER_H
#define BINARYENCODER_H

#include <vector>
#include <deque>
#include <map>
#include <map>
#include <fstream>

#include "HuffmanBinaryTree.hpp"

class BinaryEncoder {
    static void addBinarySequenceToCharacterBuffer(char* &, const std::vector<bool> &, int &, int &);
public:
    BinaryEncoder() {}

    static void compressToBinary(std::ifstream &, const int, std::ofstream &, const std::map<char, const std::vector<bool> > &);
    static void decompressFromBinary(std::ifstream &, std::ofstream &, const HBTNode* &);
};

#endif