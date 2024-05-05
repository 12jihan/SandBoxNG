#include "./includes/WindowManager.hpp"

WindowManager::WindowManager(std::string title, int width, int height) : m_title("Default title"), width(800), height(600), m_window(nullptr) {}

void WindowManager::init() {
    std::cout << "WindowManager initializing..." << std::endl;
    if (!glfwInit()) {
        std::cerr << "Could not initialize glfw window";
        std::exit(EXIT_FAILURE);
    }
    window_hints();
    create_window(m_title, width, height);
    context_current(m_window);
}

void WindowManager::create_window(std::string title, int width, int height) {
    std::cout << "Window addr: " << &m_window << std::endl;
    m_window = glfwCreateWindow(width, height, "looooool", NULL, NULL);
    if (!glfwInit())
        throw std::runtime_error("GLFW failed to initialize.");
    glfwMakeContextCurrent(m_window);
}

void WindowManager::context_current(GLFWwindow* win) {
    glfwMakeContextCurrent(win);
}

void WindowManager::window_hints() {
    std::cout << "window hints set" << std::endl;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void WindowManager::poll_events() {
    glfwPollEvents();
}

void WindowManager::clean() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

GLFWwindow* WindowManager::get_window() const {
    return m_window;
}

std::string WindowManager::get_title() {
    return m_title;
}

int WindowManager::get_width() {
    return width;
}

int WindowManager::get_height() {
    return height;
}