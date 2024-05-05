#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "./includes/Game.hpp"
#include "GLFW/glfw3.h"

int main() {
    Game engine;

    try {
        engine.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}