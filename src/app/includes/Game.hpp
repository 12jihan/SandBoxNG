#pragma once
#include <GLFW/glfw3.h>

#include "./Vk_Manager.hpp"
#include "./WindowManager.hpp"

class Game {
   public:
    void run();
    void init();
    void loop();
    void clean();

   private:
    WindowManager window;
    Vk_Manager vk_manager;
};