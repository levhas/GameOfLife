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
    Grid(int size, sf::RenderWindow * window)
    {   
        this->window = window;
        this->size = size;

        points = new int*[this->size * this->size];
        for(int i = 0; i < this->size * this->size; i++){
            points[i] = 0;
        }
    }
    void setStart(int *start, int newSize)
    {   
        delete[] points;
        this->size = newSize;
        points = new int * [this->size * this->size];
        points[0] = &start[0];
        for (long i = 0; i < this->size * this->size; i++)
        {
            points[i] = &start[i];
        }
        
    }

    void cellsToTexture()
    {
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        
        cells.setPrimitiveType(sf::Quads);
        cells.resize(this->size * this->size * 4);
        
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                int currentCell = *points[i + (j * size)];
                
                if (currentCell == 1)
                {
                    sf::Vertex *quad = &cells[(i + j * size) * 4];
                    quad[0].position = sf::Vector2f(i * size, j * size);
                    quad[1].position = sf::Vector2f((i + 1) * size, j * size);
                    quad[2].position = sf::Vector2f((i + 1) * size, (j + 1) * size);
                    quad[3].position = sf::Vector2f(i * size, (j + 1) * size);

                    quad[0].color = sf::Color::Red; 
                    quad[1].color = sf::Color::White;  
                    quad[2].color = sf::Color::Green;
                    quad[3].color = sf::Color::Black; 
                }
                if (currentCell == 0)
                {
                    sf::Vertex *quad = &cells[(i + j * size) * 4];
                    quad[0].position = sf::Vector2f(i * size, j * size);
                    quad[1].position = sf::Vector2f((i + 1) * size, j * size);
                    quad[2].position = sf::Vector2f((i + 1) * size, (j + 1) * size);
                    quad[3].position = sf::Vector2f(i * size, (j + 1) * size);

                    quad[0].color = sf::Color::Black; 
                    quad[1].color = sf::Color::Black;  
                    quad[2].color = sf::Color::Black;
                    quad[3].color = sf::Color::Black; 
                    if(mousePos.x > quad[0].position.x && mousePos.x < quad[1].position.x && mousePos.y > quad[0].position.y && mousePos.y < quad[2].position.y){
                        quad[0].color = sf::Color::Blue; 
                        quad[1].color = sf::Color::Blue;  
                        quad[2].color = sf::Color::Blue;
                        quad[3].color = sf::Color::Blue; 
                    }
                }
                
            }
        }
        
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const{
        window->setView(sf::View(cells.getBounds()));
        target.draw(cells, states);
    }
    sf::VertexArray cells;
    sf::RenderWindow* window;
    sf::View view;
    int size;
    int ** points;
};