# Specifications
CSCI 260 Fall 2024 - Programming Assignment 2 (v1.0.0)

A hypothetical company would like to have a program to manage their customer subscription and service. 

Develop a database with two indices that hold the customer records using two trees for this service in C++. 
* One index uses the customer ID as the search keys and must be implemented as a Red-Black Tree.
* The other index uses the customer email as the search keys and must be implemented as a Binary Search Tree.

A customer has these defined characteristics:
* String email: A unique email to be associated with the customer.
    * Duplicate emails may not exist within the database.
* String name: A name to be associated with the customer.
* Int id: A unique customer ID assigned to each new customer automatically by the program.
    * Customer IDs start from 100001 and increment by 1 each time.
* Bool isActive: Checks the subscription status of the customer.
    * isActive -> true if the customer is subscribed, false if they are not subscribed.

The program must present the user with an interactive interface with the following commands:
* subscribe: Subscribe as a new customer or resubscribe as an old customer.
* show: Displays all information about the customer with a given ID. 
* list: Lists the customer ID and name of ALL customers (in ascending order of customer ID).
* spam: Lists the email and name of all subscribed customers (in ascending order of customer email).
* unsubscribe: Unsubscribes a current customer with a given ID.
* quit: Terminates the program.
    * Cleans out all existing objects and nodes that were allocated on theh eap.

Assumptions:
* If a customer ID need to be entered, it is always entered as an integer number.
* The emails are case sensitive, and you don't need to check whether the emails are in the correct format.

Additional Notes:
* Program should not crash if an incorrect key is pressed (e.g. the user entered an invalid command).
* If there is an error in the user input, show a message describing the error and go on to process the next command.

## Design
For this program, I have designed four classes. One class, Object, holds an object that may be used in the database (defined in `include/object.h`). The reason for this being named 'object' is because it is easily modifiable to hold any other data (such as a student datatype, for example) instead of customer data. 
* Note: Object class methods are implemented in the `src/object.cpp` implementation file.

The other three classes, Node, BST (binary search tree), and RedBlack (red-black tree), are defined in `include/tree.h`. The reason for this is because they all operate on the same data and function off of each other. Both the BST and RedBlack classes use the same Node class and the RedBlack class inherits off of the BST class.
* Note: BST and Node class methods are implemented in the `src/bst.cpp` implementation file, while the RedBlack class methods is implemented in the `src/redblack.cpp` implementation file.

Class 1: Object
* A class that holds object data for be operated on. This data is encapsulated and can only be accessed through getter functions by the nodes used in the trees (defined later). 
* It has getter functions, setter functions, constructors, destructors, and a displayInfo() method which prints the object's information.
* Please note that this class is specifically designed to meet the requirements for this assignment, however, the class is modifiable to hold other data, but may need small tweaks to the following tree classes.

Class 2: Node
* A class that holds the data for both BST and Red-Black Tree nodes. These nodes hold a pointer to an Object (in this case, a customer), to ensure that both trees share and operate on the same object data.
* This class includes left and right child pointers, and a boolean for the colour of the node (used for RedBlack class).
    * Bool colour: If colour is false, then node is red. If colour is true, then node is black.
* This class has constructors and destructors, and has friend classes BST and RedBlack.

Class 3: BST
* A Binary Search Tree consisting of nodes that sorts the objects (customers) alphabetically based on their unique email.
* This class has insert, isEmpty, lookUp, preOrder and inOrder traversal methods. It has a cleanData() method that cleans all dynamically allocated objects from the nodes. It has a constructor and a destructor that clears all nodes.

Class 4: RedBlack
* A Red-Black Tree consisting of nodes that sorts the objects (customers) based on their unique customer ID.
* This class inherits from the BST class as a Red-Black Tree is a BST. This means it has all of the BST class methods with some modifications. It has tri-node rotation methods for the insert, a new insert, a new lookUp, and a new helper function, restore(), that maintains the Red-Black Tree properties after an insert.

## Implementation
Note that there were no required time complexity requirements for this assignment.

I chose to implement both of my trees with a pointer based structure. This is because it is by far the most common and easiest way to implement trees. I used the STL queues and stacks to help me implement certain functions, described below:
* I used a Node* queue for my inOrder traversals in order to gather every node in the trees to display their information in the `list` and `spam` commands. This was more efficient, as I could use this traversal and queue later for gathering all of my Nodes in both of my trees to delete them in my destructors, giving this function two uses.
* I used an Object* queue for my preOrder traversal as I already used a Node* queue for my inOrder traversal, meaning I couldn't store objects through my inOrder traversal. The goal of this queue is to gather all of the object data from the nodes in the tree to clean them in my cleanData() method before cleaning the nodes, ensuring no dynamically allocated objects are lost in memory.
    * The reason this is implemented in my BST class is because the RBT class inherits the BST, meaning that if you change the program to using only an RBT, the cleanData() method will still work on the RBT (Red-Black Tree), meaning you don't HAVE to use both a BST and RBT to ensure proper deletion of run-time allocated memory.
* The advantage of using a queue is that it means I don't have to implement my own remove functions to make the destructors for my trees. This means I can navigate through the queue and delete my nodes with ease, while also not having to worry about the deletion of the queue as it has its own implemented destructor in its own library. This makes the program way easier to develop and maintain on the backend. The disadvantage of using the queue is that I don't have the remove() methods for the trees for a situation where the specifications of the database change. If I had remove() methods, I could easily remove any custoemr from the middle of my trees without any issue, which I currently can't do.

* I used a Node* stack for my RBT insert in order to track my traversal path down to where the new node must be inserted. The goal of this was to easily keep track of my parent, grandparent, and even greatgrandparent nodes without using parent pointers. The stack allowed me to propagate the red-red problem up to my grandparent after solving it on the current node (can be seen in restore() method).
    * The stack simply holds the new node's parent in the top, and you can pop the stack to retrieve the new node's grandparent, pop again for greatgrandparent, etc.
* The advantage of using a stack over the parent pointers is that I don't need to maintain more pointers in both my BST and RBT methods, which saves a lot of lines of code and makes the trees easier to maintain on the backend, if changes were needed to be made. The disadvantage of using a stack is that it is a less practicted method, meaning the chance for implementation errors are higher as there isn't as much material to compare it to. It also is not as versatile as a parent pointer, meaning it has less use cases than parent pointers.

Additional implementation comments:
* I used static member variables in my object class to store my IDs as it is te easiest way to ensure each customer ID is unique and incremented by 1.
* I used AVL Tree rotation methods in my RBT to perform tri-node restructures, this is because RBT rotations work exactly the same as AVL Tree rotations, so I used an AVL Tree as a concrete data structure to implement these rotations.

## Analysis
Problem size N = the number of customers in the trees (number of nodes/objects).
Since my database has two indices using two different trees, commands using the BST have complexity O(h), where h is the height of the tree (between logN and N), and commands using the RBT has complexity O(logN).

    subscribe: O(h) - This command first takes user input, does a few conditional checks, and creates an object. This is all done in constant time. However, it must insert the object into the BST and then the RBT afterwards. 
    Inserting into the BST takes time complexity O(h). Inserting into the RBT takes time complexity O(logN). Since h must be logN or larger, the largest growth factor of this command is h.
    show: O(logN) - This command takes user input and then has to look up the customer based on their ID, meaning it uses the RBT. Since it uses the RBT, lookUp is done in O(logN) time in the worst case.
    list: O(n) - This command does an inorder traversal of the RBT, it enqueues everything, and then displays the relevant information and empties the queue. This means it does operations on N nodes some constant amount of times (because traversing the tree requires traversing N nodes, and printing them requires dequeueing N nodes), making the largest growth factor N.
    spam: O(n) - For the same reason as list, except the inorder traversal is done on the BST. This traversal still has to go through N nodes, so the largest growth factor is N.
    unsubscribe: O(logN) - This command takes user input and then searches for the customer by its ID, meaning it uses the RBT lookUp. The rest of the function does constant operations, meaning the largest growth factor is logN.
    quit: O(N) - This command calls the cleanData() method which does a traversal through N nodes, enqueues them, and deletes them all. This does operations on N nodes some constant amount of times, meaning the largest growth factor is N.
    Note that the BST and RBT nodes are handled by the destructors when they leave scope (when main ends).

## Accomplishment
I have accomplished all parts of the assignment:
* Implementation
* Documentation
* Makefile
* README
* Testing

## Testing
For my testing, I used a typescript, which can be viewed in the assignment directory. I wrote down the actions (test cases) I wanted to perform before doing the typescript. 
Behind the // markers, I put the expected output of the program should do.
Behind the * marker, I put the reason I was testing this action.

Additionally, since there was a lot of heap memory allocation this assignment, I ran my executable through valgrind to show that there are no memory leaks in my program.

Note that most testing emails are short and not in proper format for convenience of testing.

1. List command on an empty RBT. 
// Should output "There are no existing customers."
* Testing to make sure my RBT is empty when it is supposed to be, and that proper error handling occured.

2. Subscribe command as a customer with my own email. 
// Should output "User created and subscribed successfully!"
* Testing to make sure my subscribe command works properly.

3. Spam command on my BST of size 1.
// Should output my name and email.
* Testing to make sure my spam command outputs subscribed users.

4. Unsubscribe command on my own customer ID.
// Should output "User with ID: 100001 has unsubscribed."
* Testing to make sure my unsubscribe command works properly.

5. Subscribe command as a customer with a different email 'aa'. 
// Should output "User created and subscribed successfully!"
* To add more subscribed customers for further tests.

6. Subscribe command as a customer with a different email 'ab'. 
// Should output "User created and subscribed successfully!"
* To add more subscribed customers for further tests.

7. Spam command on my BST of size 3.
// Should output email and name (in alphabetical order of email) of the 2 newly inserted customers (emails aa and ab (in this order)), and not myself (email lkaranovic88@gmail.com).
* Testing to make sure my spam command outputs all subscribed users and no unsubscribed users.

8. List command on my RBT of size 3.
// Should output all 3 customer names and IDs in order of ID.
* Testing to make sure my list command outputs all users, subscribed or unsubscribed.

9. Subscribe command on my current email with new name "Dave".
// Should output "lkaranovic88@gmail.com has resubscribed"
* To check that resubscribe works.

10. Subscribe command on my current email.
// Should output "Email already exists within database and is subscribed."
* To check error checking for duplicate emails on my subscribe command.

11. Show command on ID 100001.
// Should output all customer info under my email (lkaranovic88@gmail.com), and my status. 
Note that my name will now be changed to "Dave", because I resubscribed with that name under my email.
* To make sure show command works properly.

12. Show command on ID 100004.
// Should output "A customer with the given ID does not exist."
* To make sure show command error checking works properly.

13. Add a bunch of new customers and unsubscribe a few.
Add customer with email 'cd'
Add customer with email 'z'
Add customer with email 'yay'
Unsubscribe customer 'ab'
Unsubscribe customer 'z'
// Should output "User created and subscribed successfully!"
// "User created and subscribed successfully!"
// "User created and subscribed successfully!"
// "User with ID: 100003 has unsubscribed."
// "User with ID: 100005 has unsubscribed."
* Adding all of this data for the final few tests on larger sample size.

14. Spam command on my BST of size 6.
// Should output email and name of customers with emails 'aa', 'cd', 'lkaranovic88@gmail.com', 'yay', in this order.
* Testing to make sure my spam command outputs all subscribed users and no unsubscribed users in the correct order.

15. List command on my RBT of size 6.
// Should output all 6 customer names and IDs in order of ID (100001-100006).
* Testing to make sure my list command outputs all users, subscribed or unsubscribed.

16. Terminate the program.
// Should output "Program is being terminated, cleaning all customer data."
// "Deleting customer trees..."
// "Thank you for using the program!"
Note there should also be a valgrind output showing that there are no errors/leaks.
* Testing to make sure quit command works, program terminates, and that all memory is freed properly.

## Known Bugs
No known bugs to date (November 8, 2024. v1.0.0).

## Notes
No notes at this time.