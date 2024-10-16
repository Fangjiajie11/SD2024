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
        std::cout << "栈顶元素是: " << stack.seetop() << std::endl;  // 输出: 30
        std::cout << "栈的大小为: " << stack.size() << std::endl;  // 输出: 3
        std::cout << "弹出元素: " << stack.pop() << std::endl;  // 输出: 30
        std::cout << "弹出元素: " << stack.pop() << std::endl;  // 输出: 20
        std::cout << "栈的大小为: " << stack.size() << std::endl;  // 输出: 1
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
   
    char expr[] = "(0!+1)^(2*3!+4-5)";  // 输入的中缀表达式
    char RPN[100] = "";  // 用于存储转换后的逆波兰表达式
    double result = evaluate(expr, RPN);  // 求值并生成RPN
    std::cout << "输入表达式： (0!+1)^(2*3!+4-5)" << std::endl;
    std::cout << "逆波兰表达式RPN: " << RPN << std::endl;  // 输出逆波兰表达式
    std::cout << "结果: " << result << std::endl;  // 输出计算结果
 /*
    char expr2[] = "sin(3)";  // 输入的中缀表达式
    char RPN2[100] = "";  // 用于存储转换后的逆波兰表达式
    double result2 = evaluate(expr2, RPN2);  // 求值并生成RPN

    std::cout << "RPN2: " << RPN2 << std::endl;  // 输出逆波兰表达式
    std::cout << "Result2: " << result2 << std::endl;  // 输出计算结果
   */
    std::cout << "========================================================================= " << std::endl;
    std::vector<int> heights1 = { 2, 1, 5, 6, 2, 3 };
    std::cout << "输入heights = [2,1,5,6,2,3] " << std::endl;
    int maxArea1 = largestRectangleArea(heights1);
    std::cout << "最大面积 " <<  maxArea1 << std::endl;

    srand(static_cast<unsigned>(time(0))); 
    std::cout << "随机测试： " << std::endl;
    for (int i = 0; i < 10; ++i) {
        int size = rand() % 105 + 1; // 随机生成数组长度 [1, 105]
        std::vector<int> heights = generateRandomHeights(size);
        // 计算最大矩形面积
        int maxArea = largestRectangleArea(heights);
        
        std::cout << "测试 " << i + 1 << ": 最大面积 = " << maxArea  << std::endl;
    }
    
    return 0;
}