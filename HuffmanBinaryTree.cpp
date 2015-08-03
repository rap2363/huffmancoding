#include "HuffmanBinaryTree.hpp"

HBTNode* HBTNode::getLeft() const { return this -> m_left;}
HBTNode* HBTNode::getRight() const { return this -> m_right;}
HBTNode* HBTNode::getParent() const { return this -> m_parent;}
int HBTNode::getFrequency() const { return this -> m_frequency;}
char HBTNode::getSymbol() const { return this -> m_symbol;}
bool HBTNode::isLeaf() const { return this -> m_leaf;}

void HBTNode::setParent(HBTNode* parent) { this -> m_parent = parent;}

// Delete the children
HBTNode::~HBTNode() {
    if (m_left != NULL) {
        delete m_left;
    }
    if (m_right != NULL) {
        delete m_right;
    }
}