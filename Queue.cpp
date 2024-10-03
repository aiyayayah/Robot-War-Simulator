/**********|**********|**********|
Program: Queue.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#include "Queue.h"

Queue::Node::Node(Robot *robot) : data(robot), next(nullptr) {}

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

void Queue::enqueue(Robot *robot)
{
    Node *newNode = new Node(robot); // Create a new node with the provided robot
    if (rear)
    {
        rear->next = newNode; // Link the new node to the end of the queue
    }
    else
    {
        front = newNode; // If the queue is empty, set the new node as the front
    }
    rear = newNode; // Set the new node as the rear of the queue
}

Robot *Queue::dequeue()
{
    if (!front) // Check if the queue is empty
    {
        return nullptr; // Return nullptr if the queue is empty
    }
    Node *temp = front; // Temporarily store the front node
    front = front->next; // Move the front pointer to the next node
    if (!front)          // If the queue becomes empty after dequeueing
    {
        rear = nullptr; // Set the rear pointer to nullptr
    }
    Robot *robot = temp->data;// Retrieve the robot object from the dequeued node
        delete temp;               // Delete the dequeued node
        return robot;              // Return the robot object
}

bool Queue::isEmpty()
{
    return front == nullptr; // Return true if the front pointer is nullptr
}
