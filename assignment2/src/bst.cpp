/**
 * @file bst.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 31, 2024
 *
 * Implements constructors and destructors for Node class defined in the 'include/tree.h' header file.
 * This class holds BST and RBT node properties along with pointers to the objects (in this case, customers).
 *
 * Implements methods in BST class defined in the 'include/tree.h' header file. 
 * This class holds a BST of nodes that point to objects (in this case, customers).
 */

#include <string>
#include <iostream>
#include <queue>
#include "../include/tree.h"

using namespace std;

/** @brief Default Constructor
 *
*/

Node::Node(): left(nullptr), right(nullptr), colour(false), obj(nullptr) {}

/** @brief Regular Constructor
 *
*/

Node::Node(Object* customer): left(nullptr), right(nullptr), colour(false), obj(customer) {}

/** @brief Destructor
 *
*/

Node::~Node() {}

/** @brief Inserts a new customer object into the BST.
 *
 *  This insert follows the normal BST insertion algorithm, and uses the object's email 
 *  to find where to insert the node that holds this object. Will not insert the object if the 
 *  object's email already exists within the BST.
 *
 *  @param data The customer object to be inserted into the BST.
 *  @return True if the object was inserted, false if the insertion failed.
*/

bool BST::insert(Object* data) {   
    string newKey = data->getEmail();

    if (isEmpty()) {
        Node* root = new Node(data);
        this->_root = root;
        return true;
    } else if (lookUp(newKey) != 0) {
        return false;
    }

    Node* newNode = new Node(data);
    Node* curr = _root;
    Node* parent;

    while (curr != nullptr) {
        parent = curr;
        string currKey = curr->obj->getEmail();

        if (newKey < currKey) {
            curr = curr->left;
        } else if (newKey > currKey) {
            curr = curr->right;
        }
    }

    if (newKey < parent->obj->getEmail()) {
            parent->left = newNode;
    } else if (newKey > parent->obj->getEmail()) {
            parent->right = newNode;
    }
    return true;
}

/** @brief Searches for a node containing a customer object with a specific email in the BST.
 *
 *  Searches for the target customer object based on the passed email. If found, will return the node containing a pointer
 *  to this customer. If not found, will return a null pointer.
 *
 *  @param email The customer email being searched for.
 *  @return The node pointing to the customer object with the target email.
*/

Node* BST::lookUp(string email) {
    if (isEmpty()) {
        return 0;
    }
    Node* curr = _root;
    while (curr != nullptr) {
        string currKey = curr->obj->getEmail();
        if (email == currKey) {
            return curr;
        } else if (email < currKey) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return 0;
}

/** @brief Performs an inorder traversal of the tree, putting all of the nodes into a queue.
 *
 *  Traverses the tree in order, enqueues each node into the queue. The queue is passed by reference, 
 *  meaning it will update the parameter queue with the nodes.
 *
 *  @param curr The current node in the traversal.
 *  @param queue The queue that holds all of the nodes in the tree.
 *  @return Void.
*/

void BST::inOrder(queue<Node*>& queue, Node* curr) {
    if (curr == nullptr) {
        return;
    }
    inOrder(queue, curr->left);
    queue.push(curr);
    inOrder(queue, curr->right);
}

/** @brief Performs a preorder traversal of the tree, putting all of the customer objects into a queue.
 *
 *  Traverses the tree in preorder fashion, enqueues each object of each node curr into the queue. 
 *  The queue is passed by reference, meaning it will update the parameter queue with the nodes.
 *
 *  @param curr The current node in the traversal.
 *  @param objects The queue that holds all of the objects in the nodes.
 *  @return Void.
*/

void BST::preOrder(queue<Object*>& objects, Node* curr) {
    if (curr == nullptr) {
        return;
    }
    objects.push(curr->obj);
    preOrder(objects, curr->left);
    preOrder(objects, curr->right);
}

/** @brief Checks if the tree is empty or not.
 *
 *  @return True is the tree is empty, false if the tree has atleast one node.
*/

bool BST::isEmpty() {
    if (this->_root == nullptr) {
        return true;
    }
    return false;
}

/** @brief Default Constructor
 *
*/

BST::BST(): _root(nullptr) {}

/** @brief Regular Constructor
 *
*/

BST::BST(Node* root): _root(root) {}

/** @brief Deletes all customer objects stored in the nodes.
 *
 *  Calls preorder on a newly created queue of objects. Traverses through the queue and deletes every customer object.
 *
 *  @return Void.
*/

void BST::cleanData() {
    queue<Object*> objects;
    preOrder(objects, this->_root);
    while (!objects.empty()) {
        Object* temp = objects.front();
        objects.pop();
        delete temp;
    }
}

/** @brief Destructor
 *
*/

BST::~BST() {
    queue<Node*> nodes;
    inOrder(nodes, this->_root);
    while (!nodes.empty()) {
        Node* temp = nodes.front();
        nodes.pop();
        delete temp;
    }
    _root = nullptr;
}

/** @brief Public inorder method accessible from main.
 *
 *  @return Void.
*/

void BST::inOrder(queue<Node*>& queue) {
    inOrder(queue, this->_root);
}
