#include "cell.cpp"
#include <imgui.h>
#include <imgui-SFML.h>

#include <time.h>
#include <math.h>
#include <unordered_map>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>


/*
    This whole mess needs to be cleaned
 */

class Game
{
private:
    std::unordered_map<Pos, Cell> cellTable;
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
    std::shared_ptr<spdlog::logger> logger;

    /* data */
public:
    Game(int sizeX, int sizeY, Grid *grid);
    ~Game();

    void Initialize();
    void set_values(int *input_arr, int sizeX, int sizeY);
    void Update();
    bool ApplyRules();
    void setSize(int x, int y);
    void neighbours(int i);
};

Game::Game(int sizeX, int sizeY, Grid *grid)
{
    this->logger = spdlog::get("basic_logger");

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
    cellTable.clear();
 
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            cellTable.insert(std::unordered_map<Pos, Cell>::value_type(Pos{x, y}, Cell{Pos{x, y}, rand() % 2}));
        }
    }
}
void Game::setSize(int x, int y){
    this->sizeX = x;
    this->sizeY = y;
}

bool Game::ApplyRules()
{

    std::unordered_map<Pos, Cell> tempTable;
    // td::vector<std::unordered_map<Pos, Cell>::key_type> deadCells;
    this->miy = 0;
    this->mix = 0;

    int count = 0;
    for (auto iter = cellTable.begin(); iter != cellTable.end(); ++iter)
    {

        int liveNeighbours = 0;

        for (int yy = (*iter).first.y - 1; yy < (*iter).first.y + 2; yy++)
        {
            for (int xx = (*iter).first.x - 1; xx < (*iter).first.x + 2; xx++)

            {
                if (yy == (*iter).first.y && xx == (*iter).first.x)
                {

                    continue;
                }
                this->max = std::max(xx, max);
                this->may = std::max(yy, may);
                this->mix = std::min(xx, mix);
                this->miy = std::min(yy, miy);
                auto ci = cellTable.find(Pos{xx, yy});
                if (ci == cellTable.end())
                {
                    if ((*iter).second.getCurrent() == 1)
                    {

                        tempTable.insert(std::unordered_map<Pos, Cell>::value_type(Pos{xx, yy}, Cell{Pos{xx, yy}, 0}));
                        
                    }
                    continue;
                }
                if ((*ci).second.getLives() < 0)
                {
                    cellTable.erase(ci);

                    // deadCells.push_back((*iter).first);
                    continue;
                }
                liveNeighbours += (*ci).second.getCurrent();
            }
        }

        if (((*iter).second.getCurrent() == 1 && liveNeighbours == 2) || liveNeighbours == 3)
        {
            (*iter).second.setNext(1);
        }
        else
        {
            (*iter).second.setNext(0);
        }
    }

    for (auto iter = tempTable.begin(); iter != tempTable.end(); ++iter)
    {
        int liveNeighbours = 0;
        for (int i = (*iter).first.y - 1; i < (*iter).first.y + 2; i++)
        {
            for (int j = (*iter).first.x - 1; j < (*iter).first.x + 2; j++)
            {
                if (i == (*iter).first.y && j == (*iter).first.x)
                {
                    continue;
                }
                this->max = std::max(j, max);
                this->may = std::max(i, may);
                this->mix = std::min(j, mix);
                this->miy = std::min(i, miy);
                auto ci = cellTable.find(Pos{j, i});
                if (ci == cellTable.end())
                {
                    continue;
                }

                liveNeighbours += (*ci).second.getCurrent();
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
        cellTable.insert((*iter));
    }
    // cellTable.merge(tempTable);
    tempTable.clear();

    return true;
}

void Game::Update()
{
    ImGui::Text("active cells: %i", cellTable.size());
    logger->debug("active cells: {}", cellTable.size());

    if (this->miy > 0)
    {
        this->miy = 0;
    }
    if (this->mix > 0)
    {
        this->mix = 0;
    }
    board->setStart(this->max, this->may, this->mix, this->miy);
    // std::cout << "mix" <<mix << "miy" << miy << '\n';
    // std::cout << "max" <<max << "may" << may << '\n';

    for (auto iter = cellTable.begin(); iter != cellTable.end(); iter++)
    {
        (*iter).second.setCurrent();
        board->set((*iter).second.getCurrent(), (*iter).first.x - mix, (*iter).first.y - miy);
    }
}

void Game::set_values(int *input_arr, int sizeX, int sizeY)
{
    /*
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->max = sizeX;
        this->may = sizeY; */
    for (int y = 0; y < sizeY; y++)
    {

        for (int x = 0; x < sizeX; x++)
        {
            cellTable.insert(std::unordered_map<Pos, Cell>::value_type(Pos{x, y}, Cell{Pos{x, y}, input_arr[(y * sizeX) + x]}));
        }
    }
}

Game::~Game()
{
    delete[] updatedTable;
}
