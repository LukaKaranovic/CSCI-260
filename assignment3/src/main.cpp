/**
 * @file main.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date December 3, 2024
 *
 * Implements the main routine for this application, which includes getting a command line argument,
 * reading an infrastructure from an input file, and reporting the analysis of it to an output file.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Expected use is './bin/pex3 filename', where filename is the path to the file relative to the current directory: " << endl;
        cout << "E.g. ./bin/pex3 testing/input1.txt";
        exit(1);
    }
    string filename = argv[1];
    //cout << "Enter the file that contains your network information: " << endl;

    ifstream input(filename);

    if (!input.is_open()) {
        cout << "Unable to open input file. Check if it exists or if it has read permissions" << endl;
        exit(1);
    }
    vector<string> V;

    string line;
    getline(input, line);
    int numV = stoi(line);

    for (int i = 0; i < numV; i++) {
        getline(input, line);
        V.push_back(line);
    }

    Graph g(V, V.size());

    getline(input, line);
    int numE = stoi(line);

    for(int i = 0; i < numE; i++){
        getline(input, line, ' ');
        string server1 = line;
        getline(input, line, ' ');
        string server2 = line;
        getline(input, line, ' ');
        float unitCost = stof(line);
        getline(input, line);
        int capacity = stoi(line);
        int v1 = g.findVertex(server1);
        int v2 = g.findVertex(server2);
        if (v1 != -1 && v2 != -1) {
            g.insertEdge(v1, v2, unitCost, capacity);
        }
    }

    getline(input, line);
    int numConnections = stoi(line);
    cout << "Number of connections: " << numConnections << endl;
    


    for(int i = 0; i < numConnections; i++){
        getline(input, line, ' ');
        string server1 = line;
        getline(input, line, ' ');
        string server2 = line;
        getline(input, line);
        int demandedCost = stoi(line);
        int v1 = g.findVertex(server1);
        int v2 = g.findVertex(server2);
        vector<int> shortestPath = g.findPath(v1, v2); 

        if (shortestPath[(int)shortestPath.size()-1] != v2) {
            // report bad results.
            continue;
        }
        cout << endl;
        for (int j = 0; j < (int)shortestPath.size()-1; j++) {
            g.updateLoad(demandedCost, shortestPath[j], shortestPath[j+1]);
        }
    }

    g.printMatrix();

    input.close();
    return 0;

}