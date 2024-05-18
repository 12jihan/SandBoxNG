#pragma once
#include <GLFW/glfw3.h>

#include "./VulkanManager.hpp"
#include "./WindowManager.hpp"

class Game {
   public:
    void run();
    void init();
    void loop();
    void clean();

   private:
    WindowManager window;
    VulkanManager vk_manager;
};