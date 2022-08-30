#include "cell.cpp"
#include <time.h>
#include <math.h>

/* 
    This whole mess needs to be cleaned 
 */
class Game
{
private:
    Cell **cellTable;
    Grid *board;
    int numOfCells;
    int size;
    /* data */
public:
    Game(int size, Grid *grid);
    ~Game();

    void Initialize();
    void Initialize(int *start, int size);
    void Update();
    void ApplyRules();

    int liveNeighours(int i);
    int liveNeighbours(int i);

    void neighbours(int i);
};

Game::Game(int size, Grid *grid)
{
    this->size = size;
    this->board = grid;
    this->numOfCells = size * size;
    this->cellTable = new Cell *[numOfCells];
}

void Game::Initialize()
{
    srand(time(0));

    for (int i = 0; i < numOfCells; i++)
    {
        //cellTable[i] = nullptr;
        cellTable[i] = new Cell(i);
        cellTable[i]->initNeighbors();
        //std::cout << i << "\n";
    }
    for (int i = 0; i < numOfCells; i++)
    {
        //cellTable[i] = nullptr;
        this->neighbours(i);
    }
}

void Game::Initialize(int *start, int size)
{
    this->size = size;
    this->numOfCells = size * size;
    this->cellTable = new Cell *[numOfCells];

    for (int i = 0; i < numOfCells; i++)
    {
        //cellTable[i] = nullptr;
        cellTable[i] = new Cell(start[i], i);
        cellTable[i]->initNeighbors();
    }
    for (int i = 0; i < numOfCells; i++)
    {
        //cellTable[i] = nullptr;
        this->neighbours(i);
    }
}

void Game::ApplyRules()
{

    for (int i = 0; i < numOfCells; i++)
    {
        int liveNeigbours = cellTable[i]->numOfAliveNeigbors();
        if (cellTable[i]->getCurrent() == 1)
        {
            std::cout << "im alive \n";
            if (liveNeigbours == 2 || liveNeigbours == 3)
            {
                std::cout << "i stay alive \n";
                cellTable[i]->setNext(1);
            } else {
                std::cout << "this should die \n";
                cellTable[i]->setNext(0);
            }
        }
        else if (cellTable[i]->getCurrent() == 0)
        {
            std::cout << "im ded \n";
            if (liveNeigbours == 3)
            {
                std::cout << "i wake up \n";
                cellTable[i]->setNext(1);
            }
            else
            {
                std::cout << "i stay ded \n";
                cellTable[i]->setNext(0);
            }
        }
    }
}

void Game::Update()
{
    int updatedTable[numOfCells];
    for (int i = 0; i < numOfCells; i++)
    {
        cellTable[i]->setCurrent();
        cellTable[i]->setNext(0);
        updatedTable[i] = cellTable[i]->getCurrent();
        
    }
   
    board->setStart(updatedTable, sqrt(numOfCells));
    board->cellsToTexture();
}

int Game::liveNeighours(int i)
{
    int aliveNeigbours = 0;

    //Vasen reuna
    if (i % size != 0)
    {
        aliveNeigbours += cellTable[i - 1]->getCurrent(); // vasen kesi
    }

    //oikee reuna
    if (i % size != size - 1)
    {
        aliveNeigbours += cellTable[i + 1]->getCurrent(); // Oikee keski
    }

    //yläreuna
    if (i >= size)
    {
        if (i % size != 0)
        {
            aliveNeigbours += cellTable[i - size - 1]->getCurrent(); // ylä vasen
        }
        if (i % size != size - 1)
        {
            aliveNeigbours += cellTable[i - size + 1]->getCurrent(); // ylä oikee
        }
        aliveNeigbours += cellTable[i - size]->getCurrent(); // ylä keskel
    }

    //alareuna
    if (i < numOfCells - size)
    {
        aliveNeigbours += cellTable[i + size]->getCurrent(); //  keski ala
        if (i % size != 0)
        {
            aliveNeigbours += cellTable[i + size - 1]->getCurrent(); // vasen ala
        }
        if (i + size != this->numOfCells - 1)
        {
            aliveNeigbours += cellTable[i + size + 1]->getCurrent(); // oikee ala
        }
    }

    return aliveNeigbours;
}
int Game::liveNeighbours(int i)
{
    int aliveNeigbours = 0;
    if (i != 0)
    {
        aliveNeigbours += cellTable[(i + size) % this->numOfCells]->getCurrent();     //alas
        aliveNeigbours += cellTable[(i + size) % this->numOfCells + 1]->getCurrent(); //alas oikee
        aliveNeigbours += cellTable[(i + size) % this->numOfCells - 1]->getCurrent(); //alas vasen
        aliveNeigbours += cellTable[(i - size) % this->numOfCells]->getCurrent();     //ylös
        aliveNeigbours += cellTable[(i - size) % this->numOfCells + 1]->getCurrent(); //ylös oikee
        aliveNeigbours += cellTable[(i - size) % this->numOfCells - 1]->getCurrent(); //ylös vasen
    }
    return aliveNeigbours;
}

void Game::neighbours(int i){
    
    //yläreuna
    if (i >= size)
    {
        if (i % size != 0)
        {
            cellTable[i]->addNeighbor(cellTable[i - size - 1]); // ylä vasen
        }

        cellTable[i]->addNeighbor(cellTable[i - size]); // ylä keskel

        if (i % size != size - 1)
        {
            cellTable[i]->addNeighbor(cellTable[i - size + 1]); // ylä oikee
        }
        
    }

    //oikee reuna
    if (i % size != size - 1)
    {
        this->cellTable[i]->addNeighbor(cellTable[i + 1]); // Oikee keski
    }

     //alareuna
    if (i < numOfCells - size)
    {   
        if (i + size != this->numOfCells - 1)
        {
            cellTable[i]->addNeighbor(cellTable[i + size + 1]); // oikee ala
        }

        cellTable[i]->addNeighbor(cellTable[i + size]); //  keski ala

        if (i % size != 0)
        {
            cellTable[i]->addNeighbor(cellTable[i + size - 1]); // vasen ala
        }
        
    }

    //Vasen reuna
    if (i % size != 0)
    {
        cellTable[i]->addNeighbor(cellTable[i - 1]); // vasen kesi
    }


    
}


Game::~Game()
{
}
