/**
 * @file tree.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 29, 2024
 *
 * Defines a Node class that holds a pointer to an object being operated on and has the typical 
 * properties of an RB-Tree node (left, right, colour). These nodes are to be used in the BST and RedBlack classes.
 * 
 * Defines a BST class that holds nodes pointing to objects containing customer data. 
 * These nodes are sorted by customer emails alphabetically.
 * 
 * Defines a Red-Black Tree class that holds nodes pointing to objects containing customer data. 
 * These nodes are sorted by customer IDs in ascending order.
 */

#ifndef ASSN2_TREE_H
#define ASSN2_TREE_H

#include <string>
#include <queue>
#include <stack>
#include "object.h"

using namespace std;

class Node {
    private:
        Node* left;             // pointer to left child
        Node* right;            // pointer to right child
        bool colour;            // colour of the node (for red-black tree)
        friend class BST;       // So BST class can access node member variables.
        friend class RedBlack;  // So RBT class can access node member variables.
    public:
        Object* obj;            // pointer to customer object

	/**
	 * Default constructor
	 */
    Node();

    /**
	 * Regular constructor
	 */
    Node(Object* object);

    /**
	 * Destructor
	 */
    ~Node();
};

class BST {
    protected:
    
    Node* _root;    // pointer to the root node

    /**
	 * Preorder traversal that puts all objects into a queue.
	 */
    void preOrder(queue<Object*>& objects, Node* curr);

    /**
	 * Inorder traversal that puts all nodes into a queue.
	 */
    void inOrder(queue<Node*>& queue, Node* curr); 

    public:

    /**
	 * Inserts a new node into correct spot with given object (based on email).
	 */
    virtual bool insert(Object* data);

    /**
	 * Frees all dynamically allocated objects.
	 */
    void cleanData();

	/**
	 * Default constructor
	 */
    BST();

	/**
	 * Regular constructor
	 */
    BST(Node* root);

	/**
	 * Destructor
	 */
    ~BST();

    /**
	 * Looks up an object based on email and returns node that holds it.
	 */
    virtual Node* lookUp(string email);

    /**
	 * Checks if BST is empty or not.
	 */
    bool isEmpty();

    /**
	 * Public inorder traversal method (for main.cpp).
	 */
    void inOrder(queue<Node*>& queue); 

};

class RedBlack: public BST {
    private: 
    
    /**
	 * AVL Tree rotation methods for tri-node restructure.
	 */
    Node* left_Rotate(Node* critical); 

    Node* right_Rotate(Node* critical); 

    Node* lr_Rotate(Node* critical); 

    Node* rl_Rotate(Node* critical);

    /**
	 * Handles red-red problem in RBT and maintains RBT properties.
	 */
    void restore(stack<Node*>& s, Node* curr); 

    public:

    /**
	 * Inserts a new node into correct spot with given object (based on ID).
	 */
    bool insert(Object* data);

    /**
	 * Looks up an object based on ID and returns node that holds it.
	 */
    Node* lookUp(int ID);

	/**
	 * Default constructor
	 */
    RedBlack();

	/**
	 * Destructor
	 */
    ~RedBlack();

};

#endif