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
#include "../include/graph.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

    int Graph::findMin(vector<double>& pathCost, vector<bool>& visited) {
        double min = INFINITY;
        int target;

        for (unsigned int i = 0; i < vertices.size(); i++) {
            if (!visited[i] && pathCost[i] < min) {
                min = pathCost[i];
                target = i;
            }
        }
        return target;
    }

    // vector<Edge*> Graph::processPath(vector<int>& path, int dest) {
    //     vector<Edge*> edgePath;

    //     for (unsigned int i = 0; i < path.size()-1; i++) {
    //         edgePath.push_back(adjMatrix[path[i]][path[i+1]]);
    //         edgePath.push_back(adjMatrix[path[i+1]][path[i]]);
    //     }

    //     if (path[path.size()-1] != dest) {
    //         edgePath.clear();
    //     }

    //     return edgePath;
    // }

    Graph::Graph(vector<string> V, int size): vertices(V) {
        adjMatrix = vector<vector<Edge>>(size, vector<Edge>(size, {-1, 0, 0}));
    }

    Graph::~Graph() {
        vertices.clear();
        adjMatrix.clear();
    }

    void Graph::insertVertex(string name) {
        for (unsigned int i = 0; i < vertices.size(); i++) {
            if (name == vertices[i]) {
                return;
                //throw invalid_argument("Vertex with this name already exists within the graph.");
            }
        }
        
        vertices.push_back(name);
    }


    int Graph::findVertex(string name) {
        for (unsigned int i = 0; i < vertices.size(); i++) {
            if (name == vertices[i]) {
                return i;
            }
        }
        return -1;
    }

    void Graph::insertEdge(int v1, int v2, double cost, int capacity) {
        if (adjMatrix[v1][v2].unitCost != -1 && adjMatrix[v1][v2].unitCost != -1) {
            return;
            //throw invalid_argument("An edge with these vertices already exists within the graph.");
        }
        adjMatrix[v1][v2] = {cost, capacity, 0};
        adjMatrix[v2][v1] = {cost, capacity, 0};
    }

    vector<int> Graph::findPath(int source, int dest) {
        vector<double> pathCost(vertices.size(), INFINITY); // initalize all nodes to have cost of +inf
        pathCost[source] = 0;
        vector<int> path;
        vector<bool> visited((int)vertices.size(), false);

        for (unsigned int i = 0; i < vertices.size(); i++) {
            int curr = findMin(pathCost, visited);
            visited[curr] = true;

            bool foundAdj = false;
            for (unsigned int j = 0; j < vertices.size(); j++) {
                if ((!visited[j]) && (adjMatrix[curr][j].unitCost != -1) && (pathCost[curr] != INFINITY)) {
                    foundAdj = true;
                    if (pathCost[curr] + adjMatrix[curr][j].unitCost < pathCost[j]) {
                        pathCost[j] = pathCost[curr] + adjMatrix[curr][j].unitCost;
                        if (curr == dest) {
                            path.push_back(curr);
                            //return processPath(path, dest);
                            return path;
                        }
                    }
                }
            }
            if (foundAdj == true) {
                path.push_back(curr);    
            }
        }
        //return processPath(path, dest);
        if (path[(int)path.size()-1] != dest) {
            path.clear();
        }
        return path;
    }

    void Graph::printMatrix() {
        for (unsigned int i = 0; i < adjMatrix.size(); i++) {
            for (unsigned int j = 0; j < adjMatrix.size(); j++) {
                cout << "{" << adjMatrix[i][j].unitCost << " " << adjMatrix[i][j].capacity << " " << adjMatrix[i][j].load << "}\t";
            }
            cout << endl;
        }
    }

    void Graph::updateLoad(int demand, int v1, int v2) {
        adjMatrix[v1][v2].load += demand;
        adjMatrix[v2][v1].load += demand;
    }


    

