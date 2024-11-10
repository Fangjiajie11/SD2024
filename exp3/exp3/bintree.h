#pragma once
#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

struct BinTreeNode {
    char character;
    int frequency;
    BinTreeNode* left;
    BinTreeNode* right;

    BinTreeNode(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};
class BinTree {
public:
    BinTreeNode* root;

    BinTree() : root(nullptr) {}
};
