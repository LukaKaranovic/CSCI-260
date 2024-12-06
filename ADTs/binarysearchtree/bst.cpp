/**
 * @file bst.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 7, 2024
 *
 * Implementing a binary search tree class for practice.
 */

#include <iostream>
#include "bst.h"
using namespace std;

// Inserts a new node with given key
void BST::insert(Node*& root, const int key) {
    if (root == nullptr) {
        Node* node = new Node(key);
        root = node;
    } else if (key < root->key) {
        return insert(root->left, key);
    } else if (key > root->key) {
        return insert(root->right, key);
    }
}

// Searches for node with key value.
Node* BST::search(Node* root, int key) const {
    if (root == nullptr) {
        return nullptr;
    } else if (root->key == key) {
        return root;
    } else if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Finds minimum key value in the subtree of root (including root)
Node* BST::findMin(Node*& root) const {
    if (root == nullptr || root->left == nullptr) {
        return root;
    }
    return findMin(root->left);
}

// Finds maximum key value in the subtree of root (including root)
Node* BST::findMax(Node*& root) const {
    if (root == nullptr || root->right == nullptr) {
        return root;
    }
    return findMin(root->right);
}

// Finds successor of root
Node* BST::successor(Node*& root) const {
    if (root == nullptr || root->right == nullptr) {
        return root;
    }
    return findMin(root->right);
}

// Finds predecessor of root
Node* BST::predecessor(Node*& root) const {
    if (root == nullptr || root->left == nullptr) {
        return root;
    }
    return findMax(root->left);
}

// Removes element with key value
void BST::remove(Node*& root, const int key) {
    if (root == nullptr) {
        return;
    } else if (key < root->key) {
        remove(root->left, key);
    } else if (key > root->key) {
        remove(root->right, key);
    } else {
        if (root->left != nullptr && root->right != nullptr) {
            root->key = successor(root)->key;
            remove(root->right, root->key);
        } else {
            Node* temp = root;
            if (root->left == nullptr) {
                root = root->right;
                delete temp;
            } else { // root->right == nullptr
                root = root->left;
                delete temp;
            }
        }
    }
}

// Default constructor
BST::BST(): _root(nullptr) {}

// Regular constructor
BST::BST(Node* root): _root(root) {}

// Destructor
BST::~BST() {
    clear();
}

// Checks if tree is empty or not
bool BST::isEmpty() const {
    return _root == nullptr;
}

// Inserts key value into tree
void BST::insert(const int key) {
    insert(_root, key);
}

// Searches for node with key value.
Node* BST::search(int key) const {
    Node* target = search(_root, key);
    return target;
}

// Returns successor of key
int BST::successor(int key) const {
    Node* target = search(key);
    return successor(target)->key;
}

// Returns predecessor of key
int BST::predecessor(int key) const {
    Node* target = search(key);
    return predecessor(target)->key;
}

// Displays keys in preorder format
void BST::preorder(Node*& root) {
    if (root == nullptr) {
        return;
    }
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

// Displays keys in inorder format
void BST::inorder(Node*& root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// Displays keys in postorder format
void BST::postorder(Node*& root) {
    if (root == nullptr) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

// Removes all nodes from tree
void BST::clear() {
    while (!isEmpty()) {
        remove(_root, _root->key);
    }
}

// Removes the node with key value.
void BST::remove(const int key) {
    remove(_root, key);
}

void BST::preorder() {
    preorder(_root);
}

void BST::inorder() {
    inorder(_root);
}

void BST::postorder() {
    postorder(_root);
}