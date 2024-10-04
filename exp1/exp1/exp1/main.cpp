#include "vector.h"
#include "complex.h"
#include <random>
#include <ctime>
#include <iomanip>
#include <chrono>

void testSortingEfficiency(Vector<Complex>& vec) {
    Vector<Complex> original = vec; // ����ԭʼ����
    Vector<Complex> vec2 = original;
   
     // ����
    vec2.shuffle();
    auto start = std::chrono::high_resolution_clock::now();
    vec2.bubbleSort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "���������ð�������ʱ: " << duration.count() << "��\n";

    vec2.shuffle();
    start = std::chrono::high_resolution_clock::now();
    vec2.mergeSort(0, vec2.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "��������¹鲢�����ʱ: " << duration.count() << "��\n";

    // ˳��

    vec2 = original;
    std::sort(original.begin(), original.end());
    start = std::chrono::high_resolution_clock::now();
    vec2.bubbleSort();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "˳�������ð�������ʱ: " << duration.count() << "��\n";

    start = std::chrono::high_resolution_clock::now();
    vec2.mergeSort(0, vec2.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "˳������¹鲢�����ʱ: " << duration.count() << "��\n";

   

    // ����
    vec2 = original;
    std::sort(original.begin(), original.end(), std::greater<Complex>());
    start = std::chrono::high_resolution_clock::now();
    vec2.bubbleSort();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "���������ð�������ʱ: " << duration.count() << "��\n";

    vec2 = original;
    std::sort(original.begin(), original.end(), std::greater<Complex>());
    start = std::chrono::high_resolution_clock::now();
    vec2.mergeSort(0, vec2.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "��������¹鲢�����ʱ: " << duration.count() << "��\n";
}
int main() {
    Vector<Complex> vec;
    std::default_random_engine generator(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<int> distribution(-10, 10);

    // ������ɸ�������
    for (int i = 0; i < 10; ++i) {
        double real = static_cast<int>(std::round(distribution(generator)));
        double imag = static_cast<int>(std::round(distribution(generator)));
        vec.add(Complex(real, imag));
    }
    std::cout << std::fixed; // ���ù̶�С�����ʽ��������λС��
    std::cout << "ԭʼ����: ";
    vec.print();

    // ����
    vec.shuffle();
    std::cout << "���Һ�����: ";
    vec.print();

    // ����
    double realPart, imaginaryPart;
    std::cout << "������Ҫ���ҵĸ�����ʵ�����鲿�����磺3.0 4.0��: ";
    std::cin >> realPart >> imaginaryPart;

    Complex target(realPart, imaginaryPart);  // �û�����ĸ���

    if (std::find(vec.begin(), vec.end(), target) != vec.end()) {
        std::cout << "�ҵ�����: " << target << std::endl;
    }
    else {
        std::cout << "δ�ҵ�����: " << target << std::endl;
    }


    // ����
    int insertIndex;
    std::cout << "������Ҫ����ĸ�����ʵ�����鲿�����磺3 4��: ";
    std::cin >> realPart >> imaginaryPart;
    Complex newComplex(realPart, imaginaryPart); // Ҫ����ĸ���
    std::cout << "�������������: ";
    std::cin >> insertIndex;

    // ���в������
    try {
        vec.insert(insertIndex, newComplex);
        std::cout << "����������: ";
        vec.print();
    }
    catch (const std::out_of_range& e) {
        std::cout << "����ʧ��: " << e.what() << std::endl;
    }



    // ɾ��
    std::cout << "������Ҫɾ���ĸ�����ʵ�����鲿�����磺3.0 4.0��: ";
    std::cin >> realPart >> imaginaryPart;
    Complex target2(realPart, imaginaryPart);

    if (std::find(vec.begin(), vec.end(), target2) != vec.end()) {
        vec.remove(target2);
        std::cout << "�ɹ�ɾ��: " << target2 << std::endl;
    }
    else {
        std::cout << "δ�ҵ�����: " << target2 << std::endl;
    }


    std::cout << "ɾ��������: ";
    vec.print();

    // Ψһ��
    vec.unique();
    std::cout << "Ψһ��������: ";
    vec.print();

    // �������

    testSortingEfficiency(vec);


    // �������
    double m1 = 5.0, m2 = 10.0;
    Vector<Complex> subVec;
    vec.sortByModulus();
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i].modulus() >= m1 && vec[i].modulus() < m2) {
            subVec.add(vec[i]);
        }
    }

    std::cout << "ģ����[" << m1 << ", " << m2 << ") �ĸ���: ";
    subVec.print();


    return 0;
}
