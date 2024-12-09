/**
 * @file graph.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date December 3, 2024
 *
 * Defines a Graph class which holds a vector of Vertex objects and Edge objects (both defined in include/vertex.h).
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

#ifndef ASSN3_GRAPH_H
#define ASSN3_GRAPH_H

typedef struct Edge {
    bool completed = false;
    bool isPreReq = false;       // The communication volume load of an edge based on the demands given, always initialized to 0.
} Edge;

class Graph {
    private:
        vector<string> vertices;        // A vector containing all of the vertices of the graph. It is a string vector as no location information is needed, so we just need name.
        vector<vector<Edge>> adjMatrix; // A 2-D vector containing an adjacency matrix with all of the information relating to the edges in the graph.

    public:

        /**
        * Regular constructor
        */
        Graph(vector<string> V, int size);

        /**
        * Destructor
        */
        ~Graph();

        /**
        * Returns the integer index of the vertex in the 'vertices' vector given a target name.
        */
        int findVertex(string name);

        /**
        * Inserts a new edge with two given vertices, a unit cost, and a volume capacity into the graph.
        */
        void insertEdge(int v1, int v2);

        /**
        * Helper function that prints out the adjacency matrix of a graph. Labels each row with the first letter of the vertex.
        */
        void printMatrix();

};


#endif