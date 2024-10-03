#include "Battlefield.h"
#include <iomanip>

Battlefield::Battlefield(int rows, int cols) : m(rows), n(cols)
{
    battlefield = new char *[m]; // Allocate memory for the battlefield rows
    for (int i = 0; i < m; ++i)
    {
        battlefield[i] = new char[n]; // Allocate memory for the battlefield columns
        for (int j = 0; j < n; ++j)
        {
            battlefield[i][j] = '.'; // Initialize each cell of the battlefield with '.'
        }
    }
}

Battlefield::~Battlefield()
{
    for (int i = 0; i < m; ++i)
    {
        delete[] battlefield[i]; // Delete each row
    }
    delete[] battlefield; // Delete the array of rows
}

void Battlefield::display(ofstream &outfile)
{
    // Print the top boundary
    for (int i = 0; i < n + 2; ++i)
    {
        outfile << "X ";             // Boundary character
        cout << "\033[34mX \033[0m"; // \033[34m sets the text color to blue, \033[0m resets the color
    }
    outfile << endl;
    cout << endl;

    for (int i = 0; i < m; ++i)
    {
        // Print the left boundary
        cout << "\033[34mX \033[0m";
        outfile << "X ";
        for (int j = 0; j < n; ++j)
        {
            if (battlefield[i][j] == '!')
            {
                outfile << "! "; // Print fire points
                cout << "\033[31m! \033[0m";
            }
            else if (battlefield[i][j] == '*')
            {
                outfile << "* ";
                cout << "\033[33m* \033[0m";
            }
            else
            {
                outfile << battlefield[i][j] << ' '; // Output the character representing each cell
                cout << battlefield[i][j] << ' ';
            }
        }
        // Print the right boundary
        outfile << "X ";
        cout << "\033[34mX \033[0m";
        outfile << endl;
        cout << endl;
    }
    // Print the bottom boundary
    for (int i = 0; i < n + 2; ++i)
    {
        outfile << "X ";
        cout << "\033[34mX \033[0m";
    }
    outfile << endl;
    cout << endl;
}

void Battlefield::placeRobot(Robot *robot, int x, int y)
{
    battlefield[x][y] = robot->getSymbol(); // Set the character representing the robot on the battlefield
    robot->setPosition(x, y);               // Update the position of the robot
    robots.add(robot);                      // Add the robot to the list of robots on the battlefield
}

void Battlefield::clearPosition(int x, int y)
{
    battlefield[x][y] = '.'; // Set the cell at the specified position to empty ('.')
}

bool Battlefield::isPositionValid(int x, int y)
{
    return x >= 0 && x < m && y >= 0 && y < n; // Check if the coordinates are within the battlefield bounds
}

bool Battlefield::isPositionOccupied(int x, int y)
{
    return battlefield[x][y] != '.'; // Check if the cell at the specified position is not empty
}

void Battlefield::updatePosition(Robot *robot, int newX, int newY)
{
    if (isPositionValid(newX, newY)) // Check if the new position is valid
    {
        if (!isPositionOccupied(newX, newY)) // Check if the new position is unoccupied
        {
            clearPosition(robot->getX(), robot->getY());  // Clear the current position of the robot
            robot->setPosition(newX, newY);               // Update the position of the robot
            battlefield[newX][newY] = robot->getSymbol(); // Update the battlefield with the robot's new position
        }
        else
        {
            cout << "Cannot move " << robot->getName() << " to (" << newX << ", " << newY << ") because the position is occupied." << endl;
        }
    }
    else
    {
        cout << "Cannot move " << robot->getName() << " to (" << newX << ", " << newY << ") because the position is invalid." << endl;
    }
}

int Battlefield::getRows()
{
    return m;
}

int Battlefield::getCols()
{
    return n;
}

Robot *Battlefield::getRobotAtPosition(int x, int y)
{
    // Iterate through the list of robots and return the one at the specified position
    for (RobotList::Node *current = robots.getHead(); current != nullptr; current = current->next)
    {
        if (current->data->getX() == x && current->data->getY() == y)
        {
            return current->data;
        }
    }
    return nullptr; // Return nullptr if no robot is found at the specified position
}

RobotList &Battlefield::getRobotList()
{
    return robots;
}

Queue &Battlefield::getDeadRobotsQueue()
{
    return deadRobots;
}

string Battlefield::reenterRobot(Robot *robot)
{
    int x, y;
    int maxAttempts = 100; // Maximum number of attempts to find a valid position
    int attempts = 0;
    while (attempts < maxAttempts)
    {
        x = rand() % m;
        y = rand() % n;
        if (!isPositionOccupied(x, y))
        {
            placeRobot(robot, x, y); // Place the robot at the new position
            return "Robot " + robot->getName() + " reentered at (" + to_string(x) + ", " + to_string(y) + ")";
        }
        attempts++;
    }
    cerr << "Failed to find a valid position for robot reentry: " << robot->getName() << endl;
    return "";
}

void Battlefield::placeFireMark(int x, int y)
{
    if (isPositionValid(x, y))
    {
        battlefield[x][y] = '!'; // Place a fire mark ('!') at the specified position
    }
}

void Battlefield::drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        // Mark the current position on the battlefield with a symbol, e.g., '*'
        if (battlefield[x1][y1] == '.') // Only mark empty positions
        {
            battlefield[x1][y1] = '*';
        }
        if (x1 == x2 && y1 == y2) // Check if the end point has been reached
        {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void Battlefield::clearFireMarks()
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (battlefield[i][j] == '!')
            {
                battlefield[i][j] = '.';
            }
        }
    }
}

void Battlefield::clearLineMarks()
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (battlefield[i][j] == '*')
            {
                battlefield[i][j] = '.';
            }
        }
    }
}
