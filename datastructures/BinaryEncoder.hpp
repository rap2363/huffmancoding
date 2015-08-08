#ifndef BINARYENCODER_H
#define BINARYENCODER_H

#include <vector>
#include <fstream>

class BinaryEncoder {
    std::vector<bool> m_bits;

public:
    BinaryEncoder() {}

    friend void streamCharacterOut(BinaryEncoder, std::ofstream &, int);
    void streamOut(std::ofstream &);
    void streamIn(std::ifstream &);

    void addBit(bool);
    void addBits(std::vector<bool>);

    void clearBits();

    unsigned getStreamSize();

};

#endif