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

// Debug method, delete me!
void getRandomBinarySequence(std::vector<bool> &bits, int n) {
    while (n-- > 0) {
        bits.push_back(rand() % 2);
    }
}

int main(int argc, char *argv[]) {
    std::map<char, int> symbolMap;
    if (argc != 3) {
        std::cerr << "Processor requires 2 arguments: <file_to_decompress> <symbolMap>" << std::endl;
        return 0;
    }
    std::ifstream ifs(argv[2]);
    boost::archive::binary_iarchive ia(ifs);
    ia >> symbolMap;
    ifs.close();

    HBTNode* huffman_root = constructTree(symbolMap);
    debug_printLeafCodes(huffman_root);

    std::cout << "Compressing File..." << std::endl;
    BinaryEncoder be;
    std::ifstream ifRead(argv[1]);
    be.streamInCharacterFile(ifRead, huffman_root);
    ifRead.close();

    std::cout << "Writing out compression" << std::endl;
    std::ofstream obfs("binaryoutfile", std::ios::out | std::ios::binary);
    be.streamOutBinaryFile(obfs);
    obfs.close();

    std::cout << "Round tripping" << std::endl;
    std::ofstream ofs("charoutfile");
    be.streamOutCharacterFile(ofs, huffman_root);
    ofs.close();
}

