#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex {
public:
    int real;
    int imag;

    Complex(int r = 0.0, int i = 0.0) : real(r), imag(i) {}

    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator<(const Complex& other) const {
        if (modulus() == other.modulus()) {
            return real < other.real; // ����ʵ���Ƚ�
        }
        return modulus() < other.modulus(); // ����ģ�Ƚ�
    }
    bool operator>(const Complex& other) const {
        return !(*this < other) && !(*this == other); // ʹ���Ѷ���������
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

#endif // COMPLEX_H
