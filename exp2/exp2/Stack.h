#pragma once
#include <iostream>
#include <stdexcept>  
#include<cmath>
template<typename T>
class Stack {
private:
    T* arr;           
    int top;          
    int capacity;    

public:
    // ���캯������ʼ��ջ
    Stack(int size) {
        arr = new T[size];
        capacity = size;
        top = -1;
    }

    // �����������ͷ��ڴ�
    ~Stack() {
        delete[] arr;
    }

    // ���Ԫ�ص�ջ��
    void push(T value) {
        if (isFull()) {
            throw std::overflow_error("Stack overflow: cannot push, stack is full.");
        }
        arr[++top] = value;
    }

    // ��ջ������Ԫ��
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow: cannot pop, stack is empty.");
        }
        return arr[top--];
    }

    // �鿴ջ��Ԫ��
    T seetop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty: cannot peek.");
        }
        return arr[top];
    }

    // �ж�ջ�Ƿ�Ϊ��
    bool isEmpty() const {
        return top == -1;
    }

    // �ж�ջ�Ƿ�����
    bool isFull() const {
        return top == capacity - 1;
    }

    // ��ȡջ�ĵ�ǰ��С
    int size() const {
        return top + 1;
    }
};

#define N_OPTR 13 // ���������
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE, SIN, COS, TAN, LOG} Operator;

Operator charToOperator(char op) {
    switch (op) {
    case '+': return ADD;
    case '-': return SUB;
    case '*': return MUL;
    case '/': return DIV;
    case '^': return POW;
    case '!': return FAC;
    case '(': return L_P;
    case ')': return R_P;
    case 's': return SIN; 
    case 'c': return COS; 
    case 't': return TAN; 
    case 'l': return LOG; 
    default: return EOE; 
    }
}

const char pri[N_OPTR][N_OPTR] = { // ��������ȵȼ� [ջ��] [��ǰ]
    /*              |-------------------- ��ǰ����� --------------------| */
    /*             +     -     *    /    ^    !    (   )    \0   s    c    t    l  */
    /* --  + */    '>', '>', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>',
    /* |   - */    '>', '>', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>',
    /* ջ  * */    '>', '>', '>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>',
    /* ��  / */    '>', '>', '>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>',
    /* ��  ^ */    '>', '>', '>', '>', '>', '<', '<', '>', '>', '>', '>', '>', '>',
    /* ��  ! */    '>', '>', '>', '>', '>', '>', ' ', '>', '>', '>', '>', '>', '>',
    /* ��  ( */    '<', '<', '<', '<', '<', '<', '<', '=', ' ', ' ', ' ', ' ', ' ',
    /* |   ) */    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /* -- \0 */    '<', '<', '<', '<', '<', '<', '<', ' ', '=', '>', '>', '>', '>',
    /* s */        '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>',
    /* c */        '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>',
    /* t */        '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>',
    /* l */        '<', '<', '<', '<', '<', '<', '<', '>', '>', '>', '>', '>', '>',
};
double factorial(double n) {
    if (n < 0) {
        throw std::invalid_argument("Factorial is not defined for negative numbers.");
    }
    if (n == 0) {
        return 1; 
    }
    double result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i; 
    }
    return result;
}
void readNumber(char*& S, Stack<double>&opnd) {
        double num = 0;
        while (isdigit(*S)) {
            num = num * 10 + (*S - '0'); 
            S++;
        }
        opnd.push(num); 
    }

    void append(char* RPN, double value) {
        // ��������ת��Ϊ�ַ�������ӵ�RPNĩβ
        char buffer[20];
        sprintf_s(buffer, "%.2f ", value); // ��ʽ�����ֲ��ӿո�
        strcat_s(RPN,100, buffer);
    }

    void append(char* RPN, char op) {
        // ���������ӵ�RPNĩβ
        int len = strlen(RPN);
        RPN[len] = op;
        RPN[len + 1] = ' ';  // ����ո�ָ���
        RPN[len + 2] = '\0'; // ��ֹ��
    }

    double calcu(char op, double operand) {
        switch (op) {
        case 's': return sin(operand); 
        case 'c': return cos(operand); 
        case 't': return tan(operand); 
        case 'l': return log(operand); 
        case '!': return factorial(operand); 
        default: return 0; 
        }
    }

    double calcu(double operand1, char op, double operand2) {
        switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        case '^': return pow(operand1, operand2);
        default: return 0;
        }
    }

double evaluate(char* S, char* RPN) { 
    Stack<double> opnd(200); Stack<char> optr(200); 
    optr.push('\0'); 
    while (!optr.isEmpty()) {
        if (isdigit(*S)) {
            readNumber(S, opnd);
            append(RPN, opnd.seetop()); 
        }
        else {
            
           
            char topOp = optr.seetop();
            char currentOp = *S;
            //std::cout << "charToOperator(topOp): " << charToOperator(topOp) << std::endl;
            //std::cout << "charToOperator(currentOp): " << charToOperator(currentOp) << std::endl;
            char relation = pri[charToOperator(topOp)][charToOperator(currentOp)];
            //std::cout << "relation: " << relation << std::endl;
            switch (relation) {
            case '<':
                optr.push(currentOp);
                S++;
                break;
            case '>': {
                char op = optr.pop();
                append(RPN, op);
                if (op == '!' || op == 's' || op == 'c' || op == 't' || op == 'l') {
                    double operand = opnd.pop();
                    opnd.push(calcu(op, operand));
                }
                else if (op == '^') {
                    double exponent = opnd.pop(); // ����ָ��
                    double base = opnd.pop();      // ��������
                    opnd.push(calcu(base, op, exponent)); // ������
                }
                
                else {
                    double opnd2 = opnd.pop();
                    double opnd1 = opnd.pop();
                    opnd.push(calcu(opnd1, op, opnd2));
                }
                break;
            }
            case '=':
                optr.pop();
                S++;
                break;
            default:
                exit(-1);
            }
        }
    }
    return opnd.pop();
}
    