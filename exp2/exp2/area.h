#include <iostream>
#include <vector>
#include "Stack.h"
#include <algorithm>
#include <cstdlib> // 用于随机数生成

// 计算最大矩形面积的函数
int largestRectangleArea(const std::vector<int>& heights) {
    Stack<int> indices(200); // 存储柱子的索引
    int maxArea = 0; // 记录最大面积
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        int currentHeight = (i == n) ? 0 : heights[i]; // 如果到达末尾，设当前高度为0
        while (!indices.isEmpty() && heights[indices.seetop()] > currentHeight) {
            int height = heights[indices.seetop()];
            indices.pop();
            int width = indices.isEmpty() ? i : i - indices.seetop() - 1; // 计算宽度
            maxArea = std::max(maxArea, height * width); // 更新最大面积
        }
        indices.push(i); // 将当前索引压入栈中
    }

    return maxArea;
}

// 随机生成测试数据
std::vector<int> generateRandomHeights(int size) {
    std::vector<int> heights(size);
    for (int i = 0; i < size; ++i) {
        heights[i] = rand() % 104; // 随机生成高度，范围为 [0, 10^4]
    }
    return heights;
}

