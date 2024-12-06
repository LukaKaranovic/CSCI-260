/**
 * @file main.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date November 6, 2024
 *
 * Holds the command user interface for the application.
 */

#include <iostream>
#include <string>
#include <queue>
#include "../include/object.h"
#include "../include/tree.h"

using namespace std;

/** @brief Converts the string to lowercase.
 *
 *  Changes the input string to make all of its characters lowercase.
 *
 *  @param input The input string.
 *  @return The input string in lowercase.
 */

string& stringToLower(string& input) {
    int length = input.length();
    for (int i = 0; i < length; i++) {
        input[i] = tolower(input[i]);
    }
    return input;
}

/** @brief Prompts the user for a command returns it.
 *
 *  Converts the command input to lowercase so it works for the conditional statements in main. This adds user input friendliness.
 *
 *  @param userCommand The string used to store the user's command.
 *  @return The inputted user command in lowercase.
 */

string& getCommand(string& userCommand) {
    cout << "Enter a command: ";
    getline(cin, userCommand);
    return stringToLower(userCommand);
}

/** @brief Creates a customer object with the given name and email, and inserts it into the two trees.
 *
 *  If the given email already exists within the database, will resubscribe them and update
 *  their name if unsubscribed. If they are already subscribed, will throw an exception
 *  and prompt the user for a new command input.
 *
 *  Will first attempt to insert the customer into the BST, if successful, will then insert into the RBT.
 *  This is an additional check for duplicate emails.
 *
 *  @param rbt The RBT holding the nodes that hold the customers.
 *  @param bst The BST holding the nodes that hold the customers.
 *  @param name The user inputted name for the customer.
 *  @param email The user inputted email for the customer.
 *  @return Void.
 */

void subscribe(BST& bst, RedBlack& rbt, string name, string email) {
    if (!bst.isEmpty()) {
        Node* temp = bst.lookUp(email);
        if(temp != 0) {
            if (temp->obj->getStatus() == false) {
                temp->obj->setStatus(true);
                temp->obj->setName(name);
                cout << email << " has resubscribed!" << endl;
                return;
            } else {
                throw invalid_argument("Email already exists within database and is subscribed.");
            }
        } 
    }

    Object* customer = new Object(name, email);
    bool insert = bst.insert(customer);
    if (insert == true) {
        rbt.insert(customer);
    }
    cout << "User created and subscribed successfully!" << endl;
}

/** @brief Displays all customer info of a customer with a given ID.
 *
 *  Will lookup customer in RBT, as it is searching by ID. Will then display customer
 *  name, email, id, and subscription status.
 *
 *  If the ID is not in the database, will throw an exception and prompt the user for a new command input.
 *
 *  @param rbt The RBT holding the nodes that hold the customers.
 *  @param target The input target customer ID being searched for.
 *  @return Void.
 */

void show(RedBlack& rbt, int target) {
    Node* customer = rbt.lookUp(target);
    if (customer == 0) {
        throw invalid_argument("A customer with the given ID does not exist.");
    }
    customer->obj->displayInfo();
}

/** @brief Displays all customer IDs and names in ascending order of customer ID.
 *
 *  If there are no customers, will throw an exception and prompt the user for a new command input.
 *
 *  Performs an inorder traversal of the RBT and loads all nodes into the queue in ascending order of customer ID.
 *  Iterates through the queue, printing each customer's ID and name.
 *
 *  @param rbt The RBT holding the nodes that hold the customers.
 *  @param customers The queue of nodes holding customers.
 *  @return Void.
 */

void list(RedBlack& rbt, queue<Node*> customers) {
    if (rbt.isEmpty()) {
        throw invalid_argument("There are no existing customers.");
    }
    rbt.inOrder(customers);
    while(!customers.empty()) {
        cout << "ID: " << customers.front()->obj->getID() << endl;
        cout << "Name: " <<  customers.front()->obj->getName() << endl << endl;
        customers.pop();
    }
}

/** @brief Displays all subscribed customer emails and names in alphabetical order of customer email.
 *
 *  If there are no customers, will throw an exception and prompt the user for a new command input.
 *
 *  Performs an inorder traversal of the BST and loads all nodes into the queue in alphabetical order of customer email.
 *  Iterates through the queue of customers and does the following:
 *  If the customer is subscribed, will print the customer's email and name.
 *  If the customer is not subscribed, will not print anything and will pop the customer from the queue.
 *
 *  @param bst The BST holding the nodes that hold the customers.
 *  @param customers The queue of nodes holding customers.
 *  @return Void.
 */

void spam(BST& bst, queue<Node*> customers) {
    if (bst.isEmpty()) {
        throw invalid_argument("There are no existing customers.");
    }
    bst.inOrder(customers);
    while(!customers.empty()) {
        if (customers.front()->obj->getStatus() == true) {
            cout << "email: " << customers.front()->obj->getEmail() << endl;
            cout << "Name: " << customers.front()->obj->getName() << endl << endl;
        }
        customers.pop();
    }
}

/** @brief Unsubscribes a customer with the target customer ID.
 *
 *  Searches for the customer with the target customer ID. Sets their subscription status to false.
 *
 *  If the customer is already unsubscribed or is not found, will throw an exception and prompt the user for a new command input.
 *
 *  @param rbt The RBT holding the nodes that hold the customers.
 *  @param target The user inputted target customer ID.
 *  @return Void.
 */

void unsubscribe(RedBlack& rbt, int target) {
    Node* customer = rbt.lookUp(target);
    if (customer == 0 || customer->obj->getStatus() == false) {
        throw invalid_argument("A customer with the given ID does not exist OR this customer is already unsubscribed.");
    } 
    customer->obj->setStatus(false);
    cout << "User with ID: " << customer->obj->getID() << " has unsubscribed." << endl;
}

/** @brief Terminates the program and deletes all dynamically allocated objects.
 *
 *  Calls cleanData() method on the BST that puts all objects into a queue and deletes them all.
 *
 *  @param bst The BST holding the nodes that hold the customers.
 *  @return Void.
 */

void quit(BST& bst) {
    cout << "Program is being terminated, cleaning all customer data." << endl;
    bst.cleanData();

    cout << "Deleting customer trees..." << endl;
    cout << "Thank you for using the program!" << endl;
}

int main() {
    BST bst;
    RedBlack rbt;
    queue<Node*> customers;
    string userCommand;
    cout << "Command list: " << endl;
    cout << "subscribe: Subscribe as a new customer or resubscribe as an old customer." << endl;
    cout << "show: Displays all information about the customer with a given ID." << endl;
    cout << "list: Lists the customer ID and name of all customers (in ascending order of customer ID)." << endl;
    cout << "spam: Lists the email and name of all subscribed customers (in ascending order of customer email)." << endl;
    cout << "unsubscribe: Unsubscribes a current customer with a given ID." << endl;
    cout << "quit: Terminates the program." << endl;  
    
    getCommand(userCommand);

    while (userCommand != "quit") {
        if (userCommand == "subscribe") {
            string email, name;
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter your email: ";
            getline(cin, email);
            try {
                subscribe(bst, rbt, name, email);
            } catch (invalid_argument& error) {
                cout << error.what() << endl;
            }
        } else if (userCommand == "show") {
            try {
                int target;
                cout << "Input customer ID: ";
                cin >> target;
                cin.ignore(1000, '\n');
                show(rbt, target);
            } catch (invalid_argument& error) {
                cout << error.what() << endl;
            }
        } else if (userCommand == "list") {
            try {
                list(rbt, customers);
            } catch (invalid_argument& error) {
                cout << error.what() << endl;
            }
        } else if (userCommand == "spam") {
            try {
                spam(bst, customers);
            } catch (invalid_argument& error) {
                cout << error.what() << endl;
            }
        } else if (userCommand == "unsubscribe") {
            try {
                int target;
                cout << "Input customer ID: ";
                cin >> target;
                cin.ignore(1000, '\n');
                unsubscribe(rbt, target);
            } catch (invalid_argument& error) {
                cout << error.what() << endl;
            }
        } else {
            cout << "Not a valid command, try again." << endl;
        }
        getCommand(userCommand);
    }
    quit(bst);
    return 0;

}