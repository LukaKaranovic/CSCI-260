/**
 * @file jobqueue.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.4
 * @date September 24, 2024
 *
 * Implements a JobQueue class.
 * This class holds a priority queue of the job data type. This priority queue is
 * implemented using a heap ADT. The heap is implemented using a dynamic array.
 */

#include "job.h"
#include "dynamicarray.h"
#include "jobqueue.h"
#include <string>
#include <ostream>

using namespace std;


/** @brief Compares three jobs (typically parent and both children) to see which 
 *  job has the highest priority.
 *
 *  Meant to be used with parent and child nodes. Left child is at index parent * 2 + 1 and right child is 
 *  at index parent * 2 + 2. The function compares the parent to the left child to see which has higher priority.
 *  Then the function checks if the parent has a right child, if so, it compares the right child with the highest
 *  priority job of the left child and parent, and then returns whatever job has the highest priority.
 *  
 *  @param parent The index of a job that is the parent of the subtree in the heap.
 *  @param child1 The index of a job that is the left child of the parent job.
 *  @param child2 The index of a job that is the right child of the parent job.
 *  @return The index of the job with the highest priority of the three jobs.
 */

int JobQueue::findMin(int parent, int child1, int child2) {
    int minimum = parent;
    if (jobArr[child1] > jobArr[minimum]) {
        minimum = child1;
    }
    // If right child doesn't exist, it's index is -1, will skip this.
    if ((child2 >= 0 && child2 < jobArr.size()) && jobArr[child2] > jobArr[minimum]) { 
        minimum = child2;
    }
    return minimum;
}

/** @brief Compares a job node's priority with its parent job node to maintain heap order.
 *
 *  Compares a job at an index with its parent at (i - 1) / 2. If the job has a higher priority
 *  than its parent, it swaps the two nodes and repeats the comparing process moving up the tree
 *  until all nodes are in heap order.
 *  
 *  @param currentNode The index of a job that is the child of a parent in the heap.
 *  @return Void.
 */

void JobQueue::upheap(int currentNode) {
    // Root node is already at the top and cannot be upheaped.
    if (currentNode == 0) {
        return;
    }
    
    int parent = (currentNode - 1) / 2;

    while (currentNode > 0 && jobArr[parent] < jobArr[currentNode]) {
        swap(currentNode, parent);
        currentNode = parent;
        parent = (currentNode - 1) / 2;
    }
}

/** @brief Compares a job node's priority with its children job nodes to maintain heap order.
 *
 *  Compares a job at an index with its left child at i * 2 + 1 and right child at i * 2 + 2. If a child has 
 *  a higher priority than its parent, it swaps the two nodes and repeats the comparing process moving down the heap tree
 *  until all nodes are in heap order.
 *  
 *  @param currentNode The index of a job that is the parent of children in the heap.
 *  @return Void.
 */

void JobQueue::downheap(int currentNode) {
    int leftChild = (currentNode * 2) + 1;
    int rightChild = (currentNode * 2) + 2;

    // If currentNode has no left child, currentNode must be a leaf node.
    if (leftChild >= jobArr.size()) {
        return;
    }
    // If currentNode has no right child, move the index outside of array bounds.
    if (rightChild >= jobArr.size()) {
        rightChild = -1;
    }

    int highestPriority = findMin(currentNode, leftChild, rightChild);
    if (highestPriority != currentNode) {
        swap(currentNode, highestPriority);
        downheap(highestPriority);
    }
}

/** @brief Swaps the data (job objects) of two different indexes of the job dynamic array heap.
 *
 *  @return Void.
 */

void JobQueue::swap(int x, int y) {
    Job temp = jobArr[x];
    jobArr[x] = jobArr[y];
    jobArr[y] = temp;
}

/** @brief Default constructor
 *
 */

JobQueue::JobQueue(): jobArr(DynamicArray<Job>()) {}

/** @brief Destructor
 * 
 *  Dynamic array class handles destruction of array.
 */

JobQueue::~JobQueue() {}

/** @brief Inserts a job into the job queue.
 *
 *  The job will be inserted into the bottom of the heap (last index). 
 *  An upheap will be performed on the new job to maintain heap order.
 *  If the job queue is full, the job queue will expand to double its size and
 *  then insert the new job.
 * 
 *  @return Void.
 */

void JobQueue::insert(Job job) {
    if (jobArr.isFull()) {
        jobArr.expand();
    }
    jobArr.insert(job);
    upheap(jobArr.size()-1);
}

/** @brief Removes the job with the highest priority from the queue.
 *
 *  Stores the highest priority job in a variable, then swaps the high priority job
 *  with the last job in the queue. Decrements the size by 1 as a job was removed from the queue. 
 *  Performs downheap to maintain heap order.
 * 
 *  @return The job that was removed from the job queue.
 */

Job& JobQueue::removeMin() {
    swap(0, jobArr.size() - 1);
    Job& temp = jobArr[jobArr.size()-1];
    jobArr.decSize();
    downheap(0);
    return temp;
}

/** @brief Removes the job at a particular index from the queue.
 *
 *  Stores the job at the index in a variable, then swaps the job
 *  with the last job in the queue. Decrements the size by 1 as a job 
 *  was removed from the queue. Then performs downheap on the swapped job
 *  to maintain heap order.
 *  
 *  @param index The index of the job to be removed from the queue.
 *  @return The job that was removed from the job queue.
 */

Job& JobQueue::removeAt(int index) {
    if (index == 0) {
        return removeMin();
    }
    swap(index, jobArr.size()-1);
    Job& temp = jobArr[jobArr.size()-1];
    jobArr.decSize();
    downheap(index);
    return temp;
}

/** @brief Looks at the job object that has the highest priority (top of the heap).
 * 
 *  @return The job with the highest priority in the queue.
 */

Job& JobQueue::peek() {
    return jobArr[0];
}

/** @brief Returns the job queue's current size.
 * 
 *  @return The current size of the job queue.
 */

int JobQueue::getSize() {
    return jobArr.size();
}

/** @brief Checks if the job queue is empty or not. 
 *
 *  A job queue is empty if its current size is 0.
 *
 *  @return True if it is empty, and false if it is not empty.
*/

bool JobQueue::isEmpty() {
    return jobArr.isEmpty();
}

/** @brief Checks if the job queue is full or not. 
 *
 *  A job queue is full if its current size equals its capacity.
 *
 *  @return Returns true if it is full, and false if it is not full.
*/

bool JobQueue::isFull() {
    return jobArr.isFull();
}

/** @brief Displays the information of each job currently in the queue one by one.
 *
 *  Note: The siblings in each layer of the heap may not always be in priority order, so
 *  the display isn't accurate to the complete order of the list, only layer by layer.
 *
 *  @return Void.
*/

void JobQueue::displayQueue() {
    for (int i = 0; i < jobArr.size(); i++) {
        jobArr[i].displayInfo();
    }
}