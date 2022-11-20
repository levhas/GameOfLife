#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

/*
    Handles drawing of the game
*/
class Grid : public sf::Drawable, public sf::Transformable
{

public:
    Grid(int sizeX, int sizeY, sf::RenderWindow *window) : cells(sf::Quads)
    {
        this->window = window;
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->size = sizeX * sizeY;
        this->offsetY = 0;
        this->offsetX = 0;
    }
    void setStart(int sizeX, int sizeY, int offsetX, int offsetY)
    {

        this->sizeX = sizeX;
        this->sizeY = sizeY;
        //if map has expanded to negative x or y
        //subtract the negative distance form 0 from sizeX, aka sizeX = sizeX = sizeX -- offeset
        //sizeX grows by offset amount
        if(offsetX < 0){
            this->sizeX -= offsetX;
        }
        if(offsetY < 0){
            this->sizeY -= offsetY;
        }
        cells.clear();
        cells.resize((this->sizeX) * (this->sizeY) * 5);
        this->size = sizeX * sizeY;

    }
    void set(int value, int x, int y)
    {

        sf::Vertex *quad = &cells[(x + y * sizeX) * 4];
        quad[0].position = sf::Vector2f(x * sizeX, y * sizeY);
        quad[1].position = sf::Vector2f((x + 1) * sizeX, y * sizeY);
        quad[2].position = sf::Vector2f((x + 1) * sizeX, (y + 1) * sizeY);
        quad[3].position = sf::Vector2f(x * sizeX, (y + 1) * sizeY);

        if (value == 1)
        {

            quad[0].color = sf::Color::Green;
            quad[1].color = sf::Color::Green;
            quad[2].color = sf::Color::Green;
            quad[3].color = sf::Color::Green;
        }

        if (value == 0)
        {
            quad[0].color = sf::Color::Black;
            quad[1].color = sf::Color::Black;
            quad[2].color = sf::Color::Black;
            quad[3].color = sf::Color::Black;
        }
    }


    ~Grid()
    {
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        window->setView(sf::View(cells.getBounds()));
        target.draw(cells, states);
    }
    sf::VertexArray cells;
    sf::RenderWindow *window;
    sf::View view;
    int sizeY;
    int sizeX;
    int offsetX, offsetY;
    int size;
    std::vector<int> points;
};