#pragma once
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager {
   public:
    WindowManager(std::string title, int width, int height);
    int get_width();
    int get_height();
    void init();
    void poll_events();
    void run();
    void clean();

    // Getters:
    std::string get_title();
    GLFWwindow *get_window() const;

    // Setters:
    void set_window(GLFWwindow &window);
    void set_title(std::string &title);

    // Destructors:
    ~WindowManager();

   private:
    std::string title;
    int width;
    int height;
    GLFWwindow *window;
};