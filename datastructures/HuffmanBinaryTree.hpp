#ifndef HUFFBINARYTREE_H
#define HUFFBINARYTREE_H

#include <stddef.h>

class HBTNode {
    HBTNode* m_left;
    HBTNode* m_right;
    HBTNode* m_parent;
    int m_frequency;
    char m_symbol;
    bool m_leaf;

public:
    // Initialize the node as a leaf
    HBTNode(int frequency, char symbol) :
    m_left (NULL), m_right (NULL), m_parent (NULL), m_frequency (frequency), m_symbol (symbol), m_leaf (true) { }

    // Initialize the node as a parent
    HBTNode(HBTNode* left, HBTNode* right) :
    m_left (left), m_right (right), m_parent (NULL), m_frequency (left -> getFrequency() + right -> getFrequency()), m_symbol ('\0'), m_leaf (false) { }

    // Getter methods
    HBTNode* getLeft() const;
    HBTNode* getRight() const;
    HBTNode* getParent() const;
    int getFrequency() const;
    char getSymbol() const;
    bool isLeaf() const;

    // Setter method
    void setParent(HBTNode*);

    // Destructor method
    ~HBTNode();
};

#endif