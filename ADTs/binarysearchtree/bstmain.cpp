/**
 * @file bstmain.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 7, 2024
 *
 * Main file to test my BST class.
 */

#include <iostream>
#include "bst.h"
using namespace std;

int main() {
    BST tree;

    tree.insert(17);
    tree.insert(71);
    tree.insert(37);
    tree.insert(4);
    tree.insert(16);
    tree.insert(6);
    tree.insert(124);
    tree.preorder();
    cout << endl;
    tree.remove(17);
    tree.preorder();
    cout << endl;
    tree.inorder();
    cout << endl;

    cout << tree.successor(4) << endl;
    cout << tree.predecessor(124) << endl;

    Node* target = tree.search(37);
    cout << target->getKey() << " was found" << endl;
    tree.remove(37);

    tree.inorder();
    cout << endl;

    tree.clear();
    tree.preorder();
    cout << endl;
}