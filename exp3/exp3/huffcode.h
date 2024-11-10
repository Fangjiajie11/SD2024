#include <cstring>
#include <string>
#include <iostream>

class Bitmap {
private:
    unsigned char* M;   // λͼ����
    unsigned int N;     // λͼ�Ĵ�С���ֽ�����
    unsigned int _sz;   // �����õ���Чλ��

protected:
    void init(unsigned int n) {
        M = new unsigned char[N = (n + 7) / 8]; // ��ʼ��λͼ�ռ�
        memset(M, 0, N); // ���λͼ
        _sz = 0; // ��ʼ����Чλ��Ϊ 0
    }

public:
    Bitmap(unsigned int n = 8) { init(n); } // ���캯��
    ~Bitmap() { delete[] M; } // ��������

    unsigned int size() const { return _sz; } // ������Чλ����

    void set(unsigned int k) {
        expand(k); // ��չλͼ
        _sz++;
        M[k >> 3] |= (0x80 >> (k & 0x07)); // ����λ
    }

    void clear(unsigned int k) {
        if (k >= 8 * N) return; // ������Χ��ֱ�ӷ���
        _sz--; // ������Чλ��
        M[k >> 3] &= ~(0x80 >> (k & 0x07)); // ���λ
    }

    bool test(unsigned int k) const {
        if (k >= 8 * N) return false; // ���������Χ������ false
        return M[k >> 3] & (0x80 >> (k & 0x07)); // ����ָ��λ�Ƿ�����
    }

private:
    void expand(unsigned int k) { // ��չλͼ���ڲ�����
        if (k < 8 * N) return; // ��� k �ڷ�Χ�ڣ�����Ҫ��չ
        unsigned int oldN = N;
        unsigned char* oldM = M;
        init(2 * k); // ��չλͼ����
        memcpy(M, oldM, oldN); // ����������
        delete[] oldM; // �ͷž����ݿռ�
    }

public:
    std::string bits2string(unsigned int n) const { // ����λͼ�Ķ������ַ���
        // expand(n - 1); // ȷ���ܷ��ʵ� bitmap[n - 1]
        std::string s;
        for (unsigned int i = 0; i < n; i++) {
            s += test(i) ? '1' : '0'; // ����λ���÷��� '1' �� '0'
        }
        return s;
    }
};
class HuffCode {
private:
    Bitmap bitmap; // ʹ��λͼ
public:
    HuffCode(unsigned int n) : bitmap(n) {}

    void setBit(unsigned int k) {
        bitmap.set(k);
    }

    std::string getCode()  {
        return bitmap.bits2string(bitmap.size());
    }
};

