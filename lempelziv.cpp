#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {

    // string given by question 4 on the assignment:
    string input = "010000 010010 001111 000010 000001 000010 001100 000101 000000 001001 001101 010000 001111 010011 010011 001001 000010 001001 001100 001001 010100 001001 000101 010011 000000 000001 010010 100010 010100 001111 000000 000010 100010 011011 000101 000110 000101 010010 110101 000100 000000 110111 100011 100101 011100 011110 100000 111011 100111 101001 101011 101101 101111 110001";
        
    // space then lowercase a-z
    string dictionary[64];
        
    // when fully filled, codebook dictionary simply stops accepting new entries and rest of message is encoded using this codebook dictionary

    // initliaze array
    dictionary[0] = ' ';
    cout << dictionary[0] << endl;
    for (int i = 1; i < 27; i++) {
        dictionary[i] = 'a' + (i-1);
        cout << dictionary[i] << endl;
    }

    string X;
    string curWord;
    string prevWord;
    string codeWord;
    int C = 0;
    int power = 0;

    int length = input.length();

    for (int i = 0; i < length; i++) {
        if (input[i] == '1') {
            C += pow(2, power);
            power++;
        } else if (input[i] == '0') {
            power++;
            continue;
        } else {
            if (prevWord.length() == 0) {
                curWord = dictionary[C];
                X.clear();
                X = X + curWord;
                prevWord = curWord;
                power = 0; 
                continue;
            }
            curWord = dictionary[C];
            X = X + curWord;
            codeWord = prevWord + curWord[0];
            prevWord = curWord;
            if (dictionary[C].length() == 0 && C <= 64) {
                dictionary[C] = codeWord;
            }
            power = 0;
        }
    }

    cout << X << endl;

    for (int i = 1; i < 64; i++) {
        if (dictionary[C].length() != 0) {
            cout << i << ": " << dictionary[i] << endl;
        }
    }
    return 0;
}