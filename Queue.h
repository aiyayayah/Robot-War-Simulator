/**********|**********|**********|
Program: Queue.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#ifndef QUEUE_H
#define QUEUE_H

#include "Robot.h"

class Queue
{
private:
    // Node structure to hold robot data and link to the next node
    struct Node
    {
        Node *next; // Pointer to the next node in the queue
        Robot *data; // Pointer to the robot object stored in this node
        Node(Robot *robot); // Constructor to initialize the node with a robot object
    };
    Node *front; // Pointer to the front node of the queue
    Node *rear;  // Pointer to the rear node of the queue

public:
    Queue(); // Constructor to initialize an empty queue
    ~Queue();
    void enqueue(Robot *robot); // Function to add a new robot to the end of the queue
    Robot *dequeue();           // Function to remove and return the robot from the front of the queue
    bool isEmpty();             // Function to check if the queue is empty
};

#endif
