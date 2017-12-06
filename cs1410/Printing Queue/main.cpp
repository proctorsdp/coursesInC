//
//  main.cpp
//  Printing Queue
//
//  Created by Steven Proctor on 4/13/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

//Struct of a PrintJob
class PrintJob{
public:
    string fileName;
    int numPages;
    PrintJob * next;
};

//LinkList class, or print Queue
class PrintQueue : public PrintJob {
public:
    
    //Constructor
    PrintQueue() {
        head = 0;
        tail = 0;
    }
    
    //Inserts a new print job according to size
    void enQueue(string file, int pages) {
        head = recursiveInsert(head, file, pages);
    }
    
    //Empties the Print Queue
    void deQueue(){
        if (empty()) { cout << "PRINT QUEUE EMPTY\n\n"; return; }
        string file;
        int pages;
        file = head->fileName;
        pages = head->numPages;
        this->deleteFront();
        print(file, pages);
    }
    
    //Checks to see if queue is empty
    bool empty() {
        if (head == 0) return true;
        else return false;
    }
    
    //Outputs the current job being printed
    void print(string file, int pages) {
        cout << "Printing: \"" << file << "\"" << endl;
        cout << "Pages: " << pages << endl;
        cout << endl;
        if (empty()) { cout << "PRINT QUEUE EMPTY\n\n"; }
    }
    
private:
    
    //Pointers to head and tail of PrintJob
    PrintJob * head;
    PrintJob * tail;
    
    //Recursive function to find correct location to insert printjob
    PrintJob * recursiveInsert(PrintJob * head, string file, int pages) {
        if (!head || head->numPages > pages){
            head = insert(head, file, pages);
        }
        else{
            head->next = recursiveInsert(head->next, file, pages);
        }
        return head;
    }
    
    //Creates a new printjob and inserts it into linklist
    PrintJob * insert(PrintJob * head, string file, int pages) {
        PrintJob * newPrint = new PrintJob;
        newPrint->fileName = file;
        newPrint->numPages = pages;
        newPrint->next = head;
        if (!this->tail) this->tail = newPrint;
        if (!this->head) this->head = newPrint;
        head = newPrint;
        if (!head->next) tail=head;
        return head;
    }
    
    //Sets head to the next item in the linklist
    void deleteFront() {
        head = deleted(head);
    }
    
    //Deletes the front, or dequeued item
    PrintJob * deleted(PrintJob * head) {
        if (head == 0) return head;
        PrintJob * tempnode = head;
        head = head->next;
        delete tempnode;
        if (!head) tail = 0;
        return head;
    }
    
};


int main() {
    
    PrintQueue print;
    
    //Fill Queue with random print jobs
    print.enQueue("Lecture Notes", 3);
    print.enQueue("Scholarly Article", 10);
    print.enQueue("Paystub", 1);
    print.enQueue("Lab Report", 5);
    print.enQueue("Lord of The Rings", 753);
    print.enQueue("W-2 Form", 1);
    print.enQueue("Hotel Reservation", 2);
    print.enQueue("Technical Proposal", 20);
    print.enQueue("Instruction Manual", 8);
    print.enQueue("Hitchhiker's Guide to the Galaxy", 42);
    
    //Print entire Queue
    while(!print.empty()) {
        print.deQueue();
    }
    
    return 0;
}