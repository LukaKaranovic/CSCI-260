# Specifications
CSCI 260 Fall 2024 - Programming Assignment 3 (v1.1.0)

**Problem Description:**
An organization built and maintains a network of communication infrastructure. The infrastructure consists of a set of communication servers, distributed in various locations around the world, and a set of bi-direcitonal (undirected graph) links directly connecting two servers.

Each server is assigned a unique name and is located in a particular location. Because the location information of the servers is irrelevant to the problems we need to solve in this assignment, we'll ignore lcoation information and other features of the servers.

Each direct link connecting two servers together is bidirectional (undirected), has a unit cost for a standard communication volume (weight), and a capacity of how much communication volume it can handle in a unit (time).

The organization conducted a business analysis to identify a list of communication demands. Each demand identifies the communication volume needed between two servers.

**Requirements:**
Develop a C++ program that takes the name of a file containing the infrastructure data and the communication demands identified by the business analysis as its command line argument, then conduct a technology analysis based on the information provided in the file.

More specifically, your technology analysis program should complete the following two tasks based on the provided infrastructure data and business analysis:
    1. Identify any of the communication demands that can't be met by the current infrastructure due to the lack of connected routes between the two servers listed in the demand.
    2. Excluding all the unrealizable demands identified in part 1, if all other communication demands are met with the lowest cost possible, can the current infrastructure handle them? If not, identify any direct links whose volume capacity must be expanded to handle the demands, and calculate how much its volume capacity must be expanded by, with the assumption that the unit cost of the link would remain the same after its capacity expansion.

Write your analysis results in a text file named techAnalysisResult.txt. This report must be easy to read and interpret without any ambiguity.

## Design
For this program, I decided to implement a graph using a set of vertices and an adjacency matrix. I defined my Graph class in 'include/graph.h' and my implementation for it is in 'include/graph.cpp'. Since the vertices require only one string, which is their name, I made the set of vertices a vector of strings, which is passed in order to consturct my graph.

As the edges have multiple values, I made an edge struct storing three values: The unitCost of the edge, the volume capacity of the edge, and the volume load of the edge. The load is always initialized to 0 and is used to calculate the traffic that will go through an edge after calculating the paths for the communication demands, to report to the business whether or not the capacity needs to be increased or not.

To find the shortest path, I used Dijkstra's algorithm as the unitCost of the edges act as positive weights and my graph is undirected. Dijkstra's algorithm was the best algorithm in terms of getting my pathes in the fastest way possible. It was also the easiest path-finding algorithm to modify so that it could track the sequence of vertices travelled from source to destination, which was needed to calculate the communication loads for part 2 of the results.
* I used some vectors to calculate the path and to store my shortest path so that I could report it to main, where I would update the 'load' values of my edges in the adjacency matrix using another helper function 'updateLoad()'.

## Implementation
I used std::vectors for my model because they are the easiest to work with and I wanted to take advantage of the STL.

The way I designed my graph was with an adjacency matrix, this is good because looking up a value for certain checks in a matrix is done in O(1) time, same with inserting. These actions are done quite a bit, so having that efficiency is helped. Some disadvantages of this are that some things take O(N^2) time, where N is the number of vertices in the graph. The things that take O(N^2) time are initailizing the matrix and Dijkstra's algorithm, as it must iterate through all possible edges (whether they are there or not).

The clear alternative was to use an adjacency list, which would take slightly longer to lookUp and insert things, however, initialization is done in O(1) time, and Dijkstra's algorithm can be completed in O(MlogN) time where M = number of edges and N = number of vertices.

I believe a set of edges wouldn't help at all in terms of completing the required tasks for this assignment, and would overcomplicate things.

Another algorithm I could've used was the 'All-Pairs Shortest Path' (APSP) algorithm by Warshall, Floyd, and Ingerman. I chose Dijkstra's algorithm over this one as it seemed easier to modify to hold the sequence of vertices travelled on the path. Additionally, the APSP algorithm overwrites my adjacency matrix, thus overwriting edge data which is needed to calculate and determine my outputs. This means I would have to create a whole new copy of my original adjacency matrix and then update the load values, which is not efficient at all.

## Analysis
There are no commands for this assignment, however, here are the analysis for some parts of main.
Let V = number of vertices in input file
Let E = number of edges in input file
Let C = number of requested connections in input file

To start, constructing the graph takes O(V^2) time as it must initialize the adajcency matrix, which is the dominant growing factor here.

Adding edges to the graph takes O(E) time, as the program must read all the edges to input them in, which only takes O(1) time.

For finding the connections, we must go through a loop C times, where Dijkstra's algorithm, which has complexity O(V^2), executes each time. Overall, this part takes O(C*V^2) time and is the least efficient part of my program.

Finally, the printResults function iterates through half of my adjacency matrix, checking (V^2)/2 elements, so it is done in O(V^2) time. 

Overall, I think my main would've been faster with an adjacency list, but it seemed much harder to implement, and for smaller inputs it may take longer as you lookUp unitCost and capacity values often, which takes longer than an adjacency matrix to find.

## Accomplishment
I have accomplished these parts of the assignment:
* Implementation
* Documentation
* Makefile
* README
* Testing

## Testing
I have input files input1.txt, input2.txt, and input3.txt their expected outputs are stored in output1.txt, output2.txt, and output3.txt respectively.

input1.txt - This test case is the exact same as the sample input file provided in the assignment instructions. I used this as I already had an expected output and wanted to make sure my program was meeting all the requirements it should (solving the problems correctly).

input2.txt - This test case has two detached cycles with one extra vertex (London) appended onto one of the cycles. This was to test whether or not my algoritm would get stuck in loops with the cycles and whether or not it could backtrack more than one vertex (this was testing my foundAdj flag).

input3.txt - This test case has a very detached graph and was testing whether my program would handle having the source vertex be completed isolated (path of length 0 or not). It also tested if it would not print communication demands that were fully met (e.g. Ajay Humayun 54) to the output file.

As I had memory issues, I tested all 3 of these with Valgrind to see if there were any memory leaks in the final version. The output can be viewed in the 'typescript' file in my main 'assignment3' directory.

## Known Bugs
Won't compile on g++ versions older than v8.0 (to my knowledge), see notes.

## Notes
Because of the filesystem library I made to have the output files be in their own directory so they're easy to find, the program won't compile on g++ versions that are older than v8.0 (to my knowledge).