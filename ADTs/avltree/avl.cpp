/**
 * @file avl.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 9, 2024
 *
 * Implementing an AVL tree class for practice.
 */

#include "avl.h"
#include <iostream>
using namespace std;

// Node rotations
Node* AVLTree::left_Rotate(Node* critical) { // right-right
    Node* temp = criical->right;
    critical->right = temp->left;
    temp->left = critical;
    return temp;
}

Node* AVLTree::right_Rotate(Node* critical) { // left-left
    Node* temp = critical->left;
    critical->left = temp->right;
    temp->right = critical;
    return temp;
}

Node* AVLTree::lr_Rotate(Node* critical) {
    Node* temp = critical->left;
    critical->left = left_Rotate(temp);
    return (right_Rotate(critical));
}

Node* AVLTree::rl_Rotate(Node* critical) {
    Node* temp = critical->right;
    critical->right = right_Rotate(temp);
    return (left_Rotate(critical));
}

// Calculates height of a subtree.
int AVLTree::height(Node* root) {
    int h = 0;
    if (root != nullptr) {
        int leftH = height(root->left);
        int rightH = height(root->right);
        h = leftH
        if (rightH > leftH) {
            h = rightH;
        }
        h++;
    }
    return h;
}

// Calculates balance factor of a subtree.
int AVLTree::balFactor(Node* root) {
    return height(root->left) - height(root->right);
}



// Displays keys in preorder format
void AVLTree::preorder(Node*& root) {
    if (root == nullptr) {
        return;
    }
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

// Displays keys in inorder format
void AVLTree::inorder(Node*& root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// Displays keys in postorder format
void AVLTree::postorder(Node*& root) {
    if (root == nullptr) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

// Searches for node with key value.
Node* AVLTree::search(Node* root, int key) {
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
      
// Default constructor
AVLTree::AVLTree(): _root(nullptr) {}

// Regular constructor
AVLTree::AVLTree(Node* root): _root(root) {}

// Destructor
AVLTree::~AVLTree() {
    clear();
}
        
// Inserts a new node with given key
void AVLTree::insert(const int key);

// Removes the node with key value.
void AVLTree::remove(const int key);

// Searches for node with key value.
Node* AVLTree::search(int key) {
    return search(_root, key);
}

// Balances AVL tree by performing proper rotations.
Node* AVLTree::balanceTree(Node* critical) {
    int balFactor = balFactor(criical);
    if (balFactor > 1) {
        if (balFactor(critical->left) > 0) {
            critical = right_Rotate(critical);
        } else {
            critical = lr_Rotate(critical);
        }
    } else if (balFactor < -1) {
        if (balFactor(critical->right) > 0) {
            critical = rl_Rotate(critical);
        } else {
            critical = left_Rotate(critical);
        }
    }
    return critical;
}

// Displays keys in preorder format
void AVLTree::preorder() {
    preorder(_root);
}

// Displays keys in inorder format
void AVLTree::inorder() {
    inorder(_root);
}

// Displays keys in postorder format
void AVLTree::postorder() {
    postorder(_root);
}

// Checks if tree is empty or not
bool AVLTree::isEmpty() const {
    return _root == nullptr;
}

// Removes all nodes from tree
void AVLTree::clear() {
    while (!isEmpty()) {
        remove(_root, _root->key);
    }
}