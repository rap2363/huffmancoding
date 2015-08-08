#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include "datastructures/HuffmanBinaryTree.hpp"
#include "datastructures/BinaryEncoder.hpp"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_iarchive.hpp>

class BinaryTreeNodeComparator
{
public:
    bool operator() (const HBTNode* lhs, const HBTNode* rhs)
    {
        return lhs -> getFrequency() > rhs -> getFrequency();
    }
};

void debug_searchTree(const HBTNode* node, std::string code) {
    if (node -> isLeaf()) {
        std::cout << node -> getSymbol() << ", " << node -> getFrequency() << ", code: " << code << std::endl;
    }
    else {
        if (node -> getLeft() != NULL) {
            debug_searchTree(node -> getLeft(), code + "0");
        }
        if (node -> getRight() != NULL) {
            debug_searchTree(node -> getRight(), code + "1");
        }
    }
}

// Depth-First Search of the binary tree to print the codes for each symbol.
void debug_printLeafCodes(const HBTNode* root) {
    if (root -> getLeft() != NULL) {
        debug_searchTree(root -> getLeft(), "0");
    }
    if (root -> getRight() != NULL) {
        debug_searchTree(root -> getRight(), "1");
    }
}

// Constructs a Huffman Tree from a map of symbols to ints (frequencies).
HBTNode* constructTree(const std::map<char, int> symbolFrequencyMap) {
    std::priority_queue<HBTNode*, std::vector<HBTNode*>, BinaryTreeNodeComparator> pq;
    for (auto iter = symbolFrequencyMap.begin(); iter != symbolFrequencyMap.end(); iter++) {
        pq.push(new HBTNode(iter -> second, iter -> first));
    }
    while(pq.size() > 1) {
        HBTNode* right = pq.top();
        pq.pop();
        HBTNode* left = pq.top();
        pq.pop();
        HBTNode* internal = new HBTNode(left, right);
        left -> setParent(internal);
        right -> setParent(internal);
        pq.push(internal);
    }
    return pq.top();
}
void getRandomBinarySequence(std::vector<bool> &bits, int n) {
    while (n-- > 0) {
        bits.push_back(rand() % 2);
    }
}

int main(int argc, char *argv[]) {
    std::map<char, int> symbolMap;

    if (argc != 2) {
        std::cerr << "Incorrect Number of arguments!" << std::endl;
        return 0;
    }
    std::ifstream ifs(argv[1]);
    boost::archive::binary_iarchive ia(ifs);
    ia >> symbolMap;
    ifs.close();
    HBTNode* huffman_root = constructTree(symbolMap);
    debug_printLeafCodes(huffman_root);
    BinaryEncoder be;
    std::vector<bool> bits;
    getRandomBinarySequence(bits, 10001);
    be.addBits(bits);
    std::cout << "Initial:    ";
    be.debugPrint();
    std::ofstream ofs("binaryoutfile");
    be.streamOut(ofs);
    be.clearBits();
    std::ifstream ifs2("binaryoutfile");
    be.streamIn(ifs2);
    std::cout << "Round Trip: ";
    be.debugPrint();
}

