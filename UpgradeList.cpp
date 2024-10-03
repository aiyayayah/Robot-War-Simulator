/**********|**********|**********|
Program: UpgradeList.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#include "UpgradeList.h"

UpgradeList::Node::Node(Robot *r) : robot(r), next(nullptr) {}

UpgradeList::UpgradeList() : head(nullptr), tail(nullptr) {}

UpgradeList::~UpgradeList()
{
    while (!isEmpty())
    {
        remove();
    }
}

void UpgradeList::add(Robot *robot)
{
    Node *newNode = new Node(robot); // Create a new node with the provided robot
    if (tail)
    {
        tail->next = newNode; // Link the new node to the end of the list
    }
    else
    {
        head = newNode; // If the list is empty, set the new node as the head
    }
    tail = newNode; // Set the new node as the tail of the list
}

Robot *UpgradeList::remove()
{
    if (!head) // Check if the list is empty
    {
        return nullptr; // Return nullptr if the list is empty
    }
    Node *temp = head;          // Temporarily store the current head node
    Robot *robot = head->robot; // Retrieve the robot object from the head node
    head = head->next;          // Move the head pointer to the next node
    if (!head)                  // If the list becomes empty after removing the head node
    {
        tail = nullptr; // Set the tail pointer to nullptr
    }
    delete temp;  // Delete the old head node
    return robot; // Return the robot object
}

bool UpgradeList::isEmpty() const
{
    return head == nullptr; // Return true if the head pointer is nullptr
}
