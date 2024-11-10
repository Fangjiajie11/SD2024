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

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        frequencies[ch] = 0;
    }
    ifstream file(filename);
    char ch;

    while (file.get(ch)) {
        // 转为小写并检查是否为字母
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
    string filename = "I_have_a_dream.txt"; 

    unordered_map<char, int> frequencies = getLetterFrequencies(filename);
    cout << "Letter Frequencies:\n";
    for (const auto& pair : frequencies) {
        cout << "'" << pair.first << "': " << pair.second << ", ";
    }
    cout << "\n";
    HuffmanCoder huffmanCoder(frequencies);
    huffmanCoder.printCodes();

    // 对特定单词进行编码
    string wordToEncode = "dream";
    string encoded = huffmanCoder.encode(wordToEncode);
    cout << wordToEncode  << "的huffman编码" << ": " << encoded<< endl;
    string wordToEncode2 = "have";
    string encoded2 = huffmanCoder.encode(wordToEncode2);
    cout << wordToEncode2 << "的huffman编码 " << ": " << encoded2 << endl;
    return 0;
}
