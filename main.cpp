#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "grid.cpp"
#include "game.cpp"




int main()
{
   
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    
    
    
    Grid grid(100, &window);
    Game game(100, &grid);

    
    
   
    sf::Clock clock;
    while (window.isOpen())
    {
        std::cout << " 1\n";
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    

                }
            }
             
        }
    
        
        game.ApplyRules();
        game.Update();
        window.clear();
        window.draw(grid);
        window.display();
        clock.restart();  
        
       
        
        
    }

    

    return 0;
}