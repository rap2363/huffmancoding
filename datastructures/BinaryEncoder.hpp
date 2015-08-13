#ifndef BINARYENCODER_H
#define BINARYENCODER_H

#include <vector>
#include <deque>
#include <map>
#include <map>
#include <fstream>

#include "HuffmanBinaryTree.hpp"

class BinaryEncoder {
    std::deque<bool> m_bits;
    void addBinarySequenceToCharacterBuffer(char* &, const std::vector<bool> &, int &, int &);
public:
    BinaryEncoder() {}

    void debugPrint(); // DEBUG METHOD DELETE ME
    void streamInBinaryFile(std::ifstream &);
    void streamOutCharacterFile(std::ofstream &, HBTNode*);

    void compressToBinary(std::ifstream &, const int, std::ofstream &, const std::map<char, const std::vector<bool> > &);
    void decompressFromBinary(std::ifstream &, std::ofstream &, const HBTNode* &);

    void addBit(bool);
    void addBits(std::vector<bool>);
    void removeBit();

    void clearBits();

    unsigned getStreamSize();

};

#endif