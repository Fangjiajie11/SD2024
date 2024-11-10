#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>    
#include <cctype>  
#include"bintree.h"
#include"hufftree.h"
#include"huffcode.h"
#include"huffmancoder.h"

using namespace std;

unordered_map<char, int> getLetterFrequencies(const string& filename) {
    unordered_map<char, int> frequencies;

    // ��ʼ����ĸƵ��Ϊ0
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        frequencies[ch] = 0;
    }

    ifstream file(filename);
    char ch;

    // ��ȡ�ļ���ͳ��Ƶ��
    while (file.get(ch)) {
        // תΪСд������Ƿ�Ϊ��ĸ
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z') {
            frequencies[ch]++;
        }
    }

    return frequencies;
}

int main() {
   /* unordered_map<char, int> frequencies = {
        {'d', 270}, {'r', 413}, {'e', 889}, {'a', 567}, {'m', 188},
        {'g', 175}, {'o', 607}, {'i', 565}, {'c', 182}, {'h', 384},
        {'v', 81}, {'p', 96}, {'f', 224}, {'t', 671}, {'y', 128},
        {'w', 165}, {'s', 429}, {'l', 342}, {'u', 176}, {'n', 485},
        {'b', 116}, {'k', 51}, {'x', 5}, {'j', 21}, {'q', 7},
        {'z', 6}
    };*/
    // ָ���ı��ļ���
    string filename = "I_have_a_dream.txt"; // �뽫�ļ����滻Ϊ�����ı��ļ�·��

    // ��ȡ�ַ�Ƶ��
    unordered_map<char, int> frequencies = getLetterFrequencies(filename);
    // �����ĸƵ��
    cout << "Letter Frequencies:\n";
    for (const auto& pair : frequencies) {
        cout << "'" << pair.first << "': " << pair.second << ", ";
    }
    cout << "\n";
    HuffmanCoder huffmanCoder(frequencies);
    huffmanCoder.printCodes();

    // ���ض����ʽ��б���
    string wordToEncode = "dream";
    string encoded = huffmanCoder.encode(wordToEncode);
    cout << wordToEncode  << "��huffman����" << ": " << encoded<< endl;
    string wordToEncode2 = "have";
    string encoded2 = huffmanCoder.encode(wordToEncode2);
    cout << wordToEncode2 << "��huffman���� " << ": " << encoded2 << endl;
    return 0;
}