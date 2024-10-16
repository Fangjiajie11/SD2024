#include <iostream>
#include <stdexcept>  // for exceptions
#include "stack.h"
#include "vector.h"
#include "area.h"
int main() {
    /*try {
        Stack<int> stack(5);  
        stack.push(10);
        stack.push(20);
        stack.push(30);
        std::cout << "ջ��Ԫ����: " << stack.seetop() << std::endl;  // ���: 30
        std::cout << "ջ�Ĵ�СΪ: " << stack.size() << std::endl;  // ���: 3
        std::cout << "����Ԫ��: " << stack.pop() << std::endl;  // ���: 30
        std::cout << "����Ԫ��: " << stack.pop() << std::endl;  // ���: 20
        std::cout << "ջ�Ĵ�СΪ: " << stack.size() << std::endl;  // ���: 1
        stack.push(40);
        stack.push(50);
        stack.push(60);
        stack.push(70);  
        stack.push(80);

        
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
*/
   
    char expr[] = "(0!+1)^(2*3!+4-5)";  // �������׺���ʽ
    char RPN[100] = "";  // ���ڴ洢ת������沨�����ʽ
    double result = evaluate(expr, RPN);  // ��ֵ������RPN
    std::cout << "������ʽ�� (0!+1)^(2*3!+4-5)" << std::endl;
    std::cout << "�沨�����ʽRPN: " << RPN << std::endl;  // ����沨�����ʽ
    std::cout << "���: " << result << std::endl;  // ���������
 /*
    char expr2[] = "sin(3)";  // �������׺���ʽ
    char RPN2[100] = "";  // ���ڴ洢ת������沨�����ʽ
    double result2 = evaluate(expr2, RPN2);  // ��ֵ������RPN

    std::cout << "RPN2: " << RPN2 << std::endl;  // ����沨�����ʽ
    std::cout << "Result2: " << result2 << std::endl;  // ���������
   */
    std::cout << "========================================================================= " << std::endl;
    std::vector<int> heights1 = { 2, 1, 5, 6, 2, 3 };
    std::cout << "����heights = [2,1,5,6,2,3] " << std::endl;
    int maxArea1 = largestRectangleArea(heights1);
    std::cout << "������ " <<  maxArea1 << std::endl;

    srand(static_cast<unsigned>(time(0))); 
    std::cout << "������ԣ� " << std::endl;
    for (int i = 0; i < 10; ++i) {
        int size = rand() % 105 + 1; // ����������鳤�� [1, 105]
        std::vector<int> heights = generateRandomHeights(size);
        // �������������
        int maxArea = largestRectangleArea(heights);
        
        std::cout << "���� " << i + 1 << ": ������ = " << maxArea  << std::endl;
    }
    
    return 0;
}