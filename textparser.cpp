#include <fstream>
#include <iostream>
#include <map>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_oarchive.hpp>

int main(int argc, char *argv[]) {
    std::map<char, int> symbolMap;

    if (argc != 3) {
        std::cout << "Text parser requires 2 arguments: <file_to_compress> <symbolMap_out>" << std::endl;
    }
    else {
        std::ifstream file_name(argv[1]);
        if (!file_name.is_open()) {
            std::cout << "Could not open file..." << std::endl;
        }
        else {
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
            std::ofstream ofs(argv[2]);
            boost::archive::binary_oarchive oa(ofs);
            oa << symbolMap;
            ofs.close();
        }
    }
}