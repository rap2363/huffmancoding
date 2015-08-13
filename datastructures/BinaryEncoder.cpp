#include <fstream>
#include <iostream>

#include "../utilities.hpp"
#include "BinaryEncoder.hpp"

const unsigned NUM_CHAR_BITS = 8;
// Read in ASCII characters from a text file encoded with a header byte indicating how many bits to ignore in the last byte.
void BinaryEncoder::streamInBinaryFile(std::ifstream &ifs) {
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
    }
}

// Streams out to a character file from the bits in the m_bits vector, using a Huffman Binary Tree.
void BinaryEncoder::streamOutCharacterFile(std::ofstream &ofs, HBTNode* root) {
    if (!ofs) {
        std::cerr << "Could not open file to stream characters to!" << std::endl;
    }
    else {
        HBTNode* currentNode = root;
        for (auto iter = m_bits.begin(); iter != m_bits.end(); ++iter) {
            currentNode = *iter ? currentNode -> getRight() : currentNode -> getLeft();
            if (currentNode -> isLeaf()) {
                ofs.put(currentNode -> getSymbol());
                currentNode = root;
            }
        }
    }
}

void BinaryEncoder::addBinarySequenceToCharacterBuffer(char* &char_buffer, const std::vector<bool> &bits, int &buffer_index, int &bit_index) {
    unsigned char last_buffer_char = bit_index % NUM_CHAR_BITS == 0 ? 0 : char_buffer[buffer_index];
    unsigned char char_to_write = last_buffer_char;
    for (auto iter = bits.begin(); iter != bits.end(); iter++) {
        char_to_write = char_to_write << 1;
        bit_index++;
        if (*iter) {
            char_to_write += 0x01;
        }
        if (bit_index % NUM_CHAR_BITS == 0) {
            char_buffer[buffer_index++] = char_to_write;
            last_buffer_char = 0;
            char_to_write = 0;
        }
    }
    char_buffer[buffer_index] = char_to_write;
}

void BinaryEncoder::compressToBinary(std::ifstream &char_fs, const int bit_stream_size, std::ofstream &bin_fs, const std::map<char, const std::vector<bool> >  &stc_map) {
    if (!char_fs) {
        std::cerr << "Could not open file to stream characters from!" << std::endl;
        return;
    }
    unsigned header_byte = NUM_CHAR_BITS - bit_stream_size % NUM_CHAR_BITS;
    header_byte = header_byte == 8 ? 0 : header_byte; // So we don't skip the last byte.
    unsigned buffer_size = 1 + bit_stream_size / NUM_CHAR_BITS;
    if (bit_stream_size % 8 != 0) {
        buffer_size++; //Streams that aren't exact multiples of 8 need one more character.
    }
    char* char_buffer = new char[buffer_size];
    int buffer_index = 0;
    int bit_index = NUM_CHAR_BITS; // Set index to right after the header
    char_buffer[buffer_index++] = header_byte;

    char c;
    while (char_fs.get(c)) {
        if (stc_map.find(c) != stc_map.end()) {
            this -> addBinarySequenceToCharacterBuffer(char_buffer, stc_map.at(c), buffer_index, bit_index);
        }
    }

    char_buffer[buffer_index] = char_buffer[buffer_index] << header_byte;

    if (!bin_fs) {
        std::cerr << "Could not open file to stream bits to!" << std::endl;
        return;
    }
    bin_fs.write(char_buffer, sizeof(char)*buffer_size);
    delete[] char_buffer;
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