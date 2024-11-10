#include <queue>
#include <unordered_map>

struct compare {
    bool operator()(BinTreeNode* l, BinTreeNode* r) {
        return l->frequency > r->frequency; // 最小堆
    }
};

class HuffTree {
public:
    BinTreeNode* root;

    HuffTree(const std::unordered_map<char, int>& frequencies) {
        std::priority_queue<BinTreeNode*, std::vector<BinTreeNode*>, compare> minHeap;

        // 创建叶子节点并加入优先队列
        for (const auto& pair : frequencies) {
            minHeap.push(new BinTreeNode(pair.first, pair.second));
        }

        // 构建 Huffman 树
        while (minHeap.size() != 1) {
            BinTreeNode* left = minHeap.top(); minHeap.pop();
            BinTreeNode* right = minHeap.top(); minHeap.pop();

            BinTreeNode* newNode = new BinTreeNode('\0', left->frequency + right->frequency);
            newNode->left = left;
            newNode->right = right;
            minHeap.push(newNode);
        }
        root = minHeap.top();
    }
};