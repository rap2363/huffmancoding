#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_iarchive.hpp>

int main(int argc, char *argv[]) {
    std::map<char, int> symbolMap;

    if (argc != 3) {
        std::cerr << "Incorrect number of arguments provided to compressor!" << std::endl;
        std::cerr << "Correct Usage: ./compress <file> <symbolMap> <outputFile>";
        return 0;
    }
    std::ifstream file_name(argv[1]);
    if (!file_name.is_open()) {
        std::cout << "Could not open file..." << std::endl;
        return 0;
    }
    char c;
    while (file_name.get(c)) {
        auto key_value = symbolMap.find(c);
        if (key_value == symbolMap.end()) {
            symbolMap.insert(std::pair<char, int>(c, 1));
        }
        else {
            key_value -> second++;
        }
    }
    std::ifstream ifs(argv[2]);
    boost::archive::binary_iarchive ia(ifs);
    symbolMap << ia;
    ifs.close();
    std::ifstream ifs(argv[1]);

    // Read in text file and encode to character stream
    std::vector<char> binaryStream;
    while (file_name.get(c)) {

    }
}