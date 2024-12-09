/**
 * @file graph.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
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
#include "graph.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

    /** @brief Regular Constructor
    * Takes a vector containing the vertices of the graph and constructs an empty adjacency matrix out of it.
    */

    Graph::Graph(vector<string> V, int size): vertices(V) {
        adjMatrix = vector<vector<Edge>>(size, vector<Edge>(size, {false, false}));
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
        if (name == "none") {
            return -1;
        }
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

    void Graph::insertEdge(int v1, int v2) {
        if (adjMatrix[v1][v2].isPreReq != false) {
            cout << "An edge with these vertices already exists within the graph." << endl;
            return;
        }
        adjMatrix[v1][v2] = {false, true};
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
        cout << "\t\t";
        for (int k = 0; k < (int)adjMatrix.size(); k++) {
            cout << vertices[k] << " ";
        }
        cout << endl;
        for (int i = 0; i < (int)adjMatrix.size(); i++) {
            cout << vertices[i] << "\t";
            for (int j = 0; j < (int)adjMatrix.size(); j++) {
                cout << "{" << adjMatrix[i][j].completed << ", " << adjMatrix[i][j].isPreReq << "}\t ";
            }
            cout << endl;
        }
    }

    
