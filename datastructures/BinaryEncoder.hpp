#ifndef BINARYENCODER_H
#define BINARYENCODER_H

#include <vector>
#include <map>
#include <fstream>
#include "HuffmanBinaryTree.hpp"

class BinaryEncoder {
    std::vector<bool> m_bits;

public:
    BinaryEncoder() {}

    friend void streamCharacterOut(BinaryEncoder, std::ofstream &, int);
    void debugPrint(); // DEBUG METHOD DELETE ME
    void streamOutBinaryFile(std::ofstream &);
    void streamInBinaryFile(std::ifstream &);
    void streamOutCharacterFile(std::ofstream &, HBTNode*);
    void streamInCharacterFile(std::ifstream &, HBTNode*);

    void addBit(bool);
    void addBits(std::vector<bool>);
    void removeBit();

    void clearBits();

    unsigned getStreamSize();

};

#endif