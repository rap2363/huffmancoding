#ifndef HUFFBINARYTREE_H
#define HUFFBINARYTREE_H
#include <iostream>

class HBTNode {
    HBTNode* m_left;
    HBTNode* m_right;
    HBTNode* m_parent;
    const int m_frequency;
    const char m_symbol;
    const bool m_leaf;

public:
    // Initialize the node as a leaf
    HBTNode(int frequency, char symbol) :
    m_left (NULL), m_right (NULL), m_parent (NULL), m_frequency (frequency), m_symbol (symbol), m_leaf (true) { }

    // Initialize the node as a parent
    HBTNode(HBTNode &left, HBTNode& right) :
    m_left (&left), m_right (&right), m_parent (NULL), m_frequency (left.getFrequency() + right.getFrequency()), m_symbol ('\0'), m_leaf (false) { }

    // Getter methods
    HBTNode* getLeft();
    HBTNode* getRight();
    HBTNode* getParent();
    int getFrequency();
    char getSymbol();
    bool isLeaf();

    // Setter method
    void setParent(HBTNode&);
};

#endif