/**********|**********|**********|
Program: Robot.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: CHIN ZHEN HO , ERIC TEOH WEI XIANG , BERNARD RYAN SIM KANG XUAN , CHAN KAH YONG
ID: 1221102540 , 1221102007 , 1221101777 , 1231302796
Lecture Section: TC2L
Tutorial Section: TT6L
Email: 1221102540@soffice.mmu.edu.my , 1221102007@soffice.mmu.edu.my , 1221101777@soffice.mmu.edu.my , 1231302796@soffice.mmu.edu.my
Phone: 0182067278 , 0174063708 , 0167168548 , 0109586656
**********|**********|**********/

#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>

using namespace std;

class Battlefield;

class Robot
{
private:
    string type, name;
    int posX, posY, kills, lives;
    bool upgradeFlag;

public:
    Robot();                                                                       // Default constructor
    Robot(const string &in_type, const string &in_name, int in_posX, int in_posY); // Parameterized constructor
    virtual ~Robot();                                                              // Virtual destructor
    string getType();
    string getName();
    int getX();
    int getY();
    bool isMarkedForUpgrade() const;
    void markForUpgrade();
    void setPosition(int x, int y);
    void incrementKills();
    int getKills();
    void decrementLives();
    void setLives(int newLives);
    int getLives();
    // pure virtual function
    virtual char getSymbol() = 0;
    virtual void action(Battlefield *battlefield, ofstream &outfile) = 0;
};

class MovingRobot : virtual public Robot
{
public:
    MovingRobot(string type, string name, int x, int y);
    virtual void move(Battlefield *battlefield, ofstream &outfile) = 0;
};

class ShootingRobot : virtual public Robot
{
public:
    ShootingRobot(string type, string name, int x, int y);
    virtual void fire(Battlefield *battlefield, ofstream &outfile) = 0;
};

class SeeingRobot : virtual public Robot
{
public:
    SeeingRobot(string type, string name, int x, int y);
    virtual void look(Battlefield *battlefield, ofstream &outfile) = 0;
};

class SteppingRobot : virtual public Robot
{
public:
    SteppingRobot(string type, string name, int x, int y);
    virtual void step(Battlefield *battlefield, ofstream &outfile) = 0;
};

class TerminatorRoboCop : public SeeingRobot, public MovingRobot, public ShootingRobot, public SteppingRobot
{
private:
    string type, name;
    int posX, posY;

public:
    TerminatorRoboCop(string type, string name, int x, int y);
    ~TerminatorRoboCop();
    void setPosX(int newX);
    void setPosY(int newY);
    void look(Battlefield *battlefield, ofstream &outfile) override;
    void move(Battlefield *battlefield, ofstream &outfile) override;
    void fire(Battlefield *battlefield, ofstream &outfile) override;
    void step(Battlefield *battlefield, ofstream &outfile) override;
    void action(Battlefield *battlefield, ofstream &outfile) override;
    char getSymbol() override;
};

class RoboCop : public SeeingRobot, public MovingRobot, public ShootingRobot
{
private:
    string type, name; // Type and name of the RoboCop
    int posX, posY;    // Current position of the RoboCop
public:
    RoboCop(string type, string name, int x, int y);                   // Constructor to initialize the RoboCop with specified attributes
    ~RoboCop();                                                        // Destructor
    void look(Battlefield *battlefield, ofstream &outfile) override;   // Function to allow RoboCop to look around its current position
    void move(Battlefield *battlefield, ofstream &outfile) override;   // Function to allow RoboCop to move to a new position
    void fire(Battlefield *battlefield, ofstream &outfile) override;   // Function to allow RoboCop to fire at targets
    void action(Battlefield *battlefield, ofstream &outfile) override; // Function to perform all actions for the RoboCop
    char getSymbol() override;                                         // Function to get the symbol representing the RoboCop on the battlefield
};

class Terminator : public SeeingRobot, public MovingRobot, public SteppingRobot
{
private:
    string type, name;
    int posX, posY;

public:
    Terminator(string type, string name, int x, int y);
    ~Terminator();
    void setPosX(int newX);
    void setPosY(int newY);
    void look(Battlefield *battlefield, ofstream &outfile) override;
    void move(Battlefield *battlefield, ofstream &outfile) override;
    void step(Battlefield *battlefield, ofstream &outfile) override;
    void action(Battlefield *battlefield, ofstream &outfile) override;
    char getSymbol() override;
};

class BlueThunder : public ShootingRobot
{
private:
    string type, name;
    int posX, posY;
    int directionIndex;

public:
    BlueThunder(string type, string name, int x, int y);
    ~BlueThunder();
    void fire(Battlefield *battlefield, ofstream &outfile) override;
    void action(Battlefield *battlefield, ofstream &outfile) override;
    char getSymbol() override;
};

class Madbot : public ShootingRobot
{
private:
    string type, name;
    int posX, posY;

public:
    Madbot(string type, string name, int x, int y);
    ~Madbot();
    void fire(Battlefield *battlefield, ofstream &outfile) override;
    void action(Battlefield *battlefield, ofstream &outfile) override;
    char getSymbol() override;
};

class UltimateRobot : public MovingRobot, public ShootingRobot, public SteppingRobot
{
private:
    string type, name;
    int posX, posY;
    int fireAtX, fireAtY;

public:
    UltimateRobot(string type, string name, int x, int y);
    ~UltimateRobot();
    void setPosX(int newX);
    void setPosY(int newY);
    void move(Battlefield *battlefield, ofstream &outfile) override;
    void fire(Battlefield *battlefield, ofstream &outfile) override;
    void step(Battlefield *battlefield, ofstream &outfile) override;
    void action(Battlefield *battlefield, ofstream &outfile) override;
    char getSymbol() override;
};

class RoboTank : public ShootingRobot
{
private:
    string type, name;
    int posX, posY;
    int kills; // kills count for RoboTank

public:
    RoboTank(string type, string name, int x, int y);
    ~RoboTank();
    void fire(Battlefield *battlefield, ofstream &outfile) override;
    void action(Battlefield *battlefield, ofstream &outfile) override;
    char getSymbol() override;
};

#endif
