#include <iostream>
#include <queue>
#include <map>
#include "HuffmanBinaryTree.hpp"

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

int main() {
    std::map<char, int> symbolMap;

    symbolMap.insert(std::pair<char, int>('a', 8167));
    symbolMap.insert(std::pair<char, int>('b', 1492));
    symbolMap.insert(std::pair<char, int>('c', 2782));
    symbolMap.insert(std::pair<char, int>('d', 4253));
    symbolMap.insert(std::pair<char, int>('e', 12702));
    symbolMap.insert(std::pair<char, int>('f', 2228));
    symbolMap.insert(std::pair<char, int>('g', 2015));
    symbolMap.insert(std::pair<char, int>('h', 6094));
    symbolMap.insert(std::pair<char, int>('i', 6966));
    symbolMap.insert(std::pair<char, int>('j', 153));
    symbolMap.insert(std::pair<char, int>('k', 772));
    symbolMap.insert(std::pair<char, int>('l', 4025));
    symbolMap.insert(std::pair<char, int>('m', 2406));
    symbolMap.insert(std::pair<char, int>('n', 6749));
    symbolMap.insert(std::pair<char, int>('o', 7507));
    symbolMap.insert(std::pair<char, int>('p', 1929));
    symbolMap.insert(std::pair<char, int>('q', 95));
    symbolMap.insert(std::pair<char, int>('r', 5987));
    symbolMap.insert(std::pair<char, int>('s', 6327));
    symbolMap.insert(std::pair<char, int>('t', 9056));
    symbolMap.insert(std::pair<char, int>('u', 2758));
    symbolMap.insert(std::pair<char, int>('v', 978));
    symbolMap.insert(std::pair<char, int>('w', 2361));
    symbolMap.insert(std::pair<char, int>('x', 150));
    symbolMap.insert(std::pair<char, int>('y', 1974));
    symbolMap.insert(std::pair<char, int>('z', 74));

    debug_printLeafCodes(constructTree(symbolMap));
}

