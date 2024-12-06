# Specifications
CSCI 260 Fall 2024 - Programming Assignment 3 (v1.0.0)

**Problem Description:**
An organization built and maintains a network of communication infrastructure. The infrastructure consists of a set of communication servers, distributed in various locations around the world, and a set of bi-direcitonal (undirected graph) links directly connecting two servers.

Each server is assigned a unique name and is located in a particular location. Because the location information of the servers is irrelevant to the problems we need to solve in this assignment, we'll ignore lcoation information and other features of the servers.

Each direct link connecting two servers together is bidirectional (undirected), has a unit cost for a standard communication volume (weight), and a capacity of how much communication volume it can handle in a unit (time).

The organization conducted a business analysis to identify a list of communication demands. Each demand identifies the communication volume needed between two servers.

**Goal:**
Develop a C++ program that takes the name of a file containing the infrastructure data and the communication demands identified by the business analysis as its command line argument, then conduct a technology analysis based on the information provided in the file.

More specifically, your technology analysis program should complete the following two tasks based on the provided infrastructure data and business analysis:
    1. Identify any of the communication demands that can't be met by the current infrastructure due to the lack of connected routes between the two servers listed in the demand.
    2. Excluding all the unrealizable demands identified in part 1, if all other communication demands are met with the lowest cost possible, can the current infrastructure handle them? If not, identify any direct links whose volume capacity must be expanded to handle the demands, and calculate how much its volume capacity must be expanded by, with the assumption that the unit cost of the link would remain the same after its capacity expansion.

Write your analysis results in a text file named techAnalysisResult.txt. This report must be easy to read and interpret without any ambiguity.


graph class 
- vector of vertices
- vector of edges
- number of vertices
- number of edges

vertex class
- name
- location
- adjacency list
- visited bool maybe

edge class
- unit cost
- capacity

## Design

## Implementation

## Analysis

## Accomplishment


## Testing


## Known Bugs


## Notes
