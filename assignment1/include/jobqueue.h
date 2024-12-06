/**
 * @file jobqueue.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.4
 * @date September 24, 2024
 *
 * JobQueue is a priority queue implemented using a heap. The heap is implemented through the DynamicArray<Job> class. The class has private heap methods to maintain heap order.
 * JobQueue has constructors, destructors, basic operations such as insert() and removeMin(), a removeAt() method to remove a job at a specific index (for lottery), and a 
 * displayQueue() method which displays every job currently in the queue (though there is no way to use this from main).
 */


#ifndef ASSN1_JOBQUEUE_H
#define ASSN1_JOBQUEUE_H

#include "job.h"
#include "dynamicarray.h"
#include <string>
#include <ostream>

using namespace std;

class JobQueue {
private:
    DynamicArray<Job> jobArr; // Dynamic array to store data for job queue

    /**
	 * Compares three nodes (typically parent and its children) to find which one 
     * has the highest priority.
	 */
    int findMin(int parent, int child1, int child2);

    /**
	 * Repeatedly compares child node to parent node. If child has a higher priority than
     * parent, swaps the two and compares the child with its new parent after swap.
     * Repeats until reaching root node or parent has higher priority than child.
	 */
    void upheap(int currentNode);

    /**
	 * Repeatedly compares parent node to child node. If parent has a lower priority than
     * child, swaps the two and compares the parent with its new children after swap.
     * Repeats until parent becomes a leaf node and has nothing to compare to.
	 */
    void downheap(int currentNode);

    /**
	 * Swaps the position of two elements in the heap.
	 */
    void swap(int x, int y);

public: 
    /**
	 * Default constructor
	 */
    JobQueue();

    /**
	 * Destructor. Dynamic array destructor handles deletion of data.
	 */
    ~JobQueue();
    
    /**
	 * Inserts a job into the job queue. Upheaps to make sure it is in the correct spot.
	 */
    void insert(Job job);

    /**
	 * Removes the highest priority job from the job queue. Downheaps to make sure heap is maintained.
     * Decreases the size by one.
	 */
    Job& removeMin();

    /**
	 * Removes a job at the target index from the job queue. Downheaps from the target index to make 
     * sure heap is maintained. Decreases the size by one.
	 */
    Job& removeAt(int index);

    /**
	 * Displays information of the job at the front of the queue (highest priority).
	 */
    Job& peek();

    /**
	 * Returns the size of the job queue.
	 */
    int getSize();

    /**
	 * Returns true if the job queue is empty, false if it isn't
	 */
    bool isEmpty();

    /**
	 * Returns true if the job queue is full, false if it isn't
	 */
    bool isFull();

    /**
	 * Displays the entire job queue, listing information about every job in order (used for testing).
	 */
    void displayQueue();

};

#endif