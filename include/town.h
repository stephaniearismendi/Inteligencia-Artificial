#include "cell.h"
#include <iostream>
#include <vector>
#include <list>

class town
{
public:
    town();
    ~town();

    void setSize(int, int);
    bool setInitialPos(int, int);
    bool setEndPos(int, int);
    void genObstacleRand(int);
    bool genMapFile(std::string);
    void clearMap();
    void clearSolution();

    void print();
    void printSol();

    bool isValid(int, int);
    bool solve();

    int calculateDistance(std::pair<int, int>, std::pair<int, int>);
    int evaluation(Cell &cell, std::pair<int, int>);

    void insertNodes(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it);
    int isInList(std::list<Cell> &list, Cell &node);

private:
    bool solve_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes);

    std::vector<std::vector<bool>> map_; // 0 = Clear  -  1 = Obstacle
    std::vector<std::vector<bool>> solution;
    std::pair<int, int> initialPos_;
    std::pair<int, int> endPos_;
    int width_;
    int height_;
};