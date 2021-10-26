#include "cell.h"

Cell::Cell()
{
    father_ = NULL;
}

Cell::Cell(std::pair<int, int> pos, int cost)
{
    pos_ = pos;
    cost_ = cost;
    father_ = NULL;
}

Cell::~Cell() {}

std::pair<int, int> Cell::getPos()
{
    return pos_;
}

int Cell::getX()
{
    return pos_.first;
}

int Cell::getY()
{
    return pos_.second;
}

int Cell::getCost()
{
    return cost_;
}

Cell* Cell::getFather()
{
    return father_;
}

void Cell::setCost(int cost)
{
    cost_ = cost;
}

void Cell::setPos(int X, int Y)
{
    pos_ = std::make_pair(X, Y);
}

void Cell::setPos(std::pair<int, int> pos)
{
    pos_ = pos;
}

void Cell::setFather(Cell* father)
{
    father_ = father;
}