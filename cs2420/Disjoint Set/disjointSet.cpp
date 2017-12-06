//
//  disjointSet.cpp
//  Disjoint Set
//
//  Created by Steven Proctor on 11/16/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "disjointSet.hpp"

Network::Network(int size) {
    for (int i = 0; i < size; i++) {
            network.push_back(-1);
    }
    
    numFinds = 0;
    numUnions = 0;
}


Network::~Network() {
    network.clear();
}


bool Network::unionH(int first, int second) {
    int group1 = find(first);
    int group2 = find(second);
    
    if (group1 == group2) {return false;}
    
    if (network[group1] > network[group2]) {
        network[group2] = min(network[group2], network[group1] - 1);
        network[group1] = group2;
    }
    
    else {
        network[group1] = min(network[group1], network[group2] - 1);
        network[group2] = group1;
    }
    
    numUnions++;
    
    return true;
}


int Network::find(int ID) {
    if (ID < 0 || ID > network.size()) {resolveInput(ID);}
    
    numFinds++;
    if (network[ID] < 0) {return ID;}
    
    return network[ID] = find(network[ID]);
}


void Network::resolveInput(int ID) {
    cout << ID << " is outside the acceptable range\n";
    cout << "Please enter a number from " << 0 << " to " << network.size() - 1 << endl;
    cin >> ID;
    cout << endl;
    find(ID);
}


bool Network::isConnected() {
    return (numUnions == network.size() - 1);
}


string Network::printNetwork() {
    stringstream ss;
    
    ss << "ID     Group ID" << endl;
    ss << "---------------" << endl;
    for (int i = 0; i < network.size(); i++) {
        ss << i << ":        " << network[i] << endl;
    }
    
    return ss.str();
}


string Network::printStatus() {
    stringstream ss;
    
    ss << "Number of successful unions: " << numUnions << endl;
    ss << "Number of finds performed: " << numFinds << endl;
    ss << endl;
    
    return ss.str();
}