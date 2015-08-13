#include "utilities.hpp"

void Utilities::getLeafCodes(const HBTNode* node, std::map<char, const std::vector<bool> > &stc_map, std::vector<bool> current_code) {
    if (node -> isLeaf()) {
        stc_map.insert(std::pair<char, const std::vector<bool> >(node -> getSymbol(), current_code));
    }
    else {
        if (node -> getLeft() != NULL) {
            current_code.push_back(0);
            getLeafCodes(node -> getLeft(), stc_map, current_code);
            current_code.pop_back();
        }
        if (node -> getRight() != NULL) {
            current_code.push_back(1);
            getLeafCodes(node -> getRight(), stc_map, current_code);
            current_code.pop_back();
        }
    }
}

// Constructs and returns a map of symbols to their respective codes.
std::map<char, const std::vector<bool> > Utilities::constructSymbolToCodeMap(const HBTNode* root) {
    std::map<char, const std::vector<bool> > stc_map;
    std::vector<bool> empty_code;
    if (root -> getLeft() != NULL) {
        empty_code.push_back(0);
        getLeafCodes(root -> getLeft(), stc_map, empty_code);
        empty_code.pop_back();
    }
    if (root -> getRight() != NULL) {
        empty_code.push_back(1);
        getLeafCodes(root -> getRight(), stc_map, empty_code);
        empty_code.pop_back();
    }
    return stc_map;
}

// Constructs a dynamically allocated Huffman Tree from a map of symbols to ints (frequencies).
// Returns a pointer to the root of the constructed tree.
HBTNode* Utilities::constructTree(const std::map<char, int> symbol_frequency_map) {
    std::priority_queue<HBTNode*, std::vector<HBTNode*>, BinaryTreeNodeComparator> pq;
    for (auto iter = symbol_frequency_map.begin(); iter != symbol_frequency_map.end(); iter++) {
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

int Utilities::getNumberOfBits(const std::map<char, const std::vector<bool> > &stc_map, const std::map<char, int > &symbol_map) {
    int number_of_bits = 0;
    for (auto iter = symbol_map.begin(); iter != symbol_map.end(); ++iter) {
        number_of_bits += stc_map.at(iter -> first).size() * symbol_map.at(iter -> first);
    }
    return number_of_bits;
}