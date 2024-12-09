/**
 * @file main.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.0
 * @date December 6, 2024
 *
 * Main routine to test for lab10B.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"
using namespace std;

int main() {

    ifstream input("input.txt");

    if (!input.is_open()) {
        cout << "Unable to open input file. Check if it exists or if it has read permissions." << endl;
        exit(1);
    }
    vector<string> V;

    string line;
    getline(input, line);
    int numE = stoi(line);

    for (int i = 0; i < numE; i++) {
       	bool found = false; 
		getline(input, line, ' ');
        string course1 = line;
		for (int i = 0; i < (int)V.size(); i++) {
			if (course1 == "none" || course1 == V[i]) {
				found = true;
			}
		}
		if (found == false) {
			V.push_back(line);
		}
        found = false;
		getline(input, line);
        string course2 = line;
		for (int i = 0; i < (int)V.size(); i++) {
			if (course2 == "none" || course2 == V[i]) {
				found = true;
			}
		}
		if (found == false) {
			V.push_back(line);
		}
    }

    Graph g(V, V.size());
	input.close();
	ifstream input2("input.txt");

	getline(input2, line);
    numE = stoi(line);

    for(int i = 0; i < numE; i++){
        getline(input2, line, ' ');
        string course1 = line;
        getline(input2, line);
        string course2 = line;

        int v1 = g.findVertex(course1);
        int v2 = g.findVertex(course2);
        if (v1 != -1 && v2 != -1) {
            g.insertEdge(v1, v2);
        }
    }
	g.printMatrix();

	input2.close();
	return 0;
}