/**********|**********|**********|
Program: RobotList.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#include "RobotList.h"

RobotList::Node::Node(Robot *robot) : data(robot), next(nullptr) {}

RobotList::RobotList() : head(nullptr) {}

RobotList::~RobotList()
{
    while (!isEmpty())
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

bool RobotList::isEmpty() const
{
    return head == nullptr; // Return true if the head pointer is nullptr
}

void RobotList::add(Robot *robot)
{
    Node *newNode = new Node(robot); // Create a new node with the provided robot
    if (!head)
    {
        head = newNode; // If the list is empty, set the new node as the head
    }
    else
    {
        Node *current = head;
        while (current->next)
        {
            current = current->next; // Traverse to the end of the list
        }
        current->next = newNode; // Set the new node as the next node of the last node
    }
}

void RobotList::remove(Robot *robot)
{
    if (isEmpty())
    {
        cout << "List is empty" << endl;
        return;
    }

    Node *toDelete = nullptr;
    Node *prev = nullptr;

    if (head->data == robot) // Check if the robot to be removed is at the head
    {
        toDelete = head;   // Temporarily store the head node
        head = head->next; // Move the head pointer to the next node
        delete toDelete;   // Delete the old head node
        return;
    }

    prev = head;
    toDelete = head->next;

    while (toDelete != nullptr && toDelete->data != robot) // Traverse the list to find the robot
    {
        prev = toDelete;
        toDelete = toDelete->next;
    }

    if (toDelete == nullptr) // Check if the robot was not found in the list
    {
        cout << "Robot not found in the list" << endl;
        return;
    }

    prev->next = toDelete->next; // Link the previous node to the next node
    delete toDelete;             // Delete the node containing the robot
}

RobotList::Node *RobotList::getHead() const
{
    return head; // Return a pointer to the head node
}
