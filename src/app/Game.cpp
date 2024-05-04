#include <iostream>
#include "./includes/Game.h"

void Game::run()
{
    init();
    loop();
    clean();
}

void Game::init()
{
    std::cout << "Game initialized" << std::endl;
};
void Game::loop()
{
    input();
    update();
    render();
};

void Game::input()
{
    keyboard_input();
    mouse_input();
};

void Game::update()
{
    std::cout << "Game updated" << std::endl;
};

void Game::render()
{
    std::cout << "Game rendered" << std::endl;
};

void Game::clean()
{
    std::cout << "Game cleaned" << std::endl;
};
void Game::keyboard_input()
{
    std::cout << "Keyboard input" << std::endl;
};
void Game::mouse_input()
{
    std::cout << "Mouse input" << std::endl;
};