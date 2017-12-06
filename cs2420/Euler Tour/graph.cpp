//
//  graph.cpp
//  Snowblower Path
//
//  Created by Steven Proctor on 12/7/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "graph.hpp"



//Reads in data from input file to Adjacency Matrix and Edge Array
Graph::Graph(string fileName, ostream & out) {
    fstream fin;
    fin.open(fileName);
    assert(fin);

    fin >> numNodes;
    fin >> numEdges;
    
    char from, to;
    while (!fin.eof()) {
        fin >> from;
        fin >> to;
        Edge newEdge = * new Edge;
        newEdge.set(from, to);
        edgeArr.push_back(newEdge);
    }
    
    edgeArr.pop_back();
    buildMatrix(numNodes);
    fillMatrix();
    
    if (debug) {
        cout << printArray() << endl << endl;
        cout << printMatrix() << endl << endl;
    }
    
    fin.close();
}



//Destroys all data structures when closed
Graph::~Graph() {
    for (int i = 0; i < numNodes; i++) {
        delete[] adjMatrix[i];
    }
    
    delete[] adjMatrix;
    edgeArr.clear();
    eulerTour.clear();
    cycleStack.clear();
    cyclePath.clear();
}



//Finds the Euler tour for a given graph
void Graph::computeTour(ostream & out) {
    if (!isEulerTour()) {
        out << "There is no possible Euler Tour for this graph!\n\n\n";
        return;
    }
    
    int cycle = 1;
    while (unusedEdges()) {
        markCycles(rand() % numNodes, cycle);
        out << "Cycle " << cycle << ": ";
        out << printCycle() << endl;
        cycle++;
    }
    
    if (debug) cout << printArray() << endl;
    mergeCycles(rand() % numNodes);
    
    out << endl << printArray() << endl;
    out << endl << printMatrix() << endl;
    out << endl << printTour() << endl;
    out << endl << endl << endl;
}



//Fills the Matrix with -1, implying no edges
void Graph::buildMatrix(int numNodes) {
    adjMatrix = new int * [numNodes];
    for (int i = 0; i < numNodes; i++) {
        adjMatrix[i] = new int [numNodes];
        for (int j = 0; j < numNodes; j++) {
            adjMatrix[i][j] = -1;
        }
    }
}



//Updates the Matrix to contain the edges from the input file
void Graph::fillMatrix() {
    for (int i = 0; i < numEdges; i++) {
        adjMatrix[edgeArr[i].fromNode][edgeArr[i].toNode] = i;
        adjMatrix[edgeArr[i].toNode][edgeArr[i].fromNode] = i;
    }
}



//Returns true if the Euler tour is possible for the graph
//Return false if there is no possible Euler Tour
bool Graph::isEulerTour() {
    int edgeCount;
    
    for (int i = 0; i < numNodes; i++) {
        edgeCount = 0;
        for (int j = 0; j < numNodes; j++) {
            if (adjMatrix[i][j] > -1) { edgeCount++; }
        }
        if (edgeCount % 2 != 0) { return false; }
    }
    
    return true;
}



//Beginning with a random node, marks a cycle withing the graph
//A cycle begins and ends at the same node.
void Graph::markCycles(int start, int cycle) {
    int current = start;
    int path;
    
    cyclePath.clear();
    cyclePath.push_back(char('A' + current));
    
    do {
        path = nextEdge(current, cycle);
        if (path == -1) { markCycles(rand() % numNodes, cycle); return;}
        edgeArr[path].cycleID = cycle;
        
        if (debug) cout << char('A' + current) << "->";
        current = edgeArr[path].getOtherEndpoint(current);
        cyclePath.push_back(char('A' + current));
        if (debug) cout << char('A' + current) << endl;
        
    } while (current != start);
    if (debug) cout << endl << endl;
}



//Merges the various cycles in the graph until obtaining an euler tour
void Graph::mergeCycles(int start) {
    int current = start;
    eulerTour.push_back(current);
    int path;
    
    do {
        path = nextTourEdge(current);
        if (path == -1) { restartMerge(); return;}
        edgeArr[path].used = true;
        if (cycleStack.empty() || cycleStack.back() != edgeArr[path].cycleID){
            cycleStack.push_back(edgeArr[path].cycleID);
        }
        if (debug) cout << char('A' + current) << "->";
        current = edgeArr[path].getOtherEndpoint(current);
        if (debug) cout << char('A' + current) << endl;
        eulerTour.push_back(current);
    } while (missingEdges());
}



//returns the next edge to follow when creating euler tour
int Graph::nextTourEdge(int current) {
    if (cycleStack.empty()) {
        for (int i = 0; i < numNodes; i++) {
            if (adjMatrix[current][i] > -1) {
                return adjMatrix[current][i];
            }
        }
    }
    
    int newCycle = -1;
    int sameCycle = -1;
    int oldCycle = -1;
    
    for (int i = 0; i < numNodes; i++) {
        if (adjMatrix[current][i] > -1 && !edgeArr[adjMatrix[current][i]].used) {
            if (notInStack(edgeArr[adjMatrix[current][i]].cycleID) && newCycle == -1) {
                newCycle = adjMatrix[current][i];
            }
            else if (edgeArr[adjMatrix[current][i]].cycleID == cycleStack.back() && sameCycle == -1) {
                sameCycle = adjMatrix[current][i];
            }
            else if (edgeArr[adjMatrix[current][i]].cycleID == cycleStack[cycleStack.size() - 2] && oldCycle == -1) {
                oldCycle = adjMatrix[current][i];
            }
        }
    }
    
    if (newCycle != -1) { return newCycle; }
    else if (sameCycle != -1) { return sameCycle; }
    else if (oldCycle != -1) {
        cycleStack.pop_back();
        return oldCycle;
    }
    
    return -1;
}



//if the merge misses the group of nodes, restart merge will reset the values associated
//with merging, and will try to merge the cycles again beginning from a different node
void Graph::restartMerge() {
    cycleStack.clear();
    eulerTour.clear();
    
    for (int i = 0; i < numEdges; i++) {
        edgeArr[i].used = false;
    }
    
    mergeCycles(rand() % numNodes);
}



//Determines whether a portion of a particular cycle has already been traversed
bool Graph::notInStack(int ID) {
    for (int i = 0; i < cycleStack.size(); i++) {
        if (ID == cycleStack[i]) { return false; }
    }
    return true;
}



//Returns the next to follow when building a cycle
int Graph::nextEdge(int from, int cycles) {
    for (int i = 0; i < numNodes; i++) {
        if (adjMatrix[from][i] > -1 && edgeArr[adjMatrix[from][i]].cycleID < 0) {
            return adjMatrix[from][i];
        }
    }
    return -1;
}



//return true if there are edges that have not been used in a cycle
//returns false if all edges in the graph have been used a cycle
bool Graph::unusedEdges() {
    for (int i = 0; i < numEdges; i++) {
        if (edgeArr[i].cycleID == -1) {
            return true;
        }
    }
    return false;
}



//Return the next unused edge in the edge array when building a cycle
int Graph::nextUnused() {
    for (int i = 0; i < numEdges; i++) {
        if (edgeArr[i].cycleID == -1) {
            return edgeArr[i].fromNode;
        }
    }
    return -1;
}



//return true if there are edges that have not been used in the euler tour
//returns false if all edges in the graph have been used in the euler tour
bool Graph::missingEdges() {
    for (int i = 0; i < numEdges; i++) {
        if (edgeArr[i].used == false) {
            return true;
        }
    }
    return false;
}



//Prints the contents of the adjacency matrix
string Graph::printMatrix() {
    stringstream ss;
    int w = 6;
    
    ss << "Adjacency Matrix:\n";
    ss << "*****************\n\n";
    ss << setw(w) << " ";
    
    for (int i = 0; i < numNodes; i++) {
        ss << setw(w) << char('A' + i);
    }
    ss << endl << endl;
    
    for (int i = 0; i < numNodes; i++) {
        ss << setw(w) << char('A' + i);
        for (int j = 0; j < numNodes; j++) {
            ss << setw(w) << adjMatrix[i][j];
        }
        ss << endl << endl;
    }
    
    return ss.str();
}



//Prints the contents of the edge array
string Graph::printArray() {
    stringstream ss;
    
    ss << "Edge Array:\n";
    ss << "***********\n\n";
    
    for (int i = 0; i < numEdges; i++) {
        ss << edgeArr[i].toString() << endl;
    }
    
    return ss.str();
}



//Prints the Euler Tour of the graph.
string Graph::printTour() {
    stringstream ss;
    
    ss << "EULER TOUR:  ";
    for (int i = 0; i < eulerTour.size(); i++) {
        ss << char('A' + eulerTour[i]) << "  ";
    }
    ss << endl << endl;
    
    return ss.str();
}



//Prints the cycles contained in the graph
string Graph::printCycle() {
    stringstream ss;
    
    for (int i = 0; i < cyclePath.size(); i++) {
        ss << cyclePath[i] << "   ";
    }
    ss << endl;
    
    return ss.str();
}