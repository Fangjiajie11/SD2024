#pragma once
class HuffmanCoder {
private:
    HuffTree* huffTree;
    std::unordered_map<char, std::string> huffmanCodes;

    void generateCodes(BinTreeNode* root, const std::string& str) {
        if (!root) return;
        if (root->left == nullptr && root->right == nullptr) {
            huffmanCodes[root->character] = str;
        }
        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }

public:
    HuffmanCoder(const std::unordered_map<char, int>& frequencies) {
        huffTree = new HuffTree(frequencies);
        generateCodes(huffTree->root, "");
    }

    ~HuffmanCoder() {
        delete huffTree;
    }

    void printCodes() {
        for (const auto& pair : huffmanCodes) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    std::string encode(const std::string& word) {
        std::string encoded = "";
        for (char c : word) {
            encoded += huffmanCodes[c];
        }
        return encoded;
    }
};