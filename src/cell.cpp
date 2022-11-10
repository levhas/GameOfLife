/*
    This mess represents single cell in the grid,
    I have no clue when and why I made the decision, that this class also counts the neighbouring cells
*/
#include <SFML/Graphics.hpp>

struct Pos
{
    int x;
    int y;
};

class Cell
{
private:
    /* data */
    int current;
    int next;
    int id;
    int numOfNeighbors;
    Cell * neighbors[8];
    int life;
    bool changed;






public:
    Cell(Pos position);
    Cell();
    ~Cell();
    Cell(Pos position, int value);
    Pos pos;

    void setCurrent();
    void setNext(int next);
    int getCurrent();
    int getNext();
    void addNeighbor(Cell *neighbor);
    void initNeighbors();
    int getLives();
    void setNeighbors(Cell *neighbor, int size);
    int numOfAliveNeigbors();

};

Cell::Cell(Pos position) :
    pos(position)
{
    current = 1;
    next = 1;
    life = 10;
    changed = false;
}
Cell::Cell(Pos position, int value) :
    pos(position)
{
    current = value;
    next = 0;
    life = 10;
    changed = false;
}
Cell::Cell()
{
    current = 1;
    next = 1;
    life = 5;
    changed = false;
}

void Cell::setNext(int next){
    changed = true;
    this->next = next;
}

int Cell::getNext(){
    return this->next;
}

int Cell::getCurrent(){
    changed = false;
    return current;
}

void Cell::setCurrent(){
    if(current == 0 && next == 0){
        life -= 1;
    }
    else{
        life = 10;
    }
    this->current = this->next;
    this->next = 0;

}
void Cell::addNeighbor(Cell *neighbor){

    this->neighbors[numOfNeighbors] = neighbor;
    this->numOfNeighbors++;

}

void Cell::initNeighbors(){
    //neighbors = new Cell;
}

int Cell::numOfAliveNeigbors(){
    int alive = 0;
    for(int i = 0; i < numOfNeighbors; i++){
        alive += neighbors[i]->getCurrent();
    }
    return alive;
}
int Cell::getLives(){
    return this->life;
}



bool operator < (const Cell& l, const Cell& r) {
        return (l.pos<r.pos);
    }
bool operator < (const Pos& l, const Pos& r) {
        return (l.x<r.x || (l.x==r.x && l.y<r.y));
    }
bool operator == (const Pos& l, const Pos& r) {
        return (l.x == r.x && l.y == r.y);
    }

namespace std
{
    template <>
    struct hash<Pos>
    {
        size_t operator()( const Pos& k ) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + hash<int>()( k.x );
            res = res * 31 + hash<int>()( k.y );
            return res;
        }
    };
}

Cell::~Cell()
{

}
