/**********|**********|**********|
Program: Simulation.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Battlefield.h"
#include "UpgradeList.h"

class Simulation
{
private:
    Battlefield *battlefield;                              // Pointer to the battlefield object
    int steps;                                             // Number of simulation steps
    UpgradeList upgradeList;                               // Custom linked list for robots marked for upgrade
    ofstream outfile;                                      // Output file stream
    void addRobot(string type, string name, int x, int y); // Function to add a robot to the battlefield
    void processUpgrades();                                // Function to process all upgrades
    int countRobots();                                     // Function to count the number of robots in the RobotList

public:
    Simulation(const string &outputFileName); // Constructor to initialize the simulation with the output file name
    ~Simulation();                            // Destructor to clean up resources
    void readFile(const string &filename);    // Function to read simulation parameters from a file
    void run();                               // Function to run the simulation
    void printWelcomeMessage();
};

#endif
