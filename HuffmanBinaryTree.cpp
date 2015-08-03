#include "HuffmanBinaryTree.hpp"

HBTNode* HBTNode::getLeft() { return this -> m_left;}
HBTNode* HBTNode::getRight() { return this -> m_right;}
HBTNode* HBTNode::getParent() { return this -> m_parent;}
int HBTNode::getFrequency() { return this -> m_frequency;}
char HBTNode::getSymbol() { return this -> m_symbol;}
bool HBTNode::isLeaf() { return this -> m_leaf;}

void HBTNode::setParent(HBTNode &parent) { this -> m_parent = &parent;}

bool operator < (const HBTNode &lhs, const HBTNode &rhs) {
    return lhs.m_frequency > rhs.m_frequency;
}

bool operator > (const HBTNode &lhs, const HBTNode &rhs) {
    return lhs.m_frequency < rhs.m_frequency;
}