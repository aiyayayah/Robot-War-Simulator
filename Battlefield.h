#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <fstream>
#include <vector>
#include "RobotList.h"
#include "Queue.h"

class Battlefield
{
private:
    char **battlefield; // 2D array to represent the battlefield grid
    int m, n;           // Number of rows (m) and columns (n) in the battlefield
    RobotList robots;   // List to store the robots present on the battlefield
    Queue deadRobots;   // Queue to store dead robots

public:
    Battlefield(int rows, int cols);                       // Constructor to initialize the battlefield with the specified number of rows and columns
    ~Battlefield();                                        // Destructor to free the dynamically allocated memory for the battlefield
    void display(ofstream &outfile);                       // Function to display the current state of the battlefield
    void placeRobot(Robot *robot, int x, int y);           // Function to place a robot on the battlefield at the specified position
    void clearPosition(int x, int y);                      // Function to clear the position at the specified coordinates on the battlefield
    bool isPositionValid(int x, int y);                    // Function to check if a given position is valid within the battlefield boundaries
    bool isPositionOccupied(int x, int y);                 // Function to check if a given position on the battlefield is occupied by a robot
    void updatePosition(Robot *robot, int newX, int newY); // Function to update the position of a robot on the battlefield
    int getRows();                                         // Function to get the number of rows in the battlefield
    int getCols();                                         // Function to get the number of columns in the battlefield
    Robot *getRobotAtPosition(int x, int y);               // Function to get the robot present at the specified position on the battlefield
    RobotList &getRobotList();                             // Function to get the list of robots present on the battlefield
    Queue &getDeadRobotsQueue();                           // Function to get the queue of dead robots
    string reenterRobot(Robot *robot);                     // Method to place robot back on the battlefield
    void placeFireMark(int x, int y);                      // Function to place a fire mark at the specified position
    void drawLine(int x1, int y1, int x2, int y2);         // Function to draw a line on the battlefield between two points
    void clearFireMarks();                                 // Function to clear all fire marks from the battlefield
    void clearLineMarks();                                 // Function to clear all line marks from the battlefield
};

#endif
