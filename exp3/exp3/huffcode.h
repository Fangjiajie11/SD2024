#include <cstring>
#include <string>
#include <iostream>

class Bitmap {
private:
    unsigned char* M;   // 位图数据
    unsigned int N;     // 位图的大小（字节数）
    unsigned int _sz;   // 已设置的有效位数

protected:
    void init(unsigned int n) {
        M = new unsigned char[N = (n + 7) / 8]; // 初始化位图空间
        memset(M, 0, N); // 清空位图
        _sz = 0; // 初始化有效位数为 0
    }

public:
    Bitmap(unsigned int n = 8) { init(n); } // 构造函数
    ~Bitmap() { delete[] M; } // 析构函数

    unsigned int size() const { return _sz; } // 返回有效位数量

    void set(unsigned int k) {
        expand(k); // 扩展位图
        _sz++;
        M[k >> 3] |= (0x80 >> (k & 0x07)); // 设置位
    }

    void clear(unsigned int k) {
        if (k >= 8 * N) return; // 超出范围，直接返回
        _sz--; // 更新有效位数
        M[k >> 3] &= ~(0x80 >> (k & 0x07)); // 清除位
    }

    bool test(unsigned int k) const {
        if (k >= 8 * N) return false; // 如果超出范围，返回 false
        return M[k >> 3] & (0x80 >> (k & 0x07)); // 返回指定位是否被设置
    }

private:
    void expand(unsigned int k) { // 扩展位图的内部方法
        if (k < 8 * N) return; // 如果 k 在范围内，不需要扩展
        unsigned int oldN = N;
        unsigned char* oldM = M;
        init(2 * k); // 扩展位图容量
        memcpy(M, oldM, oldN); // 拷贝旧数据
        delete[] oldM; // 释放旧数据空间
    }

public:
    std::string bits2string(unsigned int n) const { // 返回位图的二进制字符串
        // expand(n - 1); // 确保能访问到 bitmap[n - 1]
        std::string s;
        for (unsigned int i = 0; i < n; i++) {
            s += test(i) ? '1' : '0'; // 根据位设置返回 '1' 或 '0'
        }
        return s;
    }
};
class HuffCode {
private:
    Bitmap bitmap; // 使用位图
public:
    HuffCode(unsigned int n) : bitmap(n) {}

    void setBit(unsigned int k) {
        bitmap.set(k);
    }

    std::string getCode()  {
        return bitmap.bits2string(bitmap.size());
    }
};

