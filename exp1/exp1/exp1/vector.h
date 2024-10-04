#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <chrono> // �����߾��ȼ�ʱ��
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>
#include <vector>

#define DEFAULT_CAPACITY 3

typedef int Rank;

template <typename T>
class Vector {
protected:
    Rank _size;
    int _capacity;
    T* _elem;

    void expand();
    void shrink();
    void swap(T& e1, T& e2);

public:
    explicit Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);
    //~Vector() { delete[] _elem; }
    
    
    T& operator[](Rank r) const {
        return _elem[r];
    }
    T* begin() { return _elem; }
    T* end() { return _elem + _size; }
    Rank size() const { return _size; }
    bool isEmpty() const { return _size == 0; }

    void add(const T& e);
    void remove(const T& e);
    void unique();
    void shuffle();
    void sortByModulus();
    void sortByModulus2();
    void insert(Rank r, const T& e);  
    void bubbleSort();
    void mergeSort(int left, int right);
    void print() const;

private:
    void merge(int left, int mid, int right);
};

template <typename T>
Vector<T>::Vector(int c, int s, T v) {
    _capacity = c;
    _size = s;
    _elem = new T[_capacity];
    for (int i = 0; i < s; ++i) {
        _elem[i] = v;
    }
}

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    _capacity *= 2;
    T* oldElem = _elem;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template <typename T>
void Vector<T>::add(const T& e) {
    expand();
    _elem[_size++] = e;
}

template <typename T>
void Vector<T>::remove(const T& e) {
    for (int i = 0; i < _size; ++i) {
        if (_elem[i] == e) {
            for (int j = i; j < _size - 1; ++j) {
                _elem[j] = _elem[j + 1];
            }
            _size--;
            break;
        }
    }
}

template <typename T>
void Vector<T>::unique() {
    for (int i = 0; i < _size; ++i) {
        for (int j = i + 1; j < _size; ++j) {
            if (_elem[i] == _elem[j]) {
                remove(_elem[j]);
                j--; // ���¼�鵱ǰ����
            }
        }
    }
}

template <typename T>
void Vector<T>::shuffle() {
    std::default_random_engine generator(static_cast<unsigned int>(std::time(0)));
    std::shuffle(_elem, _elem + _size, generator);
}

template <typename T>
void Vector<T>::bubbleSort() {
    bool swapped;
    auto start = std::chrono::high_resolution_clock::now(); // ��¼��ʼʱ��

    for (int i = 0; i < _size - 1; ++i) {
        swapped = false;
        for (int j = 0; j < _size - i - 1; ++j) {
            if (_elem[j].modulus() > _elem[j + 1].modulus() ||
                (_elem[j].modulus() == _elem[j + 1].modulus() && _elem[j].real > _elem[j + 1].real)) {
                std::swap(_elem[j], _elem[j + 1]); // ����Ԫ��
                swapped = true;
            }
        }
        // ���û�н����������Ѿ������
        if (!swapped) {
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // ��¼����ʱ��
    std::chrono::duration<double> duration = end - start; // �����ʱ
    //std::cout << "ð�������ʱ: " << duration.count() << "��\n";
}

template <typename T>
void Vector<T>::sortByModulus() {
    bubbleSort();

    //std::sort(_elem, _elem + _size, [](const T& a, const T& b) {
        //return a.modulus() < b.modulus() || (a.modulus() == b.modulus() && a.real < b.real);
        //});
}

template <typename T>
void Vector<T>::merge(int left, int mid, int right) {
    int n1 = mid - left + 1; // ��������Ĵ�С
    int n2 = right - mid;    // ��������Ĵ�С

    // ������ʱ����
    T* leftArray = new T[n1];
    T* rightArray = new T[n2];

    // �������ݵ���ʱ����
    for (int i = 0; i < n1; i++)
        leftArray[i] = _elem[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = _elem[mid + 1 + j];

    // �ϲ���ʱ����
    int i = 0; // �������������
    int j = 0; // �������������
    int k = left; // �ϲ������������

    while (i < n1 && j < n2) {
        if (leftArray[i].modulus() < rightArray[j].modulus() ||
            (leftArray[i].modulus() == rightArray[j].modulus() && leftArray[i].real < rightArray[j].real)) {
            _elem[k++] = leftArray[i++];
        }
        else {
            _elem[k++] = rightArray[j++];
        }
    }

    // ����ʣ���Ԫ��
    while (i < n1)
        _elem[k++] = leftArray[i++];
    while (j < n2)
        _elem[k++] = rightArray[j++];

    // �ͷ���ʱ����
    delete[] leftArray;
    delete[] rightArray;
}

template <typename T>
void Vector<T>::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // �ݹ���������������
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        // �ϲ�������Ĳ���
        merge(left, mid, right);
    }
}
template <typename T>
void Vector<T>::sortByModulus2() {
    auto start = std::chrono::high_resolution_clock::now(); // ��¼��ʼʱ��

    // ���ù鲢����
    mergeSort(0, _size - 1);

    auto end = std::chrono::high_resolution_clock::now(); // ��¼����ʱ��
    std::chrono::duration<double> duration = end - start; // �����ʱ

    std::cout << "�鲢�����ʱ: " << duration.count() << "��\n";
}

template <typename T>
void Vector<T>::insert(Rank r, const T& e) {
    if (r < 0 || r > _size) {
        throw std::out_of_range("Index out of bounds");
    }
    expand();  // ȷ�����㹻�Ŀռ�
    for (int i = _size; i > r; --i) {
        _elem[i] = _elem[i - 1];  // ����Ԫ��
    }
    _elem[r] = e;  // ������Ԫ��
    _size++;
}
template <typename T>
void Vector<T>::print() const {
    for (int i = 0; i < _size; ++i) {
        std::cout << _elem[i] << " ";
    }
    std::cout << std::endl;
}

#endif // VECTOR_H
