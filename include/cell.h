#include <iostream>

class Cell
{
public:
    Cell();
    Cell(std::pair<int, int>, int);
    ~Cell();

    std::pair<int, int> getPos();
    int getX();
    int getY();
    int getCost();
    Cell* getFather();

    void setCost(int);
    void setPos(int, int);
    void setPos(std::pair<int, int> pos);
    void setFather(Cell*);

private:
    Cell* father_;
    std::pair<int, int> pos_;
    int cost_;
};