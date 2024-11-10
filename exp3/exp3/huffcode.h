#include <cstring>
#include <string>
#include <iostream>

class Bitmap {
private:
    unsigned char* M;   
    unsigned int N;     
    unsigned int _sz;  

protected:
    void init(unsigned int n) {
        M = new unsigned char[N = (n + 7) / 8];
        memset(M, 0, N); 
        _sz = 0; 
    }

public:
    Bitmap(unsigned int n = 8) { init(n); }
    ~Bitmap() { delete[] M; } 

    unsigned int size() const { return _sz; } 

    void set(unsigned int k) {
        expand(k); 
        _sz++;
        M[k >> 3] |= (0x80 >> (k & 0x07)); 
    }

    void clear(unsigned int k) {
        if (k >= 8 * N) return;
        _sz--; 
        M[k >> 3] &= ~(0x80 >> (k & 0x07)); 
    }

    bool test(unsigned int k) const {
        if (k >= 8 * N) return false; 
        return M[k >> 3] & (0x80 >> (k & 0x07)); 
    }

private:
    void expand(unsigned int k) { 
        if (k < 8 * N) return; 
        unsigned int oldN = N;
        unsigned char* oldM = M;
        init(2 * k); 
        memcpy(M, oldM, oldN); 
        delete[] oldM; 
    }

public:
    std::string bits2string(unsigned int n) const { 
        // expand(n - 1); 
        std::string s;
        for (unsigned int i = 0; i < n; i++) {
            s += test(i) ? '1' : '0'; 
        }
        return s;
    }
};
class HuffCode {
private:
    Bitmap bitmap; 
public:
    HuffCode(unsigned int n) : bitmap(n) {}

    void setBit(unsigned int k) {
        bitmap.set(k);
    }

    std::string getCode()  {
        return bitmap.bits2string(bitmap.size());
    }
};

