#include <iostream>
#include <string>
using namespace std;

int main() {

    // string given by question 3 on the assignment:
    string input = "huffman encoding algorithm uses optimized variable length bit strings to encode characters in a given string x over some alphabet. the optimization is based on the frequencies of the characters used in string x. the basic idea of the optimization is to use fewer digits to represent the characters with high frequencies. it is a greedy algorithm.";

    int frequency[26]; // for lowercase a-z

    for (int i = 0; i < 26; i++) {
        frequency[i] = 0; // initialize all values
    }

    for (int i = 0; i < input.length(); i++) {
        int c = (int)input[i];
        if (c < 97 || c > 122) { // ascii range for lowercase a-z
            continue;
        } else {
            frequency[c-97]++; // adjust for frequency array
        }
    }

    // print results, on the google doc the table was sorted by frequency number rather than letter.
    for (int i = 0; i < 26; i++) {
        cout << char(i+97) << ": " << frequency[i] << endl;
    }


    return 0;
}