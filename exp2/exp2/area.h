#include <iostream>
#include <vector>
#include "Stack.h"
#include <algorithm>
#include <cstdlib> // �������������

// ��������������ĺ���
int largestRectangleArea(const std::vector<int>& heights) {
    Stack<int> indices(200); // �洢���ӵ�����
    int maxArea = 0; // ��¼������
    int n = heights.size();

    for (int i = 0; i <= n; ++i) {
        int currentHeight = (i == n) ? 0 : heights[i]; // �������ĩβ���赱ǰ�߶�Ϊ0
        while (!indices.isEmpty() && heights[indices.seetop()] > currentHeight) {
            int height = heights[indices.seetop()];
            indices.pop();
            int width = indices.isEmpty() ? i : i - indices.seetop() - 1; // ������
            maxArea = std::max(maxArea, height * width); // ����������
        }
        indices.push(i); // ����ǰ����ѹ��ջ��
    }

    return maxArea;
}

// ������ɲ�������
std::vector<int> generateRandomHeights(int size) {
    std::vector<int> heights(size);
    for (int i = 0; i < size; ++i) {
        heights[i] = rand() % 104; // ������ɸ߶ȣ���ΧΪ [0, 10^4]
    }
    return heights;
}

