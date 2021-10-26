#include "town.h"
#include <vector>
#include <list>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <climits>

#define MAX_COST 10000

town::town()
{
    initialPos_ = std::make_pair(-1, -1);
    endPos_ = std::make_pair(-1, -1);
}
town::~town()
{
    for (int i = width_ - 1; i >= 0; i--)
    {
        for (size_t j = 0; j < height_; j++)
            map_[i].pop_back();
        map_.pop_back();
    }
}

void town::setSize(int width, int height)
{
    width_ = width;
    height_ = height;
    std::vector<bool> aux;
    for (size_t i = 0; i < height_; i++)
        aux.push_back(0);
    for (size_t i = 0; i < width_; i++)
        map_.push_back(aux);
}

bool town::setInitialPos(int X, int Y)
{
    if (X > 0 && Y > 0 && X != endPos_.first && Y != endPos_.second && X <= width_ && Y <= height_ && !map_[X - 1][Y - 1])
    {
        initialPos_.first = X - 1;
        initialPos_.second = Y - 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool town::setEndPos(int X, int Y)
{
    if (X > 0 && Y > 0 && X != initialPos_.first && Y != initialPos_.second && X <= width_ && Y <= height_ && !map_[X - 1][Y - 1])
    {
        endPos_.first = X - 1;
        endPos_.second = Y - 1;
        return true;
    }
    else
    {
        return false;
    }
}

void town::print()
{
    std::cout << "\t\t┌";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┐\n";

    for (size_t i = 0; i < height_; i++)
    {
        std::cout << "\t\t|";
        for (size_t j = 0; j < width_; j++)
            if (initialPos_.first == j && initialPos_.second == i)
                std::cout << "ø";
            else if (endPos_.first == j && endPos_.second == i)
                std::cout << "×";
            else if (map_[j][i])
                std::cout << "█";
            else
                std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "\t\t└";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┘\n";
}

void town::printSol()
{
    std::cout << "\t\t┌";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┐\n";

    for (size_t i = 0; i < height_; i++)
    {
        std::cout << "\t\t|";
        for (size_t j = 0; j < width_; j++)
            if (initialPos_.first == j && initialPos_.second == i)
                std::cout << "ø";
            else if (endPos_.first == j && endPos_.second == i)
                std::cout << "×";
            else if (solution[j][i])
                std::cout << "o";
            else if (map_[j][i])
                std::cout << "█";
            else
                std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "\t\t└";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┘\n";
}

void town::genObstacleRand(int perc)
{
    int sz = width_ * height_;
    int counter = 0;
    float percentage = perc * 0.01;
    sz = sz * percentage;
    int i = 0, j = 0;
    while (counter < sz)
    {
        i = rand() % width_;
        j = rand() % height_;
        if (!map_[i][j] && (i != initialPos_.first || j != initialPos_.second) && (i != endPos_.first || j != endPos_.second))
        {
            map_[i][j] = !map_[i][j];
            counter++;
        }
    }
}

bool town::genMapFile(std::string filename)
{
    std::ifstream File;
    File.open(filename, std::ios::in);
    if (File.is_open())
    {
        this->clearMap();
        int width, height;
        File >> width >> height;
        this->setSize(width, height);
        int input;
        for (size_t j = 0; j < height; j++)
            for (size_t i = 0; i < width_; i++)
            {
                File >> input;
                if (input == 2)
                {
                    initialPos_ = std::make_pair(i, j);
                }
                else if (input == 3)
                {
                    endPos_ = std::make_pair(i, j);
                }
                else if (input == 0 || input == 1)
                {
                    map_[i][j] = input;
                }
            }
        File.close();
        return true;
    }
    else
    {
        File.close();
        return false;
    }
}

void town::clearMap(void)
{
    if (!map_.empty())
    {
        for (int i = width_ - 1; i >= 0; i--)
        {
            for (size_t j = 0; j < height_; j++)
                map_[i].pop_back();
            map_.pop_back();
        }
        initialPos_ = std::make_pair(-1, -1);
        endPos_ = std::make_pair(-1, -1);
        width_ = 0;
        height_ = 0;
    }
}

void town::clearSolution(void)
{
    std::vector<bool> aux;
    for (size_t i = 0; i < height_; i++)
        aux.push_back(0);
    for (size_t i = 0; i < width_; i++)
        solution.push_back(aux);
}

bool town::isValid(int X, int Y)
{
    if (X >= 0 && Y >= 0 && X < width_ && Y < height_ && !map_[X][Y])
        return true;
    else
        return false;
}

bool town::solve()
{
    std::list<Cell> open_nodes;
    std::list<Cell> closed_nodes;
    clearSolution();
    open_nodes.push_back(Cell(initialPos_, 0));
    return solve_(open_nodes, closed_nodes);
}

bool town::solve_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes)
{
    bool solved = false;
    int solution_cost = MAX_COST;
    Cell better_sol(std::make_pair(0, 0), MAX_COST);
    if (initialPos_ == endPos_)
        return true;
    while (!open_nodes.empty())
    {
        std::list<Cell>::iterator it = open_nodes.begin();
        std::list<Cell>::iterator i;
        for (i = open_nodes.begin(); i != open_nodes.end(); ++i)
        {
            if (evaluation(*it, endPos_) >= evaluation(*i, endPos_) && it->getCost() < solution_cost)
                it = i;
        }
        
        if(it->getPos() == endPos_)
        {
            if (evaluation(*it, endPos_) <= evaluation(better_sol, endPos_))
            {
                better_sol = *it;
                solution_cost = it->getCost();
            }
            closed_nodes.push_back(*it);
            open_nodes.erase(it);
            solved = true;
        }
        else
        {
            closed_nodes.push_back(*it);
            open_nodes.erase(it);
            std::list<Cell>::iterator iter = closed_nodes.end();
            --iter;
            insertNodes(open_nodes, closed_nodes, iter);
        }
    }
    if (solved) 
    {
        while (better_sol.getFather() != NULL)
        {
            solution[better_sol.getX()][better_sol.getY()] = true;
            better_sol = *better_sol.getFather();
        }
        return true;
    }
    return false;
}

void town::insertNodes(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it)
{
    if(isValid(it->getX() - 1, it->getY()))
    {
        Cell insert_cell(std::make_pair(it->getX() - 1, it->getY()), it->getCost() + 1);
        insert_cell.setFather(&*it);
        int i = isInList(open_nodes, insert_cell);
        int j = isInList(closed_nodes, insert_cell);
        if (j != -1 || i != -1)
        {
            if (i != -1) {
                std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
                std::advance(open_nodes_pos, i);
                if (evaluation(*open_nodes_pos, endPos_) > evaluation(insert_cell, endPos_)) {
                    open_nodes_pos->setCost(insert_cell.getCost());
                    //posible fallo
                    open_nodes_pos->setFather(insert_cell.getFather());
                }
            }
        }
        else
        {
            open_nodes.push_back(insert_cell);
        }
    }
    if(isValid(it->getX() + 1, it->getY()))
    {
        Cell insert_cell(std::make_pair(it->getX() + 1, it->getY()), it->getCost() + 1);
        insert_cell.setFather(&*it);
        int i = isInList(open_nodes, insert_cell);
        int j = isInList(closed_nodes, insert_cell);
        if (j != -1 || i != -1)
        {
            if (i != -1) {
                std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
                std::advance(open_nodes_pos, i);
                if (evaluation(*open_nodes_pos, endPos_) > evaluation(insert_cell, endPos_)) {
                    open_nodes_pos->setCost(insert_cell.getCost());
                    //posible fallo
                    open_nodes_pos->setFather(insert_cell.getFather());
                }
            }
        }
        else
        {
            open_nodes.push_back(insert_cell);
        }
    }
    if(isValid(it->getX(), it->getY() - 1))
    {
        Cell insert_cell(std::make_pair(it->getX(), it->getY() - 1), it->getCost() + 1);
        insert_cell.setFather(&*it);
        int i = isInList(open_nodes, insert_cell);
        int j = isInList(closed_nodes, insert_cell);
        if (j != -1 || i != -1)
        {
            if (i != -1) {
                std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
                std::advance(open_nodes_pos, i);
                if (evaluation(*open_nodes_pos, endPos_) > evaluation(insert_cell, endPos_)) {
                    open_nodes_pos->setCost(insert_cell.getCost());
                    //posible fallo
                    open_nodes_pos->setFather(insert_cell.getFather());
                }
            }
        }
        else
        {
            open_nodes.push_back(insert_cell);
        }
    }
    if(isValid(it->getX(), it->getY() + 1))
    {
        Cell insert_cell(std::make_pair(it->getX(), it->getY() + 1), it->getCost() + 1);
        insert_cell.setFather(&*it);
        int i = isInList(open_nodes, insert_cell);
        int j = isInList(closed_nodes, insert_cell);
        if (j != -1 || i != -1)
        {
            if (i != -1) {
                std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
                std::advance(open_nodes_pos, i);
                if (evaluation(*open_nodes_pos, endPos_) > evaluation(insert_cell, endPos_)) {
                    open_nodes_pos->setCost(insert_cell.getCost());
                    //posible fallo
                    open_nodes_pos->setFather(insert_cell.getFather());
                }
            }
        }
        else
        {
            open_nodes.push_back(insert_cell);
        }
    }
}

int town::isInList(std::list<Cell> &list, Cell &node)
{
    std::list<Cell>::iterator it;
    int pos = 0;
    for (it = list.begin(); it != list.end(); ++it) {
        if (it->getPos() == node.getPos())
            return pos;
        ++pos;
    }
    return -1;
}

int town::calculateDistance(std::pair<int, int> point, std::pair<int, int> destination)
{
    int xDistance, yDistance, distance;
    xDistance = point.first - destination.first;
    yDistance = point.second - destination.second;
    distance = abs(xDistance) + abs(yDistance);
    return distance;
}

int town::evaluation(Cell &cell, std::pair<int, int> destination)
{
    int aux = cell.getCost() + calculateDistance(cell.getPos(), destination);
    return aux;
}