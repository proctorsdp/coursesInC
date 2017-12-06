//
//  graph.hpp
//  Snowblower Path
//
//  Created by Steven Proctor on 12/7/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "edge.h"

using namespace std;


class Graph {
    
public:
    
    Graph(string, ostream &);           //constructor: takes input filename and output format
    ~Graph();                           //destructor
    
    void computeTour(ostream &);        //finds Euler tour of graph: takes output format
    
private:
    
    vector<Edge> edgeArr;               //stores all edges and related information in an array
    vector<int> cycleStack;             //First in Last out queue to track which cycles have been traversed
    vector<char> eulerTour;             //Stores the euler tour of the graph
    vector<char> cyclePath;             //Stores the current cycle
    int ** adjMatrix;                   //stores the subscript of the edge array in the location where two nodes share an edge
    int numNodes;                       //number of nodes in a graph
    int numEdges;                       //number of edges in a graph
    bool debug = false;                 //prints debuging information to the console if true
    
    void buildMatrix(int);              //fills matrix with -1, indicating that there are no edges between nodes
    void fillMatrix();                  //updates matrix to contain the edges stored in the edge array
    bool isEulerTour();                 //returns true if the graph has an euler tour
    void markCycles(int, int);          //beginning with a random node creates a cycle inside the graph
    int nextEdge(int, int);             //returns the next edge to follow when creating a cycle
    bool unusedEdges();                 //returns true if there are edges not yet used in any cycle
    int nextUnused();                   //returns the next edge in the array that does not belong to a cycle
    void mergeCycles(int);              //merges all the cycles in a graph until only the euler tour remains
    int nextTourEdge(int);              //returns the next edge to follow when merging cycles
    bool notInStack(int);               //returns true if a given cycle has not yet been touched by the euler tour
    bool missingEdges();                //returns true if there are edges that have not yet been used by the euler tour
    void restartMerge();                //resets all values relating to merge, and restarts the merge process
    
    string printMatrix();               //print the adjacency matrix, numbers refer to the subscript in the edge array containing edge information
    string printArray();                //prints the edge array and which cycle each edge currently belongs to
    string printTour();                 //prints the euler tour for the graph
    string printCycle();                //prints the current cycle
};

#endif /* graph_hpp */
