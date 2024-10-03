/**********|**********|**********|
Program: UpgradeList.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#ifndef UPGRADELIST_H
#define UPGRADELIST_H

#include "Robot.h"

class UpgradeList
{
private:
    // Node structure to hold robot data and link to the next node
    struct Node
    {
        Robot *robot;   // Pointer to the robot object stored in this node
        Node *next;     // Pointer to the next node in the list
        Node(Robot *r); // Constructor to initialize the node with a robot object
    };
    Node *head; // Pointer to the head of the linked list
    Node *tail; // Pointer to the tail of the linked list

public:
    UpgradeList();          // Constructor to initialize an empty upgrade list
    ~UpgradeList();         // Destructor to clean up all nodes in the list
    void add(Robot *robot); // Function to add a new robot to the end of the list
    Robot *remove();        // Function to remove and return the robot from the front of the list
    bool isEmpty() const;   // Function to check if the list is empty
};

#endif
