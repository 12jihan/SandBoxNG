#pragma once
#include <GLFW/glfw3.h>

#include "./WindowManager.h"

class Game {
   public:
    void run();

   private:
    WindowManager *win_man;
};