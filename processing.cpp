#include <iostream>
#include <queue>
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

int main() {
    std::priority_queue<HBTNode*, std::vector<HBTNode*>, BinaryTreeNodeComparator> pq;
    char symbols[6] = {'a','b','c','d','e','f'};
    int frequencies[6] = {20, 15, 10, 7, 45, 5};
    for(int i = 0; i < 6; i++) {
        pq.push(new HBTNode(frequencies[i], symbols[i]));
    }
    while(pq.size() > 1) {
        HBTNode* left = pq.top();
        pq.pop();
        HBTNode* right = pq.top();
        pq.pop();
        HBTNode* internal = new HBTNode(left, right);
        left -> setParent(internal);
        right -> setParent(internal);
        pq.push(internal);
    }
    debug_printLeafCodes(pq.top());
}

