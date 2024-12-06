/**
 * @file bst.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 7, 2024
 *
 * Making a binary search tree class for practice.
 */

#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

class Node {
    private:
        int key;
        Node* left = nullptr;
        Node* right = nullptr;
    public:
        Node(int key): key(key), left(nullptr), right(nullptr) {}
        Node(int key, Node* left, Node* right): key(key), left(left), right(right) {}
        ~Node() {}
        int getKey() const {
            return key;
        }
    friend class BST;
};

class BST {
    private:
        Node* _root;

        // Inserts a new node with given key
        void insert(Node*& root, const int key);

        // Searches for node with key value.
        Node* search(Node* root, int key) const;

        // Finds minimum key value in the subtree of root (including root)
        Node* findMin(Node*& root) const;

        // Finds maximum key value in the subtree of root (including root)
        Node* findMax(Node*& root) const;

        // Finds successor of root
        Node* successor(Node*& root) const;

        // Finds predecessor of root
        Node* predecessor(Node*& root) const;

        // Removes element with key value
        void remove(Node*& root, const int key);

        // Displays keys in preorder format
        void preorder(Node*& root);

        // Displays keys in inorder format
        void inorder(Node*& root);

        // Displays keys in postorder format
        void postorder(Node*& root);

    public:

    // Default constructor
    BST();

    // Regular constructor
    BST(Node* root);

    // Destructor
    ~BST();

    // Checks if tree is empty or not
    bool isEmpty() const;

    // Inserts key value into tree
    void insert(const int key);

    // Searches for node with key value.
    Node* search(int key) const;

    // Returns successor of key
    int successor(int key) const;

    // Returns predecessor of key
    int predecessor(int key) const;

    // Removes all nodes from tree
    void clear();

    // Removes the node with key value.
    void remove(const int key);

    // Displays keys in preorder format
    void preorder();

    // Displays keys in inorder format
    void inorder();

    // Displays keys in postorder format
    void postorder();

};

#endif