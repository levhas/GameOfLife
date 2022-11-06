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

    /* data */
public:
    Game(int sizeX, int sizeY, Grid *grid);
    ~Game();

    void Initialize();

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
}

void Game::Initialize()
{
    srand(time(0));
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            // cellTable[i] = nullptr;
                cellTable.insert(std::map<Pos, Cell>::value_type(Pos{x, y}, Cell{Pos{x, y}}));
                for (int i = std::max(0,x-1); i < std::min(sizeX,x+2); i++)
                {
                    for (int j = std::max(0,y-1); j < std::min(sizeY,y+2); j++)
                    {

                        try
                        {
                            cellTable.at(Pos{j, i});
                        }
                        catch (const std::out_of_range &e)
                        {
                            cellTable.insert(std::map<Pos, Cell>::value_type(Pos{j, i}, Cell(Pos{j, i})));
                        }
                    }
                }
            // std::cout << i << "\n";
        }
    }
    std::cout << cellTable.size() << '\n';


}

bool Game::ApplyRules()
{
    int count = 0;
    for (auto iter = cellTable.begin(); iter != cellTable.end(); ++iter)
    {
        if((*iter).second.getLives() < 1 ){
            cellTable.erase(iter);
            continue;
        }
        int liveNeighbours = -(*iter).second.getCurrent();
        for (int i = std::max(0,(*iter).first.x-1); i < std::min(sizeX,(*iter).first.x+2); i++)
        {
            for (int j = std::max(0,(*iter).first.y-1); j < std::min(sizeY,(*iter).first.y+2); j++)

            {
                try
                {
                    liveNeighbours += cellTable.at(Pos{(*iter).first.x + j, (*iter).first.y + i}).getCurrent();
                }
                catch (const std::out_of_range &e)
                {


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


    return true;
}

void Game::Update()
{
    int mx = sizeX;
    int my = sizeY;
    board->setStart(mx, my);

    for (std::map<Pos, Cell>::iterator iter = cellTable.begin(); iter != cellTable.end(); iter++)
    {
        mx = std::max((*iter).first.x, mx);
        my = std::max((*iter).first.y, my);

        (*iter).second.setCurrent();

        board->set((*iter).second.getCurrent(), ((*iter).first.x * (*iter).first.y + (*iter).first.x));


    }


    board->cellsToTexture();
}

Game::~Game()
{
    delete[] updatedTable;
}
