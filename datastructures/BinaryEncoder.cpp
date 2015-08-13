#include <fstream>
#include <iostream>

#include "../utilities.hpp"
#include "BinaryEncoder.hpp"

const unsigned NUM_CHAR_BITS = 8;

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

void BinaryEncoder::decompressFromBinary(std::ifstream &bin_fs, std::ofstream &char_fs, const HBTNode* &huffman_root) {
    if (!bin_fs) {
        std::cerr << "Could not open file to decompress!" << std::endl;
        return;
    }

    unsigned buffer_size = bin_fs.tellg();
    int buffer_index = 0;
    std::vector<char> char_buffer;
    char c;
    bool isHeader = true;
    unsigned header_byte;
    unsigned offset = 0;
    bool direction;
    const HBTNode* huffman_ptr = huffman_root;
    while (bin_fs.get(c)) {
        if (isHeader) {
            header_byte = c;
            isHeader = false;
            continue;
        }
        if (++buffer_index == buffer_size) {
            offset = header_byte;
        }
        for (int i = 1; i <= NUM_CHAR_BITS - offset; i++) {
            bool direction = (c >> (NUM_CHAR_BITS - i))  % 2;
            huffman_ptr = direction ? huffman_ptr -> getRight() : huffman_ptr -> getLeft();
            if (huffman_ptr -> isLeaf()) {
                char_buffer.push_back(huffman_ptr -> getSymbol());
                huffman_ptr = huffman_root;
            }
        }
    }
    char_fs.write(&char_buffer[0], sizeof(char)*char_buffer.size());
}