#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "grid.cpp"
#include "game.cpp"
#include <SFML/System/Clock.hpp>

#include <imgui-SFML.h>
#include <imgui.h>



int main()
{
    bool pause = false;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setFramerateLimit(0);
    ImGui::SFML::Init(window);

    Grid grid(25, 25, &window);
    Game game(25,25, &grid);

    game.Initialize();


    sf::Clock clock;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){


                }
            }

        }

        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Settings");
        ImGui::Checkbox("pause", &pause);
        ImGui::End();


        game.ApplyRules();
        game.Update();

        window.clear();
        window.draw(grid);
        ImGui::SFML::Render(window);
        window.display();
        clock.restart();




    }

    ImGui::SFML::Shutdown();

    return 0;
}