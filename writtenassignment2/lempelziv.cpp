/**
 * @file lempelziv.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date December 2, 2024
 *
 * Script to decode lempel-ziv encoding for question 4 of Written Assignment 2.
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {

    // string given by question 4 on the assignment: i had to add a space at the very end to make the last else statement trigger
    string input = "010000 010010 001111 000010 000001 000010 001100 000101 000000 001001 001101 010000 001111 010011 010011 001001 000010 001001 001100 001001 010100 001001 000101 010011 000000 000001 010010 100010 010100 001111 000000 000010 100010 011011 000101 000110 000101 010010 110101 000100 000000 110111 100011 100101 011100 011110 100000 111011 100111 101001 101011 101101 101111 110001 ";
 
    // space then lowercase a-z
    string dictionary[64];
        
    // when fully filled, codebook dictionary simply stops accepting new entries and rest of message is encoded using this codebook dictionary

    // initliaze array
    dictionary[0] = 'S';
    for (int i = 1; i < 27; i++) {
        dictionary[i] = 'a' + (i-1);
    }

    // placeholder values for dictionary
    for (int i = 27; i < 64; i++) {
        dictionary[i] = "0";
    }

    // output
    string X;

    // string from dictionary for current code
    string curWord;

    // string from dictionary for previous code
    string prevWord;

    // new codewore entry into dictionary
    string codeWord;

    // used to get each binary code in its own string
    string temp;
    // for binary calcs
    int C = 0;
    int power = 0;

    int length = input.length();


    for (int i = 0; i < length; i++) {
        // compute binary code C
        if (input[i] == '1' || input[i] == '0') {
            temp += input[i];
        } else {
            for (int i = 5; i >= 0; i--) {
                if (temp[i] == '1') {
                    C += pow(2, power);
                }
                power++;
            }
            temp.clear();
            // for first code C
            if (prevWord.length() == 0) {
                curWord = dictionary[C];
                X += curWord;
                prevWord = curWord;
                power = 0; 
                C = 0;
                continue;
            }
            // for every other code C
            curWord = dictionary[C];
            X += curWord;
            codeWord = prevWord + curWord[0];   

            // check if codeword is in dictionary or if dictionary is already full, and find next available spot         
            int i = 0;
            bool duplicate = true;
            while (dictionary[i] != "0" && i < 64) {
                i++;
                if (codeWord == dictionary[i]) {
                    duplicate = false;
                }
            }
            // add new codeword to dictionary
            if (i < 64 && duplicate == true) {
                dictionary[i] = codeWord;
            }            
            prevWord = curWord;

            power = 0;
            C = 0;
        }
    }

    for (int i = 0; i < 64; i++) {
        cout << i << ": " << dictionary[i] << endl;
    }
    // final output string
    cout << X << endl;

    return 0;
}