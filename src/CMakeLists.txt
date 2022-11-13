add_executable(GameOfLife
    main.cpp)

target_link_libraries(GameOfLife PRIVATE ImGui-SFML::ImGui-SFML spdlog::spdlog_header_only)
