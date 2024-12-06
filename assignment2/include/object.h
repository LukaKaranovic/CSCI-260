/**
 * @file object.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date October 29, 2024
 *
 * Defines an object class to hold all object data, in this case a customer. Encapsulates all unique data for objects. 
 * In this case, those stated in the problem description: customer ID, email address, a name, and an internally used status. 
 * Object has a constructor, destructor, getter functions, setter functions, and a displayInfo() function which prints all encapsulated data.
 */

#ifndef ASSN2_OBJ_H
#define ASSN2_OBJ_H

#include <string>

using namespace std;

class Object {
    private:
    
    static int prefix;      // Prefix for customer IDs
    static int idTracker;   // Tracks ID for next customer, adds to prefix
    int _id;                // Holds specific customer ID
    string _name;           // Holds customer name
    string _email;          // Holds customer email
    bool isActive = true;   // Holds customer subscription status, true if subscribed

    /**
	 * Sets new customer ID upon creation.
	 */
    void setID() {
        _id = idTracker + prefix;
        idTracker++;
    }

    public:

    /**
	 * Regular constructor
	 */  
    Object(string name, string email);

    /**
	 * Destructor
	 */
    ~Object();
    
    /**
	 * Returns customer's ID.
	 */   
    int getID();

    /**
	 * Returns customer's email.
	 */
    string getEmail();

    /**
	 * Returns customer's name.
	 */
    string getName();

    /**
	 * Returns customer's subscription status.
	 */
    bool getStatus();

    /**
	 * Updates customer's subscription status.
	 */
    void setStatus(bool subscribed);

    /**
	 * Updates customer's name.
	 */
    void setName(string name);

    /**
	 * Displays all customer information: name, email, id, subscription status.
	 */
    void displayInfo();
};

#endif