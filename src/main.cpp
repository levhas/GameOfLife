#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "grid.cpp"
#include "game.cpp"
#include <SFML/System/Clock.hpp>
#include <sstream>
#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/spdlog.h>




int main()
{
    sf::Clock clock;


    bool pause = false;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setFramerateLimit(0);
    ImGui::SFML::Init(window);

    Grid grid(200, 200, &window);
    Game game(200, 200, &grid);
    int gen = 0;
    game.Initialize();
    int spinner[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int testgrid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //game.set_values(testgrid, 10, 10);
    sf::Time frame_start = clock.getElapsedTime();

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






        ImGui::SFML::Update(window,frame_start);

        ImGui::Begin("Info");
        game.ApplyRules();
        game.Update();

        ImGui::Text("gen: %i",gen++);
        ImGui::Text("average gen/sec: %f",gen/frame_start.asSeconds());
        ImGui::Text("fps: %f",1/(clock.getElapsedTime().asSeconds()-frame_start.asSeconds()));

        if(ImGui::Button("save log")){
            spdlog::info("average gen/sec, {}!", gen/frame_start.asSeconds());

        }

        frame_start = clock.getElapsedTime();
        ImGui::Checkbox("pause", &pause);
        ImGui::End();
        window.clear();
        window.draw(grid);
        ImGui::SFML::Render(window);
        window.display();





    }

    ImGui::SFML::Shutdown();

    return 0;
}
