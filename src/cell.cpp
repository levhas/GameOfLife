/*
    This mess represents single cell in the grid,
    I have no clue when and why I made the decision, that this class also counts the neighbouring cells
*/
class Cell
{
private:
    /* data */
    int current;
    int next;
    int id;
    int numOfNeighbors;  
    Cell * neighbors[8];
    
public:
    Cell(int current, int id);
    Cell(int id);
    Cell();
    ~Cell();
    void setCurrent();
    void setNext(int next);
    int getCurrent();
    int getNext();
    void addNeighbor(Cell *neighbor);
    void initNeighbors();
     
    void setNeighbors(Cell *neighbor, int size);
    int numOfAliveNeigbors();
};

Cell::Cell() :
    next(0),
    current(rand()%2),
    id()
{    
    numOfNeighbors = 0;
    
} 

Cell::Cell(int id) :
    next(0),
    current(rand()%2),
    id(id)
{    
    numOfNeighbors = 0;
    
}    
Cell::Cell(int current, int id) :
    current(current),
    next(current),
    id(id)
{
    numOfNeighbors = 0;
}

void Cell::setNext(int next){
    this->next = next;
}

int Cell::getNext(){
    return this->next;
}

int Cell::getCurrent(){
    return current;
}

void Cell::setCurrent(){
    this->current = this->next;
    
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




Cell::~Cell()
{
    
}
