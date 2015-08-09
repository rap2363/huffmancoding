#include <fstream>
#include <iostream>
#include <map>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "datastructures/HuffmanBinaryTree.hpp"
#include "datastructures/BinaryEncoder.hpp"
#include "utilities.hpp"

int main(int argc, char *argv[]) {
    std::map<char, int> symbolMap;

    if (argc != 2) {
        std::cout << "Compressor requires a file to compress!" << std::endl;
    }
    else {
        std::string original_file_name = argv[1];
        std::ifstream ifs(original_file_name);
        if (!ifs.is_open()) {
            std::cout << "Could not open file..." << std::endl;
            return 1;
        }
        char c;
        while (ifs.get(c)) {
            auto key_value = symbolMap.find(c);
            if (key_value == symbolMap.end()) {
                symbolMap.insert(std::pair<char, int>(c, 1));
            }
            else {
                key_value -> second++;
            }
        }
        std::ofstream ocsmfs(original_file_name+".csm");
        boost::archive::binary_oarchive oa(ocsmfs);
        oa << symbolMap;
        ocsmfs.close();

        HBTNode* huffman_root = Utilities::constructTree(symbolMap);

        ifs.clear() ;
        ifs.seekg(0, std::ios::beg) ;
        std::cout << "Compressing File..." << std::endl;
        BinaryEncoder be;
        be.streamInCharacterFile(ifs, huffman_root);
        ifs.close();

        std::cout << "Writing out compression" << std::endl;
        std::ofstream obfs(original_file_name+".bin", std::ios::out | std::ios::binary);
        be.streamOutBinaryFile(obfs);
        obfs.close();
    }
}