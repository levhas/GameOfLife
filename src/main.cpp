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
#include <spdlog/sinks/daily_file_sink.h>



int main()
{
    sf::Clock clock;
    auto logger = spdlog::daily_logger_mt("basic_logger", "../logs/log.txt");

    int START_X = 500;
    int START_Y = 500;
    logger->info("Starting size: X {} Y {}",START_X,START_Y);

    logger->enable_backtrace(3);
    logger->set_level(spdlog::level::off);

    bool pause = false;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setFramerateLimit(0);
    ImGui::SFML::Init(window);

    Grid grid(START_X, START_Y, &window);
    Game game(START_X, START_Y, &grid);
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

        if(frame_start.asSeconds() > 30){
            window.close();
        }
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
        logger->debug("average gen/sec: {}",gen/frame_start.asSeconds());
        logger->debug("runtime: {}s", frame_start.asSeconds());

/*         if(ImGui::Button("save log")){

            logger->enable_backtrace(2);

        } */
        frame_start = clock.getElapsedTime();
        ImGui::Checkbox("pause", &pause);
        ImGui::End();
        window.clear();
        window.draw(grid);
        ImGui::SFML::Render(window);
        window.display();





    }
    logger->dump_backtrace();

    ImGui::SFML::Shutdown();

    return 0;
}
