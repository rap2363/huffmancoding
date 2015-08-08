#ifndef BINARYENCODER_H
#define BINARYENCODER_H

#include <vector>
#include <fstream>

class BinaryEncoder {
    std::vector<bool> m_bits;

public:
    BinaryEncoder() {}

    friend void streamCharacterOut(BinaryEncoder, std::ofstream &, int);
    void debugPrint(); // DEBUG METHOD DELETE ME
    void streamOut(std::ofstream &);
    void streamIn(std::ifstream &);

    void addBit(bool);
    void addBits(std::vector<bool>);
    void removeBit();

    void clearBits();

    unsigned getStreamSize();

};

#endif