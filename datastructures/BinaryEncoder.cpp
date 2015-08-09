#include <fstream>
#include <iostream>

#include "../utilities.hpp"
#include "BinaryEncoder.hpp"

const unsigned NUM_CHAR_BITS = 8;

// Outputs bits to a file in characters. Header character is an unsigned int indicating how many bits to ignore in the last
// streamed character
void BinaryEncoder::streamOutBinaryFile(std::ofstream &ofs) {
    if (!ofs) {
        std::cerr << "Could not open file to stream bits to!" << std::endl;
    }
    else {
        unsigned stream_size = this -> getStreamSize();
        unsigned header_byte = NUM_CHAR_BITS - stream_size % NUM_CHAR_BITS;
        header_byte = header_byte == 8 ? 0 : header_byte; // So we don't skip the last byte.
        unsigned buffer_size = 1 + stream_size / NUM_CHAR_BITS;
        if (stream_size % 8 != 0) {
            buffer_size++; //Streams that aren't exact multiples of 8 need one more character.
        }
        char* char_buffer = new char[buffer_size];
        int buffer_index = 0;
        char_buffer[buffer_index++] = header_byte;
        for (int i = 0; i < stream_size; i += NUM_CHAR_BITS) {
            unsigned char char_to_write = 0;
            unsigned num_filling_zeros = NUM_CHAR_BITS;
            for (int j=i;j < stream_size && j < i + NUM_CHAR_BITS; ++j) {
                char_to_write = char_to_write << 1;
                if (m_bits[j]) {
                    char_to_write += 0x01;
                }
                num_filling_zeros--;
            }
            char_buffer[buffer_index++] = char_to_write;
        }
        ofs.write(char_buffer, sizeof(char)*buffer_size);
        delete[] char_buffer;
    }
}

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

// Streams in a character file into the m_bits vector, using a Huffman Binary Tree.
void BinaryEncoder::streamInCharacterFile(std::ifstream &ifs, HBTNode* root) {
    std::map<char, std::vector<bool> > stc_map = Utilities::constructSymbolToCodeMap(root);
    if (!ifs) {
        std::cerr << "Could not open file to stream characters from!" << std::endl;
    }
    else {
        char c;
        while (ifs.get(c)) {
            if (stc_map.find(c) != stc_map.end()) {
                this -> addBits(stc_map[c]);
            }
        }
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