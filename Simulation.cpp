/**********|**********|**********|
Program: Simulation.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#include "Simulation.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>

Simulation::Simulation(const string &outputFileName) : battlefield(nullptr), steps(0), outfile(outputFileName)
{
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open output file " << outputFileName << endl;
        exit(1);
    }
}

Simulation::~Simulation()
{
    delete battlefield; // Clean up the battlefield object
    outfile.close();    // Close the output file
}

void Simulation::readFile(const string &filename)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    int m, n, numRobots;
    // Read the size of the battlefield (m x n)
    if (getline(infile, line))
    {
        stringstream ss(line);
        string part;
        getline(ss, part, ':');
        ss >> m >> n;
        battlefield = new Battlefield(m, n); // Create a new battlefield object
    }
    // Read the number of simulation steps
    if (getline(infile, line))
    {
        stringstream ss(line);
        string part;
        getline(ss, part, ':');
        ss >> steps;
    }
    // Read the number of robots to be added to the battlefield
    if (getline(infile, line))
    {
        stringstream ss(line);
        string part;
        getline(ss, part, ':');
        ss >> numRobots;
    }
    // Add robots to the battlefield based on the provided parameters
    for (int i = 0; i < numRobots; ++i)
    {
        if (getline(infile, line))
        {
            stringstream ss(line);
            string type, name, posXStr, posYStr;
            ss >> type >> name >> posXStr >> posYStr;

            int posX, posY;
            // Determine the initial position of the robot (random or specified)
            if (posXStr == "random")
            {
                posX = rand() % battlefield->getRows();
            }
            else
            {
                posX = stoi(posXStr);
            }
            if (posYStr == "random")
            {
                posY = rand() % battlefield->getCols();
            }
            else
            {
                posY = stoi(posYStr);
            }

            addRobot(type, name, posX, posY); // Add the robot to the battlefield
        }
    }

    infile.close(); // Close the input file
}

void Simulation::addRobot(string type, string name, int x, int y)
{
    Robot *robot;
    // Create a robot object based on the given type
    if (type == "RoboCop")
    {
        robot = new RoboCop(type, name, x, y);
    }
    else if (type == "Terminator")
    {
        robot = new Terminator(type, name, x, y);
    }
    else if (type == "TerminatorRoboCop")
    {
        robot = new TerminatorRoboCop(type, name, x, y);
    }
    else if (type == "BlueThunder")
    {
        robot = new BlueThunder(type, name, x, y);
    }
    else if (type == "Madbot")
    {
        robot = new Madbot(type, name, x, y);
    }
    else if (type == "UltimateRobot")
    {
        robot = new UltimateRobot(type, name, x, y);
    }
    else if (type == "RoboTank")
    {
        robot = new RoboTank(type, name, x, y);
    }
    else
    {
        cerr << "Unknown robot type" << endl;
        return;
    }
    // Attempt to place the robot on the battlefield
    int maxAttempts = 100;
    int attempts = 0;
    while (attempts < maxAttempts)
    {
        if (!battlefield->isPositionOccupied(x, y))
        {
            battlefield->placeRobot(robot, x, y);
            return;
        }
        // Try a new random position if the current one is occupied
        x = rand() % battlefield->getRows();
        y = rand() % battlefield->getCols();
        attempts++;
    }
    // If a valid position is not found after maxAttempts, print an error message
    cerr << "Failed to find a valid position for robot: " << name << endl;
    delete robot; // Clean up the allocated memory
}

void Simulation::processUpgrades()
{
    while (!upgradeList.isEmpty())
    {
        Robot *robot = upgradeList.remove();
        string type = robot->getType();
        string name = robot->getName();
        int lives = robot->getLives();
        int x = robot->getX();
        int y = robot->getY();

        if (type == "BlueThunder")
        {
            // Create a new Madbot with the same attributes
            Robot *madbot = new Madbot("Madbot", name, x, y);
            madbot->setLives(lives);
            battlefield->clearPosition(x, y); // Remove BlueThunder from the battlefield and the list
            battlefield->getRobotList().remove(robot);
            delete robot;                          // Proper deletion with virtual destructor
            battlefield->placeRobot(madbot, x, y); // Place the new Madbot on the battlefield and at the end of the linked list
        }
        else if (type == "Madbot")
        {
            // Create a new RoboTank with the same attributes
            Robot *robotank = new RoboTank("RoboTank", name, x, y);
            robotank->setLives(lives);
            battlefield->clearPosition(x, y); // Remove Madbot from the battlefield and the list
            battlefield->getRobotList().remove(robot);
            delete robot;                            // Proper deletion with virtual destructor
            battlefield->placeRobot(robotank, x, y); // Place the new RoboTank on the battlefield and at the end of the linked list
        }
        else if (type == "RoboCop" || type == "Terminator")
        {
            // Create a new TerminatorRoboCop with the same attributes
            Robot *robocop = new TerminatorRoboCop("TerminatorRoboCop", name, x, y);
            robocop->setLives(lives);
            battlefield->clearPosition(x, y); // Remove RoboCop or Terminator from the battlefield and the list
            battlefield->getRobotList().remove(robot);
            delete robot;                           // Proper deletion with virtual destructor
            battlefield->placeRobot(robocop, x, y); // Place the new TerminatorRoboCop on the battlefield and at the end of the linked list
        }
        else if (type == "TerminatorRoboCop" || type == "RoboTank")
        {
            // Create a new UltimateRobot with the same attributes
            Robot *terminatorroboCop = new UltimateRobot("UltimateRobot", name, x, y);
            terminatorroboCop->setLives(lives);
            battlefield->clearPosition(x, y); // Remove TerminatorRoboCop or RoboTank from the battlefield and the list
            battlefield->getRobotList().remove(robot);
            delete robot;                                     // Proper deletion with virtual destructor
            battlefield->placeRobot(terminatorroboCop, x, y); // Place the new UltimateRobot on the battlefield and at the end of the linked list
        }
    }
}

int Simulation::countRobots()
{
    int count = 0;
    for (RobotList::Node *current = battlefield->getRobotList().getHead(); current != nullptr; current = current->next)
    {
        if (current->data->getLives() > 0)
        {
            count++;
        }
    }
    return count;
}

void Simulation::run()
{
    outfile << " _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl
            << "|                          |" << endl
            << "| 'R' = RoboCop            |" << endl
            << "| 'T' = Terminator         |" << endl
            << "| 'O' = TerminatorRoboCop  |" << endl
            << "| 'B' = BlueThunder        |" << endl
            << "| 'M' = Madbot             |" << endl
            << "| 'K' = RoboTank           |" << endl
            << "| 'U' = UltimateRobot      |" << endl
            << "| '!' = Fire Mark          |" << endl
            << "| '*' = Bresenham Line     |" << endl
            << "|_ _ _ _ _ _ _ _ _ _ _ _ _ |" << endl
            << endl;

    cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ " << endl
         << "|                          |" << endl
         << "| 'R' = RoboCop            |" << endl
         << "| 'T' = Terminator         |" << endl
         << "| 'O' = TerminatorRoboCop  |" << endl
         << "| 'B' = BlueThunder        |" << endl
         << "| 'M' = Madbot             |" << endl
         << "| 'K' = RoboTank           |" << endl
         << "| 'U' = UltimateRobot      |" << endl
         << "| '!' = Fire Mark          |" << endl
         << "| '*' = Bresenham Line     |" << endl
         << "|_ _ _ _ _ _ _ _ _ _ _ _ _ |" << endl
         << endl;

    // Display the initial positions of the robots on the battlefield
    outfile << "Robot's initial position :" << endl
            << endl;
    cout << "Robot's initial position :" << endl
         << endl;

    // Iterate through the list of robots and print their details
    for (RobotList::Node *current = battlefield->getRobotList().getHead(); current != nullptr; current = current->next)
    {
        Robot *robot = current->data;
        outfile << robot->getType() << " " << robot->getName() << " is at position (" << robot->getX() << ", " << robot->getY() << ")" << endl;
        cout << robot->getType() << " " << robot->getName() << " is at position (" << robot->getX() << ", " << robot->getY() << ")" << endl;
    }
    outfile << endl;
    cout << endl;

    // Display the battlefield with the actual positions of the robots
    battlefield->display(outfile);
    outfile << endl;
    cout << endl;

    // Run the simulation for the specified number of steps
    for (int step = 0; step < steps; ++step)
    {
        outfile << "Step " << step + 1 << ":" << endl;
        cout << "Step " << step + 1 << ":" << endl;

        processUpgrades(); // Process upgrades at the beginning of each step

        int numRobots = countRobots(); // Check the number of robots at the beginning of each step
        if (numRobots == 1 && battlefield->getDeadRobotsQueue().isEmpty() && upgradeList.isEmpty())
        {
            // If there is only one robot, declare it the winner and stop the simulation
            for (RobotList::Node *current = battlefield->getRobotList().getHead(); current != nullptr; current = current->next)
            {
                if (current->data->getLives() > 0)
                {
                    outfile << "Winner: " << current->data->getName() << " (" << current->data->getType() << ")" << endl;
                    cout << "Winner: " << current->data->getName() << " (" << current->data->getType() << ")" << endl;
                    return;
                }
            }
        }

        // Perform actions for each robot on the battlefield
        for (RobotList::Node *current = battlefield->getRobotList().getHead(); current != nullptr; current = current->next)
        {
            if (current->data->getLives() > 0)
            {
                current->data->action(battlefield, outfile); // Perform the action associated with the robot
                outfile << endl;
                cout << endl;

                // If the robot is marked for upgrade, add it to the upgrade queue
                if (current->data->isMarkedForUpgrade())
                {
                    upgradeList.add(current->data);
                }
            }
        }

        // Check the number of robots after actions are performed
        numRobots = countRobots();
        if (numRobots == 1 && battlefield->getDeadRobotsQueue().isEmpty() && upgradeList.isEmpty())
        {
            // If there is only one robot left, declare it the winner and stop the simulation
            for (RobotList::Node *current = battlefield->getRobotList().getHead(); current != nullptr; current = current->next)
            {
                if (current->data->getLives() > 0)
                {
                    outfile << "Winner: " << current->data->getName() << " (" << current->data->getType() << ")" << endl;
                    cout << "Winner: " << current->data->getName() << " (" << current->data->getType() << ")" << endl;
                    return;
                }
            }
        }

        // Reenter one dead robot at the end of the current step
        if (!battlefield->getDeadRobotsQueue().isEmpty())
        {
            Robot *robot = battlefield->getDeadRobotsQueue().dequeue();
            if (robot->getLives() > 0)
            {
                string reentryInfo = battlefield->reenterRobot(robot) + "\n";
                if (!reentryInfo.empty())
                {
                    outfile << reentryInfo;
                    cout << reentryInfo;
                }
            }
        }
    }
}

void Simulation::printWelcomeMessage()
{
    outfile << "        __   __  ___  _______ ___      ______   ______  ___      ___  _______      ___________ ______       \n";
    outfile << "       |\"  |/  \\|  \"|/\"     |\"  |    /\" _  \"\\ /    \" \\|\"  \\    /\"  |/\"     \"|    (\"     _   \")    \" \\      \n";
    outfile << "       |'  /    \\:  (: ______)|  |   (: ( \\___)/ ____  \\\\   \\  //   (: ______)     )__/  \\\\__// ____  \\     \n";
    outfile << "       |: /'        |\\/    | |:  |    \\/ \\   /  /    ) :)\\\\  \\/.    |\\/    |          \\\\_ / /  /    ) :)    \n";
    outfile << "        \\//  /'\\    |// ___)_ \\  |___ //  \\ (: (____/ //: \\.        |// ___)_         |.  |(: (____/ //     \n";
    outfile << "        /   /  \\\\   (:      \"( \\_|:  (:   _) \\        /|.  \\    /:  (:      \"|        \\:  | \\        /      \n";
    outfile << "       |___/    \\___|\\_______)\\_______)_______)\"_____/ |___|\\__/|___|\\_______)         \\__|  \\\"_____/       \n";
    outfile << "                                                                                                            \n";
    outfile << "                              _______    ______   _______    ______ ___________                             \n";
    outfile << "                             /\"      \\  /    \" \\ |   _  \"\\  /    \" (\"     _   \")                            \n";
    outfile << "                            |:        |// ____  \\(. |_)  :)// ____  )__/  \\\\__/                             \n";
    outfile << "                            |_____/   )  /    ) :):     \\//  /    ) :) \\\\_ /                                \n";
    outfile << "                             //      (: (____/ //(|  _  \\(: (____/ //  |.  |                                \n";
    outfile << "                            |:  __   \\\\        / |: |_)  :)        /   \\:  |                                \n";
    outfile << "                            |__|  \\___)\\\"_____/  (_______/ \\\"_____/     \\__|                                \n";
    outfile << "                                                                                                            \n";
    outfile << "      ________ __    ___      ___ ____  ____ ___           __ ___________ __     ______   _____  ___        \n";
    outfile << "     /\"       )\" \\  |\"  \\    /\"  (\"  _||_ \" |\"  |         /\"\"(\"     _   \")\" \\   /    \" \\ (\"   \\|\"  \\       \n";
    outfile << "    (:   \\___/||  |  \\   \\  //   |   (  ) : ||  |        /    )__/  \\\\__/||  | // ____  \\|.\\\\   \\    |      \n";
    outfile << "     \\___  \\  |:  |  /\\\\  \\/.    (:  |  | . ):  |       /' /\\  \\ \\\\_ /   |:  |/  /    ) :): \\.   \\\\  |      \n";
    outfile << "      __/  \\\\ |.  | |: \\.        |\\\\ \\__/ // \\  |___   //  __'  \\|.  |   |.  (: (____/ //|.  \\    \\. |      \n";
    outfile << "     /\" \\   :)/\\  |\\|.  \\    /:  |/\\\\ __ //\\( \\_|:  \\ /   /  \\\\  \\:  |   /\\  |\\        / |    \\    \\ |      \n";
    outfile << "    (_______/(__\\_|_)___|\\__/|___(__________)\\_______|___/    \\___)__|  (__\\_|_)\"_____/   \\___|\\____\\)      \n";
    outfile << endl
            << endl;
}

int main()
{
    srand(time(0)); // Seed the random number generator

    Simulation simulation("output3.txt");   // Create a Simulation object with the output file name
    simulation.readFile("battlefield.txt"); // Read simulation parameters from a file
    simulation.printWelcomeMessage();
    simulation.run(); // Run the simulation

    return 0;
}
