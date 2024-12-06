/**
 * @file object.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 31, 2024
 *
 * Implements methods in object class defined in the 'include/object.h' header file. These methods are specific 
 * to the customer data defined in the assigment specifications only. 
 */

#include <string>
#include <iostream>
#include "../include/object.h"

using namespace std;

// Initialization of static member variables.

int Object::prefix = 100000;    // Since IDs start at 100001. 

int Object::idTracker = 1;      // Since IDs start at 100001 and increment by 1 each time.

/** @brief Regular Constructor
 *
*/

Object::Object(string name, string email): _name(name), _email(email) {
    this->setID();
}

/** @brief Destructor
 *
*/

Object::~Object() {}

/** @brief Gets the customer's ID.
 *
 *  @return The customer's ID as an integer,
*/

int Object::getID() {
    return this->_id;
}

/** @brief Gets the customer's email.
 *
 *  @return The customer's email as a string.
*/

string Object::getEmail() {
    return this->_email;
}

/** @brief Gets the customer's name.
 *
 *  @return The customer's name as a string.
*/

string Object::getName() {
    return this->_name;
}


/** @brief Gets the customer's subscription status.
 *
 *  @return True if the customer is subscribed, false if they are not subscribed.
*/

bool Object::getStatus() {
    return this->isActive;
}

/** @brief Sets the customer's subscription status.
 *
 *  @param subscribed The status to update the customer's status to. True -> subscribed, false -> not subscribed.
 *  @return Void.
*/

void Object::setStatus(bool subscribed) {
    this->isActive = subscribed;
}

/** @brief Sets the customer's name.
 *
 *  @param name The new name of the customer.
 *  @return Void.
*/

void Object::setName(string name) {
    this->_name = name;
}

/** @brief Displays all of the customer's information.
 *
 *  Labels and displays each key bit of customer data on its own line.
 *  The data includes: ID, email, name, and subscription status.
 *
 *  @return Void.
*/

void Object::displayInfo() {
    cout << "ID: " << this->_id << endl;
    cout << "email: " << this->_email << endl;
    cout << "name: " << this->_name << endl;
    if (this->isActive) {
        cout << "Subscription: Active" << endl;
    } else {
        cout << "Subscription: Inactive" << endl;
    }
}
