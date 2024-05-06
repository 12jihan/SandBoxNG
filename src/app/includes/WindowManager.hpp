#pragma once
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager {
   public:
    WindowManager();

    int get_width();
    int get_height();
    void init();
    void poll_events();
    void clean();

    // implement this crap later:
    std::string get_title();
    GLFWwindow *get_window() const;

   private:
    GLFWwindow *m_window;
    std::string m_title;
    int width;
    int height;

    void create_window(std::string title, int width, int height);
    void context_current(GLFWwindow *win);
    void window_hints();
};