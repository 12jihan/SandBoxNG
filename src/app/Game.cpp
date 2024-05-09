#include "./includes/Game.hpp"

#include <iostream>

#include "./includes/VulkanInstance.hpp"
#include "./includes/VulkanValidation.hpp"
#include "./includes/WindowManager.hpp"

void Game::run() {
    std::cout << "Game Running..." << std::endl;
    init();
    loop();
    clean();
}

void Game::init() {
    window.init();
    vk_instance.init();
    vk_validation.init();
}

void Game::loop() {
    while (!glfwWindowShouldClose(window.get_window())) {
        window.poll_events();
    }
}

void Game::clean() {
    vk_instance.clean();
    window.clean();
}