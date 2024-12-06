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
    double unitCost;
    int capacity;
    int load;
} Edge;

class Graph {
    private:
        vector<string> vertices;
        vector<vector<Edge>> adjMatrix;


        int findMin(vector<double>& totalCost, vector<bool>& visited);

        //vector<Edge*> processPath(vector<int>& path, int dest);

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
    * Inserts a new vertex with a given name into the graph.
    */
    void insertVertex(string name);

    int findVertex(string name);

    /**
    * Inserts a new edge with two given vertices, a unit cost, and a volume capacity into the graph.
    */
    void insertEdge(int v1, int v2, double cost, int capacity);

    vector<int> findPath(int source, int dest);

    void printMatrix();

    void updateLoad(int demand, int v1, int v2);

};


#endif