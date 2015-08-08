#include <fstream>
#include <iostream>
#include <vector>
#include "BinaryEncoder.hpp"

const unsigned NUM_CHAR_BITS = 8;

void streamCharacterOut(BinaryEncoder be, std::ofstream &ofs, int i) {
    unsigned char char_to_write = 0;
    int initial = i;
    int num_filling_zeros = NUM_CHAR_BITS;
    unsigned stream_size = be.getStreamSize();
    for (;i < stream_size && i < initial + NUM_CHAR_BITS; i++) {
        char_to_write = char_to_write << 1;
        if (be.m_bits[i]) {
            char_to_write += 0x01;
        }
        num_filling_zeros--;
    }
    char_to_write = char_to_write << num_filling_zeros;
    ofs.put(char_to_write);
}

// Outputs bits to a file in characters. Header character is an unsigned int indicating how many bits to ignore in the last
// streamed character
void BinaryEncoder::streamOut(std::ofstream &ofs) {
    if (!ofs) {
        std::cerr << "Could not open file to stream bits to!" << std::endl;
    }
    else {
        unsigned stream_size = this -> getStreamSize();
        unsigned header_byte = NUM_CHAR_BITS - stream_size % NUM_CHAR_BITS;
        if (header_byte == 8) {
            header_byte = 0; // Otherwise we won't read the last character.
        }
        ofs.put(header_byte);
        for (int i = 0; i < stream_size; i += NUM_CHAR_BITS) {
            streamCharacterOut(*this, ofs, i);
        }
        ofs.close();
    }
}

// Read in ASCII characters from a text file encoded with a header byte indicating final character length.
void BinaryEncoder::streamIn(std::ifstream &ifs) {
    if (!ifs) {
        std::cerr << "Could not open file to stream bits from!" << std::endl;
    }
    else {
        char c;
        unsigned header_byte;
        bool isHeader = true;
        while (ifs.get(c)) {
            if (isHeader) {
                header_byte = c;
                isHeader = false;
            }
            else {
                for (int i = 1; i <= NUM_CHAR_BITS; i++) {
                    this -> addBit((c >> (NUM_CHAR_BITS - i))  %2);
                }
            }
        }
        while (header_byte) {
            this -> removeBit();
            header_byte--;
        }
        ifs.close();
    }
}

void BinaryEncoder::addBit(bool bit) {
    this -> m_bits.push_back(bit);
}

void BinaryEncoder::removeBit() {
    this -> m_bits.pop_back();
}

// DEBUG METHOD DELETE ME
void BinaryEncoder::debugPrint() {
    for (int i =0; i < this -> m_bits.size(); i++) {
        std::cout << this -> m_bits[i];
    }
    std::cout << std::endl;
}

void BinaryEncoder::addBits(std::vector<bool> bits) {
    for (int i = 0, bit_length=bits.size(); i < bit_length; i++) {
        this -> addBit(bits[i]);
    }
}

void BinaryEncoder::clearBits() {
    this -> m_bits.clear();
}

unsigned BinaryEncoder::getStreamSize() {
    return this -> m_bits.size();
}