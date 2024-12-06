/**
 * @file avl.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 9, 2024
 *
 * Making an AVL tree class for practice.
 */

#ifndef AVL_H
#define AVL_H



class Node (
    private:
        int key;
        Node* left = nullptr;
        Node* right = nullptr;
        int bal;
    public:
        Node(int key): key(key), left(nullptr), right(nullptr), bal(0) {}
        Node(int key, Node* left, Node* right): key(key), left(left), right(right), bal(0) {}
        ~Node() {}
        int getKey() const {
            return key;
        }
        int getBal() const {
            return bal;
        }
    friend class AVLTree;
);

class AVLTree {
    private: 
        Node* _root;

        // Node rotations
        Node* left_Rotate(Node* critical);
        Node* right_Rotate(Node* critical);
        Node* lr_Rotate(Node* critical);
        Node* rl_Rotate(Node* critical);

        // Calculates height of a subtree.
        int height(Node* root);

        // Calculates balance factor of a subtree.
        int balFactor(Node* root);

        // Displays keys in preorder format
        void preorder(Node*& root);

        // Displays keys in inorder format
        void inorder(Node*& root);

        // Displays keys in postorder format
        void postorder(Node*& root);

        // Searches for node with key value.
        Node* search(Node* root, int key);

    public:
            
        // Default constructor
        AVLTree();

        // Regular constructor
        AVLTree(Node* root);

        // Destructor
        ~AVLTree();
        
        // Inserts a new node with given key
        void insert(const int key);

        // Removes the node with key value.
        void remove(const int key);

        // Searches for node with key value.
        Node* search(int key);

        // Balances AVL tree by performing proper rotations.
        Node* balanceTree(Node* critical);

        // Displays keys in preorder format
        void preorder();

        // Displays keys in inorder format
        void inorder();

        // Displays keys in postorder format
        void postorder();

        // Checks if tree is empty or not
        bool isEmpty() const;

        // Removes all nodes from tree
        void clear();
};