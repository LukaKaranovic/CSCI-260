/**
 * @file graph.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.1.0
 * @date December 3, 2024
 *
 * Implements the methods for the Graph class defined in the 'include/graph.h' header file.
 * This class contains a vector of vertex objects and a vector of edge objects, both of which are defined in the 'include/vertex.h' header file.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "../include/graph.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

    /** @brief Searches for the lowest unitCost edge adjacent to the current vertex.
    *
    *  This is a helper function for Dijkstra's algorithm (implemented in findPath()). It searches for the lowest unitCost neighbour (that hasn't been visited already).
    *  of the current vertex in Dijkstra's algorithm, so that it can move to the new vertex and explore its neighbours to construct more pathes.
    *
    *  @param pathCost A vector containing the total unitCost of the path from the source (defined in findPath()) to each vertex in the graph.
    *  @param visited A vector containing information on whether a vertex in the graph has already been explored in Dijkstra's algorithm or not.
    *  @return The lowest unitCost unvisited neighbour of the current vertex in the graph.
    */

    int Graph::findMin(vector<double>& pathCost, vector<bool>& visited) {
        double min = INFINITY;
        int target = -1;

        for (int i = 0; i < (int)vertices.size(); i++) {
            if (!visited[i] && pathCost[i] < min) {
                min = pathCost[i];
                target = i;
            }
        }
        return target;
    }

    /** @brief Regular Constructor
    * Takes a vector containing the vertices of the graph and constructs an empty adjacency matrix out of it.
    */

    Graph::Graph(vector<string> V, int size): vertices(V) {
        adjMatrix = vector<vector<Edge>>(size, vector<Edge>(size, {-1, 0, 0}));
    }

    /** @brief Destructor
    *
    */

    Graph::~Graph() {
        vertices.clear();
        adjMatrix.clear();
    }

    /** @brief Searches for the vertex with a matching name and returns its integer index in the vector.
    *
    *  @param name The name of the vertex being searched for.
    *  @return The index in the vertices vector of the target vertex.
    */

    int Graph::findVertex(string name) {
        for (int i = 0; i < (int)vertices.size(); i++) {
            if (name == vertices[i]) {
                return i;
            }
        }
        return -1;
    }

    /** @brief Inserts an edge into the graph's adjacency matrix.
    *
    *  Takes input edge data from parameters and inserts it into the appropriate place in the adjacency matrix. Will not insert
    *  an edge if there is an existing edge between those two vertices already. A non existent edge has the form {-1, 0, 0} - unitCost is negative.
    *
    *  @param v1 The first vertex endpoint of the edge.
    *  @param v2 The second vertex endpoint of the edge.
    *  @param cost The unitCost/weight of the edge.
    *  @param capacity The volume capacity of the edge.
    *  @return Void.
    */


    void Graph::insertEdge(int v1, int v2, double cost, int capacity) {
        if (adjMatrix[v1][v2].unitCost != -1 && adjMatrix[v1][v2].unitCost != -1) {
            cout << "An edge with these vertices already exists within the graph." << endl;
            return;
        }
        adjMatrix[v1][v2] = {cost, capacity, 0};
        adjMatrix[v2][v1] = {cost, capacity, 0};
    }

    /** @brief Finds the shortest unitCost path between the source vertex and destination vertex.
    *
    *  Uses Dijkstra's algorithm to calculate all possible pathes from source to destination, and returns the shortest cost path from source to destination.
    *  Uses several vectors to aid in finding the path: pathCost to calculate the totalCost from, source to every other vertex (to find best intermediate pathes),
    *  visited to see which vertices have already been visited or not, and path to store the sequence of vertices to get from source to destination 
    *  so that the edge data can be updated.
    *
    *  @param source The source/starting vertex of the path.
    *  @param dest The destination/ending vertex of the path.
    *  @return The sequence of vertices taken from source to destination in the lowest unitCost.
    */


    vector<int> Graph::findPath(int source, int dest) {
        vector<double> pathCost((int)vertices.size(), INFINITY); // initalize all nodes to have cost of +inf
        pathCost[source] = 0;
        vector<int> path;
        vector<bool> visited((int)vertices.size(), false);

        for (int i = 0; i < (int)vertices.size(); i++) {
            int curr = findMin(pathCost, visited);
            if (curr == dest) {
                path.push_back(curr);
                return path;
            } else if (curr == -1) {
                return path;
            }
            visited[curr] = true;
            bool foundAdj = false;
            for (int j = 0; j < (int)vertices.size(); j++) {
                if ((!visited[j]) && (adjMatrix[curr][j].unitCost != -1) && (pathCost[curr] != INFINITY)) {
                    foundAdj = true;
                    if (pathCost[curr] + adjMatrix[curr][j].unitCost < pathCost[j]) {
                        pathCost[j] = pathCost[curr] + adjMatrix[curr][j].unitCost;
                    }
                }
            }
            // If no adjacent nodes are found, it is a dead end, so we should backtrace 1 step and check again.
            if (foundAdj == true) {
                path.push_back(curr);    
            } else {
                if ((int)path.size() <= 1) {
                    // This is so there is no segmentation fault when checking in main, note that -1 is an invalid index.
                    path.push_back(-1); 
                    return path;
                } else if (path[(int)path.size()-1] != dest) {
                    path.pop_back();
                }
            }
        }
        return path;
    }

    /** @brief Prints the data from the graph's adjacency matrix.
    *
    *  Labels each row with the first letter of the vertex's name (for convenience). Each entry is encased by {}, the first
    *  number is the unitCost of the edge, the second number is the volume capacity, the third number is the communication load
    *  after the demands have been processed. An empty edge has the form {-1, 0, 0}.
    *
    *  @return Void.
    */

    void Graph::printMatrix() {
        for (int i = 0; i < (int)adjMatrix.size(); i++) {
            cout << vertices[i][0] << ":\t";
            for (int j = 0; j < (int)adjMatrix.size(); j++) {
                cout << "{" << adjMatrix[i][j].unitCost << " " << adjMatrix[i][j].capacity << " " << adjMatrix[i][j].load << "}\t";
            }
            cout << endl;
        }
    }

    /** @brief Updates the communication load of an edge based on the communication demands given.
    *
    *  @return Void.
    */

    void Graph::updateLoad(int demand, int v1, int v2) {
        adjMatrix[v1][v2].load += demand;
        adjMatrix[v2][v1].load += demand;
    }

    /** @brief Prints the results relating to volume capacity requirements based on the communication demands given.
    *
    *  As the graph is undirected, only checks one half of the adjacency matrix as to not output double results. Compares each edge's communication volume load with
    *  its communication volume capacity. If the required load is greater than the capacity, outputs the required value it must be increased to so that the edge can meet
    *  the demands in the output file.
    *
    *  @return Void.
    */

    void Graph::printResults(std::ostream& stream) {
        stream << "In order to meet the rest of the communication demands with the lowest cost possible, the following direct link(s) must expand their capacity: " << endl;
        for (int i = 0; i < (int)adjMatrix.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (adjMatrix[i][j].capacity < adjMatrix[i][j].load) {
                    stream << vertices[i] << " to " << vertices[j] << " must expand its capacity from " << adjMatrix[i][j].capacity << " to " << adjMatrix[i][j].load << endl;
                }
            }
        
        }
    }

    
