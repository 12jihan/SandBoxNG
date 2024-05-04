#pragma once
#include <GLFW/glfw3.h>

#include "./WindowManager.hpp"

class Game {
   public:
    void run();
    void init();
    void loop();
    void clean();

   private:
    WindowManager *window;
};