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
