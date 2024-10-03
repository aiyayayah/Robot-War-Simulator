/**********|**********|**********|
Program: RobotList.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#ifndef ROBOTLIST_H
#define ROBOTLIST_H

#include "Robot.h"

class RobotList
{
public:
    // Node structure to hold robot data and link to the next node
    struct Node
    {
        Node *next;         // Pointer to the next node in the list
        Robot *data;        // Pointer to the robot object stored in this node
        Node(Robot *robot); // Constructor to initialize the node with a robot object
    };

    RobotList(); // Constructor to initialize the linked list with no nodes
    ~RobotList();
    bool isEmpty() const;      // Function to check if the list is empty
    void add(Robot *robot);    // Function to add a new robot to the end of the list
    void remove(Robot *robot); // Function to remove a robot from the list
    Node *getHead() const;     // Function to get the head of the linked list

private:
    Node *head; // Pointer to the head of the linked list
};

#endif
