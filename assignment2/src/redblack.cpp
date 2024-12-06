/**
 * @file redblack.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date November 5, 2024
 *
 * Implements methods in RedBlack class defined in the 'include/tree.h' header file. 
 * This class holds an RB-Tree of nodes that point to objects (in this case, customers).
 */

#include <string>
#include <iostream>
#include <stack>
#include "../include/tree.h"

/** @brief Performs an AVL tree left rotate on 3 nodes.
 *  
 *  @param critical The node with an unbalanced balance factor, in this case, a grandparent node.
 *  @return The child of the critical node, in this case, the parent.
*/

Node* RedBlack::left_Rotate(Node* critical) { 
    Node* temp = critical->right;
    critical->right = temp->left;
    temp->left = critical;
    return temp;
}

/** @brief Performs an AVL tree right rotate on 3 nodes.
 *  
 *  @param critical The node with an unbalanced balance factor, in this case, a grandparent node.
 *  @return The child of the critical node, in this case, the parent.
*/

Node* RedBlack::right_Rotate(Node* critical) { 
    Node* temp = critical->left;
    critical->left = temp->right;
    temp->right = critical;
    return temp;
}

/** @brief Performs an AVL tree left-right rotate on 3 nodes.
 *  
 *  @param critical The node with an unbalanced balance factor, in this case, a grandparent node.
 *  @return The child of the critical node, in this case, the parent.
*/

Node* RedBlack::lr_Rotate(Node* critical) {
    Node* temp = critical->left;
    critical->left = left_Rotate(temp);
    return (right_Rotate(critical));
}

/** @brief Performs an AVL tree right-left rotate on 3 nodes.
 *  
 *  @param critical The node with an unbalanced balance factor, in this case, a grandparent node.
 *  @return The child of the critical node, in this case, the parent.
*/

Node* RedBlack::rl_Rotate(Node* critical) {
    Node* temp = critical->right;
    critical->right = right_Rotate(temp);
    return (left_Rotate(critical));
}

/** @brief Inserts a new customer object into the RBT.
 *
 *  This insert follows the normal BST insertion algorithm, and uses the object's ID 
 *  to find where to insert the node that holds this object. As it is traversing down the tree to find where to insert, a stack of nodes,
 *  called traversal, keeps track of all the nodes traversed. This is for the restore() method below that restores the RBT's properties.
 * 
 *  Note: This method is currently only called if the BST insert was successful, meaning it will always return true.
 *  
 *  @param data The customer object to be inserted into the RBT.
 *  @return True if the object was inserted, false if the insertion failed.
*/

bool RedBlack::insert(Object* data) {
    int newID = data->getID();

    if (isEmpty()) {
        Node* root = new Node(data);
        root->colour = true;
        this->_root = root;
        return true;
    } 

    Node* newNode = new Node(data);
    stack<Node*> traversal;
    Node* curr = _root;

    while (curr != nullptr) {
        traversal.push(curr);
        int currID = curr->obj->getID();

        if (newID < currID) {
            curr = curr->left;
        } else if (newID > currID) {
            curr = curr->right;
        }
    }
    Node* parent = traversal.top();

    if (newID < parent->obj->getID()) {
            parent->left = newNode;
            curr = newNode;
    } else if (newID > parent->obj->getID()) {
            parent->right = newNode;
            curr = newNode;
    }
    if (parent->colour == false) {
        restore(traversal, curr);
    }
    return true;
}

/** @brief Restores the RBT properties after an insert. Handles the red-red problem that may arise.
 *
 *  Uses the stack from insert to traverse back up the tree to find parent and grandparent pointers. If the tree is big enough,
 *  needs a greatgrandparent pointer (ggparent) to ensure that it points to the correct node after a tri-node restructure.
 *  First goes through the cases of the parent being the left child of the grandparent, with subcases for how to resolve the insertion issue.
 *  If the parent is the right child of the grand parent, goes through those cases, with subcases for how to resolve the insertion issue.
 *  If needed, will propogate the problem to the grandparrent node.
 *  
 *  @param s The stack used in insert to traverse down the tree.
 *  @param curr The current node (child/newly inserted node normally) causing the conflict.
 *  @return Void
*/

void RedBlack::restore(stack<Node*>& s, Node* curr) {
    if (s.empty() || s.top()->colour == true) {
        return;
    }
    Node* parent = s.top();
    s.pop();
    Node* grandparent = s.top();
    s.pop();
    Node* ggparent = nullptr;
    if (!s.empty()) {
        ggparent = s.top();
    }

    if (grandparent->left == parent) {
        Node* uncle = grandparent->right;
        if (uncle != nullptr && uncle->colour == false) {
            parent->colour = true;
            uncle->colour = true;
            grandparent->colour = false;
            if (grandparent)
            restore(s, grandparent);
        } else {
            if (parent->left == curr) {
                if (ggparent != nullptr) {
                    if (ggparent->left == grandparent) {
                        ggparent->left = right_Rotate(grandparent);
                    } else {
                        ggparent->right = right_Rotate(grandparent);
                    }
                } else {
                    this->_root = right_Rotate(grandparent);
                }


                bool temp = grandparent->colour;
                grandparent->colour = parent->colour;
                parent->colour = temp;
            } else {
                if (ggparent->left == grandparent) {
                    ggparent->left = lr_Rotate(grandparent);
                } else {
                    ggparent->right = lr_Rotate(grandparent);
                }

                bool temp = grandparent->colour;
                grandparent->colour = curr->colour;
                curr->colour = temp;
            }
        }
    } else { // grandparent->right == parent
        Node* uncle = grandparent->left;
        if (uncle != nullptr && uncle->colour == false) {
            parent->colour = true;
            uncle->colour = true;
            grandparent->colour = false;
            restore(s, grandparent);
        } else {
            if (parent->right == curr) {
                if (ggparent != nullptr) {
                    if (ggparent->left == grandparent) {
                        ggparent->left = left_Rotate(grandparent);
                    } else {
                        ggparent->right = left_Rotate(grandparent);
                    }
                } else {
                    this->_root = left_Rotate(grandparent);
                }

                bool temp = grandparent->colour;
                grandparent->colour = parent->colour;
                parent->colour = temp;
            } else {
                if (ggparent->left == grandparent) {
                    ggparent->left = rl_Rotate(grandparent);
                } else {
                    ggparent->right = rl_Rotate(grandparent);
                }

                bool temp = grandparent->colour;
                grandparent->colour = curr->colour;
                curr->colour = temp;
            }
        }
    }
    _root->colour = true;
}

/** @brief Searches for a node containing a customer object with a specific ID in the RBT.
 *
 *  Searches for the target customer object based on the passed ID. If found, will return the node containing a pointer
 *  to this customer. If not found, will return a null pointer.
 *
 *  @param ID The customer ID being searched for.
 *  @return The node pointing to the customer object with the target ID.
*/

Node* RedBlack::lookUp(int ID) {
    if (isEmpty()) {
        return 0;
    }
    Node* curr = _root;
    while (curr != nullptr) {
        int currID = curr->obj->getID();
        if (ID == currID) {
            return curr;
        } else if (ID < currID) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return 0;
}

/** @brief Default Constructor
 *
 *  Inherits from the BST constructor.
*/

RedBlack::RedBlack() {}

/** @brief Destructor
 *
*/

RedBlack::~RedBlack() {
    queue<Node*> nodes;
    inOrder(nodes, this->_root);
    while (!nodes.empty()) {
        Node* temp = nodes.front();
        nodes.pop();
        delete temp;
    }
    _root = nullptr;
}

