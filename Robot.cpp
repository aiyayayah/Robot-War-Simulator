/**********|**********|**********|
Program: Robot.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#include "Robot.h"
#include "Battlefield.h"

Robot::Robot() : type(""), name(""), posX(0), posY(0), kills(0), lives(3), upgradeFlag(false) {}
Robot::Robot(const string &in_type, const string &in_name, int in_posX, int in_posY)
    : type(in_type), name(in_name), posX(in_posX), posY(in_posY), kills(0), lives(3), upgradeFlag(false) {}
Robot::~Robot() {}

string Robot::getType() { return type; }
string Robot::getName() { return name; }
int Robot::getX() { return posX; }
int Robot::getY() { return posY; }
bool Robot::isMarkedForUpgrade() const { return upgradeFlag; }
void Robot::markForUpgrade() { upgradeFlag = true; }
void Robot::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}
void Robot::incrementKills() { kills++; }
int Robot::getKills() { return kills; }
void Robot::decrementLives() { lives--; }
void Robot::setLives(int newLives) { lives = newLives; }
int Robot::getLives() { return lives; }

MovingRobot::MovingRobot(string type, string name, int x, int y) : Robot(type, name, x, y) {}
ShootingRobot::ShootingRobot(string type, string name, int x, int y) : Robot(type, name, x, y) {}
SeeingRobot::SeeingRobot(string type, string name, int x, int y) : Robot(type, name, x, y) {}
SteppingRobot::SteppingRobot(string type, string name, int x, int y) : Robot(type, name, x, y) {}

TerminatorRoboCop::TerminatorRoboCop(string type, string name, int x, int y)
    : Robot(type, name, x, y), SeeingRobot(type, name, x, y), MovingRobot(type, name, x, y), ShootingRobot(type, name, x, y), SteppingRobot(type, name, x, y) {}
TerminatorRoboCop::~TerminatorRoboCop() {}

void TerminatorRoboCop::setPosX(int newX) { posX = newX; }
void TerminatorRoboCop::setPosY(int newY) { posY = newY; }

void TerminatorRoboCop::look(Battlefield *battlefield, ofstream &outfile)
{
    int rows = battlefield->getRows();
    int cols = battlefield->getCols();
    outfile << "TerminatorRoboCop " << getName() << " is seeing at (" << getX() << ", " << getY() << ")" << endl;
    cout << "TerminatorRoboCop " << getName() << " is seeing at (" << getX() << ", " << getY() << ")" << endl;

    // Iterate over each cell in the 3x3 range centered around the robot
    for (int i = getX() - 1; i <= getX() + 1; ++i)
    {
        for (int j = getY() - 1; j <= getY() + 1; ++j)
        {
            // Check if the position is valid
            if (battlefield->isPositionValid(i, j) && (i != getX() || j != getY()))
            {
                // Check if the position is occupied by a robot
                if (battlefield->isPositionOccupied(i, j))
                {
                    Robot *robot = battlefield->getRobotAtPosition(i, j);
                    if (robot)
                    {
                        outfile << "TerminatorRoboCop " << getName() << " detected a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                        cout << "TerminatorRoboCop " << getName() << " detected a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    }
                }
            }
        }
    }
}
void TerminatorRoboCop::move(Battlefield *battlefield, ofstream &outfile)
{
    const int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    const int maxAttempts = 20; // Maximum number of attempts to find a valid move
    int attempts = 0;

    while (attempts < maxAttempts)
    {
        int randDirection = rand() % 8; // Generate a random direction index
        int newX = getX() + directions[randDirection][0];
        int newY = getY() + directions[randDirection][1];

        if (battlefield->isPositionValid(newX, newY) && !battlefield->isPositionOccupied(newX, newY))
        {
            // Update the position of the robot on the battlefield
            outfile << "TerminatorRoboCop " << getName() << " is move to position (" << newX << " , " << newY << ")" << endl;
            cout << "TerminatorRoboCop " << getName() << " is move to position (" << newX << " , " << newY << ")" << endl;
            battlefield->updatePosition(this, newX, newY);
            return;
        }

        attempts++;
    }

    // If no valid move is found after maximum attempts, inform that the robot stays in place
    outfile << getName() << " did not find a valid move and stays in place." << endl;
    cout << getName() << " did not find a valid move and stays in place." << endl;
}

void TerminatorRoboCop::fire(Battlefield *battlefield, ofstream &outfile)
{
    int battlefieldRows = battlefield->getRows();
    int battlefieldCols = battlefield->getCols();

    int currentX = getX();
    int currentY = getY();

    for (int i = 0; i < 3; ++i)
    {
        int dx, dy;
        int targetX, targetY;
        do
        {
            dx = rand() % 21 - 10; // -10 to 10
            dy = rand() % 21 - 10; // -10 to 10

            targetX = currentX + dx;
            targetY = currentY + dy;
        } while (!(targetX >= 0 && targetX < battlefieldRows && targetY >= 0 && targetY < battlefieldCols &&
                   !(targetX == currentX && targetY == currentY) && (abs(dx) + abs(dy)) <= 10));

        // Check if the target position is occupied by another robot
        if (battlefield->isPositionOccupied(targetX, targetY))
        {
            Robot *targetRobot = battlefield->getRobotAtPosition(targetX, targetY);
            if (targetRobot)
            {
                battlefield->clearPosition(targetX, targetY);
                targetRobot->decrementLives();
                outfile << "TerminatorRoboCop " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                cout << "TerminatorRoboCop " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                incrementKills();

                if (targetRobot->getLives() > 0)
                {
                    battlefield->getDeadRobotsQueue().enqueue(targetRobot);
                    battlefield->getRobotList().remove(targetRobot);
                }
                else
                    battlefield->getRobotList().remove(targetRobot);

                if (getKills() == 3)
                {
                    markForUpgrade();
                    outfile << "TerminatorRoboCop " << getName() << " has been marked for upgrade to UltimateRobot." << endl;
                    cout << "TerminatorRoboCop " << getName() << " has been marked for upgrade to UltimateRobot." << endl;
                }
            }
        }

        battlefield->clearPosition(targetX, targetY);
        battlefield->placeFireMark(targetX, targetY);
        outfile << "Fire shot landed at (" << targetX << ", " << targetY << ")." << endl;
        cout << "Fire shot landed at (" << targetX << ", " << targetY << ")." << endl;

        // Draw a line from the roboy to the fire mark
        battlefield->drawLine(currentX, currentY, targetX, targetY);
    }
}
void TerminatorRoboCop::step(Battlefield *battlefield, ofstream &outfile)
{

    int currentX = getX();
    int currentY = getY();
    bool foundTarget = false;

    // Check adjacent positions
    for (int i = currentX - 1; i <= currentX + 1; ++i)
    {
        for (int j = currentY - 1; j <= currentY + 1; ++j)
        {
            // Skip the current position
            if (i == currentX && j == currentY)
                continue;

            // Check if the position is valid and occupied by a robot
            if (battlefield->isPositionValid(i, j) && battlefield->isPositionOccupied(i, j))
            {
                // Get the robot at the position
                Robot *robot = battlefield->getRobotAtPosition(i, j);
                if (robot)
                {
                    // Kill the robot
                    battlefield->clearPosition(i, j);
                    robot->decrementLives();
                    outfile << "TerminatorRoboCop " << getName() << " killed a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    cout << "TerminatorRoboCop " << getName() << " killed a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    incrementKills();

                    if (robot->getLives() > 0)
                    {
                        battlefield->getDeadRobotsQueue().enqueue(robot);
                        battlefield->getRobotList().remove(robot);
                    }
                    else
                    {
                        battlefield->getRobotList().remove(robot);
                    }

                    // Move to the position where the robot was killed
                    battlefield->updatePosition(this, i, j);
                    setPosX(i);
                    setPosY(j);
                    foundTarget = true;

                    if (getKills() == 3)
                    {
                        markForUpgrade();
                        outfile << "TerminatorRoboCop " << getName() << " has been marked for upgrade to UltimateRobot." << endl;
                        cout << "TerminatorRoboCop " << getName() << " has been marked for upgrade to UltimateRobot." << endl;
                    }
                    return; // Exit after one kill and movement
                }
            }
        }
    }

    // If no robots were killed, the robot stays in place
    if (!foundTarget)
    {
        outfile << getName() << " did not find any robots to kill and stays in place." << endl;
        cout << getName() << " did not find any robots to kill and stays in place." << endl;
    }
}
void TerminatorRoboCop::action(Battlefield *battlefield, ofstream &outfile)
{
    // Clear fire marks before performing the action
    battlefield->clearFireMarks();
    battlefield->clearLineMarks();

    // Display the number of kills and lives before performing the action
    outfile << "TerminatorRoboCop " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    cout << "TerminatorRoboCop " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    // Get the current position of the robot
    int currentX = getX();
    int currentY = getY();
    look(battlefield, outfile);
    move(battlefield, outfile);
    fire(battlefield, outfile);
    step(battlefield, outfile);

    // Display the updated battlefield after all actions
    outfile << "Position Robot After Doing Action" << endl;
    cout << "Position Robot After Doing Action" << endl;
    battlefield->display(outfile);
    outfile << "____________________________________" << endl;
    cout << "____________________________________" << endl;
}
char TerminatorRoboCop::getSymbol() { return 'O'; }

RoboCop::RoboCop(string type, string name, int x, int y)
    : Robot(type, name, x, y), SeeingRobot(type, name, x, y), MovingRobot(type, name, x, y), ShootingRobot(type, name, x, y) {}
RoboCop::~RoboCop() {}
void RoboCop::look(Battlefield *battlefield, ofstream &outfile)
{
    int rows = battlefield->getRows(); // Get the number of rows in the battlefield
    int cols = battlefield->getCols(); // Get the number of columns in the battlefield
    outfile << "RoboCop " << getName() << " is seeing at (" << getX() << ", " << getY() << ")" << endl;
    cout << "RoboCop " << getName() << " is seeing at (" << getX() << ", " << getY() << ")" << endl;

    // Iterate over each cell in the 3x3 range centered around the robot
    for (int i = getX() - 1; i <= getX() + 1; ++i)
    {
        for (int j = getY() - 1; j <= getY() + 1; ++j)
        {
            // Check if the position is valid
            if (battlefield->isPositionValid(i, j) && (i != getX() || j != getY()))
            {
                // Check if the position is occupied by a robot
                if (battlefield->isPositionOccupied(i, j))
                {
                    Robot *robot = battlefield->getRobotAtPosition(i, j);
                    if (robot)
                    {
                        outfile << "RoboCop " << getName() << " detected a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                        cout << "RoboCop " << getName() << " detected a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    }
                }
            }
        }
    }
}
void RoboCop::move(Battlefield *battlefield, ofstream &outfile)
{
    const int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; // Possible movement directions
    const int maxAttempts = 20;                                                                          // Maximum number of attempts to find a valid move
    int attempts = 0;

    while (attempts < maxAttempts)
    {
        int randDirection = rand() % 8; // Generate a random direction index
        int newX = getX() + directions[randDirection][0];
        int newY = getY() + directions[randDirection][1];

        if (battlefield->isPositionValid(newX, newY) && !battlefield->isPositionOccupied(newX, newY))
        {
            // Update the position of the robot on the battlefield
            outfile << "RoboCop " << getName() << " is moving to position (" << newX << " , " << newY << ")" << endl;
            cout << "RoboCop " << getName() << " is moving to position (" << newX << " , " << newY << ")" << endl;
            battlefield->updatePosition(this, newX, newY);
            return;
        }

        attempts++;
    }

    // If no valid move is found after maximum attempts, inform that the robot stays in place
    outfile << getName() << " did not find a valid move and stays in place." << endl;
    cout << getName() << " did not find a valid move and stays in place." << endl;
}
void RoboCop::fire(Battlefield *battlefield, ofstream &outfile)
{
    int battlefieldRows = battlefield->getRows(); // Get the number of rows in the battlefield
    int battlefieldCols = battlefield->getCols(); // Get the number of columns in the battlefield

    int currentX = getX(); // Get the current X position of the RoboCop
    int currentY = getY(); // Get the current Y position of the RoboCop

    for (int i = 0; i < 3; ++i) // Fire three shots
    {
        int dx, dy;
        int targetX, targetY;
        do
        {
            dx = rand() % 21 - 10; // Random X offset between -10 and 10
            dy = rand() % 21 - 10; // Random Y offset between -10 and 10

            targetX = currentX + dx;
            targetY = currentY + dy;
        } while (!(targetX >= 0 && targetX < battlefieldRows && targetY >= 0 && targetY < battlefieldCols &&
                   !(targetX == currentX && targetY == currentY) && (abs(dx) + abs(dy)) <= 10));

        // Check if the target position is occupied by another robot
        if (battlefield->isPositionOccupied(targetX, targetY))
        {
            Robot *targetRobot = battlefield->getRobotAtPosition(targetX, targetY);
            if (targetRobot)
            {
                battlefield->clearPosition(targetX, targetY);
                targetRobot->decrementLives();
                outfile << "RoboCop " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                cout << "RoboCop " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                incrementKills();

                if (targetRobot->getLives() > 0)
                {
                    battlefield->getDeadRobotsQueue().enqueue(targetRobot);
                    battlefield->getRobotList().remove(targetRobot);
                }
                else
                {
                    battlefield->getRobotList().remove(targetRobot);
                }

                if (getKills() == 3)
                {
                    markForUpgrade();
                    outfile << "RoboCop " << getName() << " has been marked for upgrade to TerminatorRoboCop." << endl;
                    cout << "RoboCop " << getName() << " has been marked for upgrade to TerminatorRoboCop." << endl;
                }
            }
        }

        battlefield->clearPosition(targetX, targetY); // Clear the target position on the battlefield
        battlefield->placeFireMark(targetX, targetY); // Place a fire mark at the target position
        outfile << "Fire shot landed at (" << targetX << ", " << targetY << ")." << endl;
        cout << "Fire shot landed at (" << targetX << ", " << targetY << ")." << endl;

        // Draw a line from the RoboCop to the fire mark
        battlefield->drawLine(currentX, currentY, targetX, targetY);
    }
}
void RoboCop::action(Battlefield *battlefield, ofstream &outfile)
{
    // Clear fire marks before performing the action
    battlefield->clearFireMarks();
    battlefield->clearLineMarks();

    // Display the number of kills and lives before performing the action
    outfile << "RoboCop " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    cout << "RoboCop " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    // Get the current position of the robot
    int currentX = getX();
    int currentY = getY();
    look(battlefield, outfile); // Perform the look action
    move(battlefield, outfile); // Perform the move action
    fire(battlefield, outfile); // Perform the fire action

    // Display the updated battlefield after all actions
    outfile << "Position Robot After Doing Action" << endl;
    cout << "Position Robot After Doing Action" << endl;
    battlefield->display(outfile);
    outfile << "____________________________________" << endl;
    cout << "____________________________________" << endl;
}
char RoboCop::getSymbol() { return 'R'; }

Terminator::Terminator(string type, string name, int x, int y)
    : Robot(type, name, x, y), SeeingRobot(type, name, x, y), MovingRobot(type, name, x, y), SteppingRobot(type, name, x, y) {}
Terminator::~Terminator() {}
void Terminator::setPosX(int newX) { posX = newX; }
void Terminator::setPosY(int newY) { posY = newY; }
void Terminator::look(Battlefield *battlefield, ofstream &outfile)
{
    int rows = battlefield->getRows();
    int cols = battlefield->getCols();
    outfile << "Terminator " << getName() << " is seeing at (" << getX() << ", " << getY() << ")" << endl;
    cout << "Terminator " << getName() << " is seeing at (" << getX() << ", " << getY() << ")" << endl;

    // Iterate over each cell in the 3x3 range centered around the robot
    for (int i = getX() - 1; i <= getX() + 1; ++i)
    {
        for (int j = getY() - 1; j <= getY() + 1; ++j)
        {
            // Check if the position is valid
            if (battlefield->isPositionValid(i, j) && (i != getX() || j != getY()))
            {
                // Check if the position is occupied by a robot
                if (battlefield->isPositionOccupied(i, j))
                {
                    Robot *robot = battlefield->getRobotAtPosition(i, j);
                    if (robot)
                    {
                        outfile << "Terminator " << getName() << " detected a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                        cout << "Terminator " << getName() << " detected a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    }
                }
            }
        }
    }
}
void Terminator::move(Battlefield *battlefield, ofstream &outfile)
{
    const int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    const int maxAttempts = 20; // Maximum number of attempts to find a valid move
    int attempts = 0;

    while (attempts < maxAttempts)
    {
        int randDirection = rand() % 8; // Generate a random direction index
        int newX = getX() + directions[randDirection][0];
        int newY = getY() + directions[randDirection][1];

        if (battlefield->isPositionValid(newX, newY) && !battlefield->isPositionOccupied(newX, newY))
        {
            // Update the position of the robot on the battlefield
            outfile << "Terminator " << getName() << " is moving to position (" << newX << " , " << newY << ")" << endl;
            cout << "Terminator " << getName() << " is moving to position (" << newX << " , " << newY << ")" << endl;
            battlefield->updatePosition(this, newX, newY);
            return;
        }

        attempts++;
    }

    // If no valid move is found after maximum attempts, inform that the robot stays in place
    outfile << getName() << " did not find a valid move and stays in place." << endl;
    cout << getName() << " did not find a valid move and stays in place." << endl;
}

void Terminator::step(Battlefield *battlefield, ofstream &outfile)
{
    int currentX = getX();
    int currentY = getY();
    bool foundTarget = false;

    // Check adjacent positions
    for (int i = currentX - 1; i <= currentX + 1; ++i)
    {
        for (int j = currentY - 1; j <= currentY + 1; ++j)
        {
            // Skip the current position
            if (i == currentX && j == currentY)
                continue;

            // Check if the position is valid and occupied by a robot
            if (battlefield->isPositionValid(i, j) && battlefield->isPositionOccupied(i, j))
            {
                // Get the robot at the position
                Robot *robot = battlefield->getRobotAtPosition(i, j);
                if (robot)
                {
                    // Kill the robot
                    battlefield->clearPosition(i, j);
                    robot->decrementLives();
                    outfile << "Terminator " << getName() << " killed a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    cout << "Terminator " << getName() << " killed a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    incrementKills();

                    if (robot->getLives() > 0)
                    {
                        battlefield->getDeadRobotsQueue().enqueue(robot);
                        battlefield->getRobotList().remove(robot);
                    }
                    else
                    {
                        battlefield->getRobotList().remove(robot);
                    }

                    // Move to the position where the robot was killed
                    battlefield->updatePosition(this, i, j);
                    setPosX(i);
                    setPosY(j);
                    foundTarget = true;

                    if (getKills() == 3)
                    {
                        markForUpgrade();
                        outfile << "Terminator " << getName() << " has been marked for upgrade to TerminatorRoboCop." << endl;
                        cout << "Terminator " << getName() << " has been marked for upgrade to TerminatorRoboCop." << endl;
                    }
                    return; // Exit after one kill and movement
                }
            }
        }
    }

    // If no robots were killed, the robot stays in place
    if (!foundTarget)
    {
        outfile << getName() << " did not find any robots to kill and stays in place." << endl;
        cout << getName() << " did not find any robots to kill and stays in place." << endl;
    }
}
void Terminator::action(Battlefield *battlefield, ofstream &outfile)
{
    outfile << "Terminator " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    cout << "Terminator " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    look(battlefield, outfile);
    move(battlefield, outfile);
    step(battlefield, outfile);

    outfile << "Position Robot After Doing Action" << endl;
    cout << "Position Robot After Doing Action" << endl;
    battlefield->display(outfile);
    outfile << "____________________________________" << endl;
    cout << "____________________________________" << endl;
}
char Terminator::getSymbol() { return 'T'; }

BlueThunder::BlueThunder(string type, string name, int x, int y)
    : Robot(type, name, x, y), ShootingRobot(type, name, x, y) {}
BlueThunder::~BlueThunder() {}
void BlueThunder::fire(Battlefield *battlefield, ofstream &outfile) {
    int battlefieldRows = battlefield->getRows();
    int battlefieldCols = battlefield->getCols();

    int currentX = getX();
    int currentY = getY();

    int directions[8][2] = {
        {-1, 0}, // up
        {-1, 1}, // up-right
        {0, 1},  // right
        {1, 1},  // down-right
        {1, 0},  // down
        {1, -1}, // down-left
        {0, -1}, // left
        {-1, -1} // up-left
    };

    bool validTargetFound = false;

    // Loop through all directions to find a valid target
    for (int i = 0; i < 8; ++i) 
    {
        int dx = directions[directionIndex][0];
        int dy = directions[directionIndex][1];
        int targetX = currentX + dx;
        int targetY = currentY + dy;

        // Ensure the target position is within the battlefield bounds
        if (targetX >= 0 && targetX < battlefieldRows && targetY >= 0 && targetY < battlefieldCols) 
        {
            // Check if the target position is occupied by another robot
            if (battlefield->isPositionOccupied(targetX, targetY)) 
            {
                Robot *targetRobot = battlefield->getRobotAtPosition(targetX, targetY);
                if (targetRobot) 
                {
                    battlefield->clearPosition(targetX, targetY);
                    targetRobot->decrementLives();
                    outfile << "BlueThunder " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    cout << "BlueThunder " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    incrementKills();

                    if (targetRobot->getLives() > 0) 
                    {
                        battlefield->getDeadRobotsQueue().enqueue(targetRobot);
                        battlefield->getRobotList().remove(targetRobot);
                    } 
                    else 
                    {
                        battlefield->getRobotList().remove(targetRobot);
                    }

                    if (getKills() == 3) 
                    {
                        markForUpgrade();
                        outfile << "BlueThunder " << getName() << " has been upgraded to Madbot." << endl;
                        cout << "BlueThunder " << getName() << " has been upgraded to Madbot." << endl;
                    }
                    // Place a fire mark at the destroyed robot's position
                    battlefield->placeFireMark(targetX, targetY);

                }
            } 
            else 
            {  // Place a fire mark at the target position if no robot is there
                battlefield->placeFireMark(targetX, targetY);
                outfile << "Fire at (" << targetX << ", " << targetY << ")." << endl;
                cout << "Fire at (" << targetX << ", " << targetY << ")." << endl;
            }
            
            validTargetFound = true;
            break;
        }
        // Move to the next direction in clockwise order
        directionIndex = (directionIndex + 1) % 8;
    }

    // Move to the next direction for the next fire call
    directionIndex = (directionIndex + 1) % 8;
}
void BlueThunder::action(Battlefield *battlefield, ofstream &outfile)
{
    // Clear fire marks before performing the action
    battlefield->clearFireMarks();
    battlefield->clearLineMarks();

    // Display the number of kills and lives before performing the action
    outfile << "BlueThunder " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    cout << "BlueThunder " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    // Get the current position of the robot
    int currentX = getX();
    int currentY = getY();
    fire(battlefield, outfile);

    // Display the updated battlefield after all actions
    outfile << "Position Robot After Doing Action" << endl;
    cout << "Position Robot After Doing Action" << endl;
    battlefield->display(outfile);
    outfile << "____________________________________" << endl;
    cout << "____________________________________" << endl;
}

char BlueThunder::getSymbol() { return 'B'; }

Madbot::Madbot(string type, string name, int x, int y)
    : Robot(type, name, x, y), ShootingRobot(type, name, x, y) {}
Madbot::~Madbot() {}
void Madbot::fire(Battlefield *battlefield, ofstream &outfile)
{
    int battlefieldRows = battlefield->getRows();
    int battlefieldCols = battlefield->getCols();

    int currentX = getX();
    int currentY = getY();

    int directions[8][2] = {
        {0, 1},   // right
        {0, -1},  // left
        {1, 0},   // down
        {-1, 0},  // up
        {-1, -1}, // up-left
        {-1, 1},  // up-right
        {1, -1},  // down-left
        {1, 1}    // down-right
    };

    bool validTargetFound = false;

    while (!validTargetFound)
    {
        // Randomly select one of the 8 directions
        int directionIndex = rand() % 8;
        int dx = directions[directionIndex][0];
        int dy = directions[directionIndex][1];
        int targetX = currentX + dx;
        int targetY = currentY + dy;

        // Ensure the target position is within the battlefield bounds
        if (targetX >= 0 && targetX < battlefieldRows && targetY >= 0 && targetY < battlefieldCols)
        {
            // Check if the target position is occupied by another robot
            if (battlefield->isPositionOccupied(targetX, targetY))
            {
                Robot *targetRobot = battlefield->getRobotAtPosition(targetX, targetY);
                if (targetRobot)
                {
                    battlefield->clearPosition(targetX, targetY);
                    targetRobot->decrementLives();
                    outfile << "Madbot " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    cout << "Madbot " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    incrementKills();

                    // Remove the robot from the battlefield
                    battlefield->getRobotList().remove(targetRobot);

                     // If the destroyed robot still has lives, enqueue it in dead robots queue
                    if (targetRobot->getLives() > 0)
                    {
                        battlefield->getDeadRobotsQueue().enqueue(targetRobot);
                        battlefield->getRobotList().remove(targetRobot);
                    }

                    if (getKills() == 3)
                    {
                        markForUpgrade();
                        outfile << "Madbot " << getName() << " has been upgraded to RoboTank." << endl;
                        cout << "Madbot " << getName() << " has been upgraded to RoboTank." << endl;
                    }
                }
            }
            battlefield->clearPosition(targetX, targetY);
            // Place a fire mark at the target position
            battlefield->placeFireMark(targetX, targetY);
            outfile << "Fire at (" << targetX << ", " << targetY << ")." << endl;
            cout << "Fire at (" << targetX << ", " << targetY << ")." << endl;
            validTargetFound = true; // A valid target or empty position within bounds has been found
        }
        else
        {
            // If the target position is out of bounds, continue searching
            continue;
        }
    }
}
void Madbot::action(Battlefield *battlefield, ofstream &outfile)
{
    // Clear fire marks before performing the action
    battlefield->clearFireMarks();
    battlefield->clearLineMarks();

    // Display the number of kills and lives before performing the action
    outfile << "Madbot " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    cout << "Madbot " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    // Get the current position of the robot
    int currentX = getX();
    int currentY = getY();
    fire(battlefield, outfile);

    // Display the updated battlefield after all actions
    outfile << "Position Robot After Doing Action" << endl;
    cout << "Position Robot After Doing Action" << endl;
    battlefield->display(outfile);
    outfile << "____________________________________" << endl;
    cout << "____________________________________" << endl;
}
char Madbot::getSymbol() { return 'M'; }

UltimateRobot::UltimateRobot(string type, string name, int x, int y)
    : Robot(type, name, x, y), MovingRobot(type, name, x, y), ShootingRobot(type, name, x, y), SteppingRobot(type, name, x, y) {}
UltimateRobot::~UltimateRobot() {}

void UltimateRobot::setPosX(int newX) { posX = newX; }
void UltimateRobot::setPosY(int newY) { posY = newY; }

void UltimateRobot::move(Battlefield *battlefield, ofstream &outfile)
{
    const int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    const int maxAttempts = 20; // Maximum number of attempts to find a valid move
    int attempts = 0;

    while (attempts < maxAttempts)
    {
        int randDirection = rand() % 8; // Generate a random direction index
        int newX = getX() + directions[randDirection][0];
        int newY = getY() + directions[randDirection][1];

        if (battlefield->isPositionValid(newX, newY) && !battlefield->isPositionOccupied(newX, newY))
        {
            // Update the position of the robot on the battlefield
            outfile << "UltimateRobot " << getName() << " is moving to position (" << newX << " , " << newY << ")" << endl;
            cout << "UltimateRobot " << getName() << " is moving to position (" << newX << " , " << newY << ")" << endl;
            battlefield->updatePosition(this, newX, newY);
            return;
        }

        attempts++;
    }

    // If no valid move is found after maximum attempts, inform that the robot stays in place
    outfile << getName() << " did not find a valid move and stays in place." << endl;
    cout << getName() << " did not find a valid move and stays in place." << endl;
}

void UltimateRobot::fire(Battlefield *battlefield, ofstream &outfile)
{
    // get the number of row and columns in battlefield
    int battlefieldRows = battlefield->getRows();
    int battlefieldCols = battlefield->getCols();

    int currentX = getX(); // get the current position x of RoboTank
    int currentY = getY(); // get the current position y of RoboTank

    bool validTargetFound = false;
    // int targetX, targetY;
    while (!validTargetFound)
    {
        int targetX = rand() % battlefieldRows;
        int targetY = rand() % battlefieldCols;

        // Ensure the target position is within the battlefield bounds
        if (targetX >= 0 && targetX < battlefieldRows && targetY >= 0 && targetY < battlefieldCols)
        {
            // Check if the target position is occupied by another robot
            if (battlefield->isPositionOccupied(targetX, targetY))
            {
                Robot *targetRobot = battlefield->getRobotAtPosition(targetX, targetY);
                if (targetRobot && targetRobot != this) // // Ensure robot wont shoot back itself
                {
                    battlefield->clearPosition(targetX, targetY);
                    targetRobot->decrementLives();
                    outfile << "UltimateRobot " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    cout << "UltimateRobot " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    incrementKills();

                    if (targetRobot->getLives() > 0)
                    {
                        battlefield->getDeadRobotsQueue().enqueue(targetRobot);
                        battlefield->getRobotList().remove(targetRobot);
                    }
                    else
                    {
                        battlefield->getRobotList().remove(targetRobot);
                    }
                    

                }
            }
            battlefield->clearPosition(targetX, targetY);
            battlefield->placeFireMark(targetX, targetY);
            outfile << "Fire at (" << targetX << ", " << targetY << ")." << endl;
            cout << "Fire at (" << targetX << ", " << targetY << ")." << endl;
            battlefield->drawLine(currentX, currentY, targetX, targetY);
            validTargetFound = true; // A valid target or empty position within bounds has been found
        }
        else
        {
            // If the target position is out of bounds, continue searching
            continue;
        }
    }
}
void UltimateRobot::step(Battlefield *battlefield, ofstream &outfile)
{

    int currentX = getX();
    int currentY = getY();
    bool foundTarget = false;

    // Check adjacent positions
    for (int i = currentX - 1; i <= currentX + 1; ++i)
    {
        for (int j = currentY - 1; j <= currentY + 1; ++j)
        {
            // Skip the current position
            if (i == currentX && j == currentY)
                continue;

            // Check if the position is valid and occupied by a robot
            if (battlefield->isPositionValid(i, j) && battlefield->isPositionOccupied(i, j))
            {
                // Get the robot at the position
                Robot *robot = battlefield->getRobotAtPosition(i, j);
                if (robot)
                {
                    // Kill the robot
                    battlefield->clearPosition(i, j);
                    robot->decrementLives();
                    outfile << "UltimateRobot " << getName() << " killed a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    cout << "UltimateRobot " << getName() << " killed a robot named " << robot->getName() << " at (" << i << ", " << j << ")." << endl;
                    incrementKills();

                    if (robot->getLives() > 0)
                    {
                        battlefield->getDeadRobotsQueue().enqueue(robot);
                        battlefield->getRobotList().remove(robot);
                    }
                    else
                    {
                        battlefield->getRobotList().remove(robot);
                    }

                    // Move to the position where the robot was killed
                    battlefield->updatePosition(this, i, j);
                    setPosX(i);
                    setPosY(j);
                    foundTarget = true;

                    return; // Exit after one kill and movement
                }
            }
        }
    }

    // If no robots were killed, the robot stays in place
    if (!foundTarget)
    {
        outfile << getName() << " did not find any robots to kill and stays in place." << endl;
        cout << getName() << " did not find any robots to kill and stays in place." << endl;
    }
}
void UltimateRobot::action(Battlefield *battlefield, ofstream &outfile)
{
    // Clear fire marks before performing the action
    battlefield->clearFireMarks();
    battlefield->clearLineMarks();

    // Display the number of kills and lives before performing the action
    outfile << "UltimateRobot " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    cout << "UltimateRobot " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    // Get the current position of the robot
    int currentX = getX();
    int currentY = getY();
    move(battlefield, outfile);
    fire(battlefield, outfile);
    fire(battlefield, outfile);
    fire(battlefield, outfile);
    step(battlefield, outfile);

    // Display the updated battlefield after all actions
    outfile << "Position Robot After Doing Action" << endl;
    cout << "Position Robot After Doing Action" << endl;
    battlefield->display(outfile);
    outfile << "____________________________________" << endl;
    cout << "____________________________________" << endl;
}
char UltimateRobot::getSymbol() { return 'U'; }

RoboTank::RoboTank(string type, string name, int x, int y)
    : Robot(type, name, x, y), ShootingRobot(type, name, x, y) {}
RoboTank::~RoboTank() {}
void RoboTank::fire(Battlefield *battlefield, ofstream &outfile)
{
    // get the number of row and columns in battlefield
    int battlefieldRows = battlefield->getRows();
    int battlefieldCols = battlefield->getCols();

    int currentX = getX(); // get the current position x of RoboTank
    int currentY = getY(); // get the current position y of RoboTank

    bool validTargetFound = false;
    // int targetX, targetY;
    while (!validTargetFound)
    {
        int targetX = rand() % battlefieldRows;
        int targetY = rand() % battlefieldCols;

        // Ensure the target position is within the battlefield bounds
        if (targetX >= 0 && targetX < battlefieldRows && targetY >= 0 && targetY < battlefieldCols)
        {
            // Check if the target position is occupied by another robot
            if (battlefield->isPositionOccupied(targetX, targetY))
            {
                Robot *targetRobot = battlefield->getRobotAtPosition(targetX, targetY);
                if (targetRobot && targetRobot != this) // // Ensure robot wont shoot back itself
                {
                    battlefield->clearPosition(targetX, targetY);
                    targetRobot->decrementLives();
                    outfile << "RoboTank " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    cout << "RoboTank " << getName() << " destroyed a robot named " << targetRobot->getName() << " at (" << targetX << ", " << targetY << ")." << endl;
                    incrementKills();

                    if (targetRobot->getLives() > 0)
                    {
                        battlefield->getDeadRobotsQueue().enqueue(targetRobot);
                        battlefield->getRobotList().remove(targetRobot);
                    }
                    else
                    {
                    battlefield->getRobotList().remove(targetRobot);
                    }

                    if (getKills() == 3)
                    {
                        markForUpgrade();
                        outfile << "RoboTank " << getName() << " has been upgraded to RoboTank." << endl;
                        cout << "RoboTank " << getName() << " has been upgraded to RoboTank." << endl;
                    }
                }
            }
            battlefield->clearPosition(targetX, targetY);
            battlefield->placeFireMark(targetX, targetY);
            outfile << "Fire at (" << targetX << ", " << targetY << ")." << endl;
            cout << "Fire at (" << targetX << ", " << targetY << ")." << endl;
            battlefield->drawLine(currentX, currentY, targetX, targetY);
            validTargetFound = true; // A valid target or empty position within bounds has been found
        }
        else
        {
            // If the target position is out of bounds, continue searching
            continue;
        }
    }
}
void RoboTank::action(Battlefield *battlefield, ofstream &outfile)
{
    // Clear fire marks before performing the action
    battlefield->clearFireMarks();
    battlefield->clearLineMarks();

    // Display the number of kills and lives before performing the action
    outfile << "RoboTank " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;
    cout << "RoboTank " << getName() << " - Kills: " << getKills() << ", Lives: " << getLives() << endl;

    // Get the current position of the robot
    int currentX = getX();
    int currentY = getY();
    fire(battlefield, outfile);

    // Display the updated battlefield after all actions
    outfile << "Position Robot After Doing Action" << endl;
    cout << "Position Robot After Doing Action" << endl;
    battlefield->display(outfile);
    outfile << "____________________________________" << endl;
    cout << "____________________________________" << endl;
}
char RoboTank::getSymbol() { return 'K'; }
