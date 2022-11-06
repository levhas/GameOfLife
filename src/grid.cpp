#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

/*
    Handles drawing of the game
*/
class Grid : public sf::Drawable
{

public:
    Grid(int sizeX, int sizeY, sf::RenderWindow *window)
    {
        this->window = window;
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->size = sizeX * sizeY;

        for (int i = 0; i < this->size; i++)
        {
            points.push_back(0);
        }
    }
    void setStart(int sizeX, int sizeY)
    {
        points.clear();
        this->size = sizeX * sizeY;
        this->sizeX = sizeX;
        this->sizeY = sizeY;

        for (long i = 0; i < this->size; i++)
        {
            points.push_back(0);
        }
    }
    void set(int value, int pos)
    {
        points.at(pos) = value;
    }
    void cellsToTexture()
    {
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        cells.clear();
        cells.setPrimitiveType(sf::Quads);
        cells.resize(this->sizeX * sizeY * 4);

        for (int i = 0; i < sizeY; i++)
        {
            for (int j = 0; j < sizeX; j++)
            {

                int currentCell = points[i + (j * sizeY)];

                if (currentCell != 1)
                {

                    sf::Vertex *quad = &cells[(i + j * sizeX) * 4];
                    quad[0].position = sf::Vector2f(i * sizeX, j * sizeY);
                    quad[1].position = sf::Vector2f((i + 1) * sizeX, j * sizeY);
                    quad[2].position = sf::Vector2f((i + 1) * sizeX, (j + 1) * sizeY);

                    quad[3].position = sf::Vector2f(i * sizeX, (j + 1) * sizeY);
                    quad[0].color = sf::Color::Red;
                    quad[1].color = sf::Color::Blue;
                    quad[2].color = sf::Color::Green;
                    quad[3].color = sf::Color::Black;
                }
                if (currentCell == 0)
                {
                    sf::Vertex *quad = &cells[(i + j * sizeX) * 4];
                    quad[0].position = sf::Vector2f(i * sizeX, j * sizeY);
                    quad[1].position = sf::Vector2f((i + 1) * sizeX, j * sizeY);
                    quad[2].position = sf::Vector2f((i + 1) * sizeX, (j + 1) * sizeY);

                    quad[3].position = sf::Vector2f(i * sizeX, (j + 1) * sizeY);
                    quad[0].color = sf::Color::Black;
                    quad[1].color = sf::Color::Black;
                    quad[2].color = sf::Color::Black;
                    quad[3].color = sf::Color::Black;
                    if (mousePos.x > quad[0].position.x && mousePos.x < quad[1].position.x && mousePos.y > quad[0].position.y && mousePos.y < quad[2].position.y)
                    {
                        quad[0].color = sf::Color::Blue;
                        quad[1].color = sf::Color::Blue;
                        quad[2].color = sf::Color::Blue;
                        quad[3].color = sf::Color::Blue;
                    }
                }
                // std::cout << "x" << '\n';
            }
        }
    }

    ~Grid()
    {
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        window->setView(sf::View(cells.getBounds()));
        target.draw(cells, states);
    }
    sf::VertexArray cells;
    sf::RenderWindow *window;
    sf::View view;
    int sizeY;
    int sizeX;
    int size;
    std::vector<int> points;
};