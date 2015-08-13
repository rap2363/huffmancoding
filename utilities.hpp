#ifndef HBT_UTILITIES_H
#define HBT_UTILITIES_H

#include "datastructures/HuffmanBinaryTree.hpp"
#include <stddef.h>
#include <vector>
#include <map>
#include <queue>

class Utilities {
private:
    Utilities() {}

    class BinaryTreeNodeComparator {
    public:
        bool operator() (const HBTNode* lhs, const HBTNode* rhs)
        {
            return lhs -> getFrequency() > rhs -> getFrequency();
        }
    };

    static void getLeafCodes(const HBTNode*, std::map<char, const std::vector<bool> > &, std::vector<bool>);

public:

    // Constructs and returns a map of symbols to their respective codes.
    static std::map<char, const std::vector<bool> > constructSymbolToCodeMap(const HBTNode* );

    // Calculates the total number of bits required for a compression.
    static int getNumberOfBits(const std::map<char, const std::vector<bool> > &, const std::map<char, int > &);

    // Constructs a dynamically allocated Huffman Tree from a map of symbols to ints (frequencies).
    // Returns a pointer to the root of the constructed tree.
    static HBTNode* constructTree(const std::map<char, int>);
};

#endif