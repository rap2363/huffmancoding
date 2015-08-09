#include <fstream>
#include <iostream>
#include <map>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "datastructures/HuffmanBinaryTree.hpp"
#include "datastructures/BinaryEncoder.hpp"
#include "utilities.hpp"

int main(int argc, char *argv[]) {
    std::map<char, int> symbolMap;

    if (argc != 3) {
        std::cout << "Decompressor requires 2 arguments: <compressed_file> <csm_file>" << std::endl;
    }
    else {
        std::string compressed_file_name = argv[1];
        std::string decompressed_file_name = compressed_file_name.substr(0,compressed_file_name.length()-4);
        std::string csm_file_name = argv[2];
        std::ifstream icsm(csm_file_name);
        if (!icsm.is_open()) {
            std::cout << "Could not open file..." << std::endl;
            return 1;
        }
        std::map<char, int> symbolMap;
        boost::archive::binary_iarchive ia(icsm);
        ia >> symbolMap;
        icsm.close();

        HBTNode* huffman_root = Utilities::constructTree(symbolMap);
        BinaryEncoder be;

        std::cout << "Decompressing file..." << std::endl;
        std::ifstream ifbs(compressed_file_name);
        be.streamInBinaryFile(ifbs);
        ifbs.close();

        std::cout << "Writing out decompression..." << std::endl;
        std::ofstream ofs(decompressed_file_name);
        be.streamOutCharacterFile(ofs, huffman_root);
        ofs.close();
    }
}