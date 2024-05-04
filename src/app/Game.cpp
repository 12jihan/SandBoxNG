#include <iostream>
#include "./includes/Game.h"


Game::Game()
{
    std::cout << "Game Constructor" << std::endl;
}

Game::~Game()
{
    std::cout << "Game Destructor" << std::endl;
}

void Game::run()
{
    std::cout << "Running" << std::endl;
}