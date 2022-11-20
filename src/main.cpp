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
#include <regex>
namespace ImGui
{   
    // https://stackoverflow.com/a/69046907
    // ImGui::InputText() with std::string
    // Because text input needs dynamic resizing, we need to setup a callback to grow the capacity
    IMGUI_API bool  InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool  InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool  InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
}


int main()
{
    sf::Clock clock;
    auto logger = spdlog::daily_logger_mt("basic_logger", "../logs/log.txt");

    int START_X = 200;
    int START_Y = 200;
    logger->info("Starting size: X {} Y {}",START_X,START_Y);

    logger->enable_backtrace(3);
    logger->set_level(spdlog::level::off);

    bool pause = false;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setFramerateLimit(0);
    ImGui::SFML::Init(window);
    int newSize[2] = {START_X, START_Y};
    Grid grid(START_X, START_Y, &window);
    Game game(START_X, START_Y, &grid);
    int gen = 0;
    game.Initialize();
    int rpen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
                  0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
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
    int glider[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //game.set_values(rpen, 10, 10);
    sf::Time frame_start = clock.getElapsedTime();

            std::string s{"foo"};


    while (window.isOpen())
    {

/*         if(frame_start.asSeconds() > 30){
            window.close();
        } */
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
        bool changed = false;
        ImGui::InputText( "Text", &s);
        
        ImGui::InputInt2("x y", newSize, 0);
        if(ImGui::Button("restart")){
            game.setSize(newSize[0], newSize[1]);
            game.Initialize();
        }

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
