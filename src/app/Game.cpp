#include "./includes/Game.hpp"

#include <iostream>

#include "./includes/WindowManager.hpp"
#include "./includes/VulkanInstance.hpp"

void Game::run() {
    std::cout << "Game Running..." << std::endl;
    init();
    loop();
    clean();
}

void Game::init() {
    window.init();
    vk_instance.init();
}

void Game::loop() {
    while (!glfwWindowShouldClose(window.get_window())) {
        std::cout << "Game Looping..." << std::endl;
        window.poll_events();
    }
}

void Game::clean() {
    window.clean();
}