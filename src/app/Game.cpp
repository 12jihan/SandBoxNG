#include "./includes/Game.hpp"

#include <iostream>

#include "./includes/Vk_Manager.hpp"
#include "./includes/WindowManager.hpp"

void Game::run() {
    init();
    loop();
    clean();
}

void Game::init() {
    window.init();
    vk_manager.init(window);
}

void Game::loop() {
    while (!glfwWindowShouldClose(window.get_window())) {
        window.poll_events();
    }
}

void Game::clean() {
    vk_manager.clean();
    window.clean();
}