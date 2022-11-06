#include "cell.cpp"
#include <time.h>
#include <math.h>
#include <map>
#include <stdexcept>

/*
    This whole mess needs to be cleaned
 */

class Game
{
private:
    std::map<Pos, Cell> cellTable;
    Grid *board;
    int numOfCells;
    int sizeX, sizeY;
    int *updatedTable;
    float speed;
    float lastUpdate;
    int max;
    int may;
    int mix;
    int miy;


    /* data */
public:
    Game(int sizeX, int sizeY, Grid *grid);
    ~Game();

    void Initialize();
    void set_values(int * input_arr, int sizeX, int sizeY);
    void Update();
    bool ApplyRules();

    void neighbours(int i);
};

Game::Game(int sizeX, int sizeY, Grid *grid)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->board = grid;
    this->numOfCells = sizeX * sizeY;
    this->updatedTable = new int[numOfCells];
    this->lastUpdate = 0.000001;
    max = sizeX;
    may = sizeY;
}

void Game::Initialize()
{
    srand(time(0));
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            // cellTable[i] = nullptr;
                cellTable.insert(std::map<Pos, Cell>::value_type(Pos{x, y}, Cell{Pos{x, y},rand() % 2}));
        }
    }
    std::cout << cellTable.size() << '\n';


}

bool Game::ApplyRules()
{   
    std::map<Pos, Cell> tempTable;

    int count = 0;
    for (auto iter = cellTable.begin(); iter != cellTable.end(); ++iter)
    {
        
        int liveNeighbours = 0;
        max = std::max((*iter).first.x, max);
        may = std::max((*iter).first.y, may);
        for (int i = (*iter).first.y-1; i < (*iter).first.y+2; i++)
        {
            for (int j = (*iter).first.x-1; j < (*iter).first.x+2; j++)

            {
                if(i == (*iter).first.y && j == (*iter).first.x){
                    std::cout << "skipped self" << '\n';

                    continue;
                }
                try
                {
                    std::cout << "am i here" << '\n';

                    liveNeighbours += cellTable.at(Pos{j,i}).getCurrent();
                    std::cout << liveNeighbours << '\n';
                }
                catch (const std::out_of_range &e)
                {

                    tempTable.insert(std::map<Pos, Cell>::value_type(Pos{j,i}, Cell{Pos{j, i},0}));


                }
            }
        }

        if ((*iter).second.getCurrent() == 1)
        {
            if (liveNeighbours == 2 || liveNeighbours == 3)
            {
                (*iter).second.setNext(1);
            }
            else
            {
                (*iter).second.setNext(0);
            }
        }
        else if ((*iter).second.getCurrent() == 0)
        {

            if (liveNeighbours == 3)
            {

                (*iter).second.setNext(1);
            }
            else
            {
                (*iter).second.setNext(0);
            }
        }
    }

    cellTable.merge(tempTable);
    for (auto iter = cellTable.begin(); iter != cellTable.end(); ++iter)
    {
        
        int liveNeighbours = 0;
        max = std::max((*iter).first.x, max);
        may = std::max((*iter).first.y, may);
        mix = std::min((*iter).first.x, mix);
        miy = std::min((*iter).first.y, miy);
    }

    return true;
}

void Game::Update()
{

    board->setStart(max, may);

    for (auto iter = cellTable.begin(); iter != cellTable.end(); iter++)
    {


        (*iter).second.setCurrent();
        
        

        board->set((*iter).second.getCurrent(), ((max * (*iter).first.y) + (*iter).first.x));


    }


    board->cellsToTexture();
}

void Game::set_values(int * input_arr, int sizeX, int sizeY){

    this->sizeX = sizeX;
    this->sizeY = sizeY;
    cellTable.clear();
    for(int y = 0; y < sizeY; y++){

        for(int x = 0; x < sizeX; x++){
            
            cellTable.insert(std::map<Pos, Cell>::value_type(Pos{x, y}, Cell{Pos{x, y}, input_arr[y*sizeX + x]}));

        }
    }

}



Game::~Game()
{
    delete[] updatedTable;
}
