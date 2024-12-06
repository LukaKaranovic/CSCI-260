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
#include <string>
#include <vector>
#include "graph.h"
using namespace std;
//int argc, char** argv
int main() {

    vector<string> V;
    
    V.push_back("Daisy");
    V.push_back("Heather");
    V.push_back("Iris");
    V.push_back("Jasmine");
    V.push_back("Rose");
    V.push_back("Violet");

    Graph g(V, V.size());

    g.insertEdge(0, 2, 7.5, 50);
    g.insertEdge(0, 1, 25.8, 60);
    g.insertEdge(0, 5, 14.2, 80);
    g.insertEdge(1, 3, 12.7, 28);
    g.insertEdge(2, 3, 8.3, 75);
    g.insertEdge(2, 5, 3.5, 35);
    g.insertEdge(3, 5, 2.1, 67);

    vector<Edge> DaisyIris = g.findPath(0, 2);

    cout << "Daisy - Iris, 38" << endl;
    for (unsigned int i = 0; i < DaisyIris.size(); i++) {
        cout << "Cost: " << DaisyIris[i].unitCost << "\t" << "Capacity: " << DaisyIris[i].capacity << "\t" << endl;
    }

    vector<Edge> DaisyJasmine = g.findPath(0, 3);

    cout << "Daisy - Jasmine, 52" << endl;
    for (unsigned int i = 0; i < DaisyJasmine.size(); i++) {
        cout << "Cost: " << DaisyJasmine[i].unitCost << "\t" << "Capacity: " << DaisyJasmine[i].capacity << "\t" << endl;
    }

    vector<Edge> DaisyViolet = g.findPath(0, 5);

    cout << "Daisy - Violet, 62" << endl;
    for (unsigned int i = 0; i < DaisyViolet.size(); i++) {
        cout << "Cost: " << DaisyViolet[i].unitCost << "\t" << "Capacity: " << DaisyViolet[i].capacity << "\t" << endl;
    }


    vector<Edge> HeatherViolet = g.findPath(1, 5);

    cout << "Heather - Violet, 59" << endl;
    for (unsigned int i = 0; i < HeatherViolet.size(); i++) {
        cout << "Cost: " << HeatherViolet[i].unitCost << "\t" << "Capacity: " << HeatherViolet[i].capacity << "\t" << endl;
    }


    vector<Edge> HeatherRose = g.findPath(1, 4);

    cout << "Heather - Rose, 15" << endl;
    for (unsigned int i = 0; i < HeatherRose.size(); i++) {
        cout << "Cost: " << HeatherRose[i].unitCost << "\t" << "Capacity: " << HeatherRose[i].capacity << "\t" << endl;
    }

    g.printMatrix();
    /*
    {-1 0 0}        {25.8 60 0}     {7.5 50 0}      {-1 0 0}        {-1 0 0}        {14.2 80 0}
    {25.8 60 0}     {-1 0 0}        {-1 0 0}        {12.7 28 0}     {-1 0 0}        {-1 0 0}
    {7.5 50 0}      {-1 0 0}        {-1 0 0}        {8.3 75 0}      {-1 0 0}        {3.5 35 0}
    {-1 0 0}        {12.7 28 0}     {8.3 75 0}      {-1 0 0}        {-1 0 0}        {2.1 67 0}
    {-1 0 0}        {-1 0 0}        {-1 0 0}        {-1 0 0}        {-1 0 0}        {-1 0 0}
    {14.2 80 0}     {-1 0 0}        {3.5 35 0}      {2.1 67 0}      {-1 0 0}        {-1 0 0}
    */

    return 0;

}

/*
{-1 0 0}        {25.8 60 0}     {7.5 50 0}      {-1 0 0}        {-1 0 0}        {14.2 80 0}
{25.8 60 0}     {-1 0 0}        {-1 0 0}        {12.7 28 0}     {-1 0 0}        {-1 0 0}
{7.5 50 0}      {-1 0 0}        {-1 0 0}        {8.3 75 0}      {-1 0 0}        {3.5 35 0}
{-1 0 0}        {12.7 28 0}     {8.3 75 0}      {-1 0 0}        {-1 0 0}        {2.1 67 0}
{-1 0 0}        {-1 0 0}        {-1 0 0}        {-1 0 0}        {-1 0 0}        {-1 0 0}
{14.2 80 0}     {-1 0 0}        {3.5 35 0}      {2.1 67 0}      {-1 0 0}        {-1 0 0}
*/