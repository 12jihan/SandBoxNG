#include "./includes/WindowManager.hpp"

WindowManager::WindowManager(std::string title, int width, int height) : title("Default title"), width(800), height(600) {
    this->title = title;
    this->width = width;
    this->height = height;
}

void WindowManager::init() {
    if (!glfwInit()) {
        std::invalid_argument("Could not initialize glfw window");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
    }
}

void WindowManager::poll_events() {
    glfwPollEvents();
}

void WindowManager::clean() {
    glfwDestroyWindow(window);
}

// Getters:
GLFWwindow *WindowManager::get_window() const {
    return window;
}

std::string WindowManager::get_title() {
    return title;
}

int WindowManager::get_width() {
    return width;
}

int WindowManager::get_height() {
    return height;
}