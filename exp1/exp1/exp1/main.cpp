#include "vector.h"
#include "complex.h"
#include <random>
#include <ctime>
#include <iomanip>
#include <chrono>

void testSortingEfficiency(Vector<Complex>& vec) {
    Vector<Complex> original = vec; // 备份原始数据
    Vector<Complex> vec2 = original;
   
     // 乱序
    vec2.shuffle();
    auto start = std::chrono::high_resolution_clock::now();
    vec2.bubbleSort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "乱序情况下冒泡排序耗时: " << duration.count() << "秒\n";

    vec2.shuffle();
    start = std::chrono::high_resolution_clock::now();
    vec2.mergeSort(0, vec2.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "乱序情况下归并排序耗时: " << duration.count() << "秒\n";

    // 顺序

    vec2 = original;
    std::sort(original.begin(), original.end());
    start = std::chrono::high_resolution_clock::now();
    vec2.bubbleSort();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "顺序情况下冒泡排序耗时: " << duration.count() << "秒\n";

    start = std::chrono::high_resolution_clock::now();
    vec2.mergeSort(0, vec2.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "顺序情况下归并排序耗时: " << duration.count() << "秒\n";

   

    // 逆序
    vec2 = original;
    std::sort(original.begin(), original.end(), std::greater<Complex>());
    start = std::chrono::high_resolution_clock::now();
    vec2.bubbleSort();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "逆序情况下冒泡排序耗时: " << duration.count() << "秒\n";

    vec2 = original;
    std::sort(original.begin(), original.end(), std::greater<Complex>());
    start = std::chrono::high_resolution_clock::now();
    vec2.mergeSort(0, vec2.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "逆序情况下归并排序耗时: " << duration.count() << "秒\n";
}
int main() {
    Vector<Complex> vec;
    std::default_random_engine generator(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<int> distribution(-10, 10);

    // 随机生成复数向量
    for (int i = 0; i < 10; ++i) {
        double real = static_cast<int>(std::round(distribution(generator)));
        double imag = static_cast<int>(std::round(distribution(generator)));
        vec.add(Complex(real, imag));
    }
    std::cout << std::fixed; // 设置固定小数点格式，保留两位小数
    std::cout << "原始向量: ";
    vec.print();

    // 置乱
    vec.shuffle();
    std::cout << "置乱后向量: ";
    vec.print();

    // 查找
    double realPart, imaginaryPart;
    std::cout << "请输入要查找的复数的实部和虚部（例如：3.0 4.0）: ";
    std::cin >> realPart >> imaginaryPart;

    Complex target(realPart, imaginaryPart);  // 用户输入的复数

    if (std::find(vec.begin(), vec.end(), target) != vec.end()) {
        std::cout << "找到复数: " << target << std::endl;
    }
    else {
        std::cout << "未找到复数: " << target << std::endl;
    }


    // 插入
    int insertIndex;
    std::cout << "请输入要插入的复数的实部和虚部（例如：3 4）: ";
    std::cin >> realPart >> imaginaryPart;
    Complex newComplex(realPart, imaginaryPart); // 要插入的复数
    std::cout << "请输入插入索引: ";
    std::cin >> insertIndex;

    // 进行插入操作
    try {
        vec.insert(insertIndex, newComplex);
        std::cout << "插入后的向量: ";
        vec.print();
    }
    catch (const std::out_of_range& e) {
        std::cout << "插入失败: " << e.what() << std::endl;
    }



    // 删除
    std::cout << "请输入要删除的复数的实部和虚部（例如：3.0 4.0）: ";
    std::cin >> realPart >> imaginaryPart;
    Complex target2(realPart, imaginaryPart);

    if (std::find(vec.begin(), vec.end(), target2) != vec.end()) {
        vec.remove(target2);
        std::cout << "成功删除: " << target2 << std::endl;
    }
    else {
        std::cout << "未找到复数: " << target2 << std::endl;
    }


    std::cout << "删除后向量: ";
    vec.print();

    // 唯一化
    vec.unique();
    std::cout << "唯一化后向量: ";
    vec.print();

    // 排序测试

    testSortingEfficiency(vec);


    // 区间查找
    double m1 = 5.0, m2 = 10.0;
    Vector<Complex> subVec;
    vec.sortByModulus();
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i].modulus() >= m1 && vec[i].modulus() < m2) {
            subVec.add(vec[i]);
        }
    }

    std::cout << "模介于[" << m1 << ", " << m2 << ") 的复数: ";
    subVec.print();


    return 0;
}
