#include "./includes/Vk_Instance.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

#ifdef NDEBUG
const bool enable_validation = false;
#else
const bool enable_validation = true;
#endif

const std::vector<const char*> val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

const std::vector<const char*> exts = {
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

void Vk_Instance::init() {
    std::cout << "Vk_Instance" << std::endl;
    _create_instance();
}

void Vk_Instance::_create_instance() {
    if (enable_validation && false) {
        throw new std::runtime_error("Validation layers requested, but not available!");
    }

    _app_info();
    _create_info();
}

void Vk_Instance::_app_info() {
    // Handles the creation of app_info object
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Sandbox_NG";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "No Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;
}

void Vk_Instance::_create_info() {
    // Handles creating everything else included with create_info object
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;                                           // Ensure pNext is set to nullptr
    create_info.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;  // Set macOS compatibility flag
    create_info.pApplicationInfo = &app_info;

    // Get required exts and enable them:
    auto _exts = _get_req_exts();
    create_info.enabledExtensionCount = static_cast<uint32_t>(_exts.size());
    create_info.ppEnabledExtensionNames = _exts.data();

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};
    if (enable_validation) {
        create_info.enabledLayerCount = static_cast<uint32_t>(val_layers.size());
        create_info.ppEnabledLayerNames = val_layers.data();
        // _pop_debug_msgr_create_info(debug_create_info);
    }
}

std::vector<const char*> Vk_Instance::_get_req_exts() {
    uint32_t _glfw_ext_count = 0;
    const char** _glfw_exts;
    _glfw_exts = glfwGetRequiredInstanceExtensions(&_glfw_ext_count);

    std::vector<const char*> _exts = exts;
    _exts.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    // Combine GLFW extensions with additional extensions
    std::vector<const char*> _combined_exts(_glfw_exts, _glfw_exts + _glfw_ext_count);
    _combined_exts.insert(_combined_exts.end(), _exts.begin(), _exts.end());

    // If debuggin is enabled, add the debug extension
    if (enable_validation) _combined_exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    //** For testing purposes - start
    std::cout << "\nGetting all required extensions:" << std::endl;
    std::cout << "----------------------" << std::endl;
    for (auto& __ext : _combined_exts) {
        std::cout << __ext << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    //** For testing purposes - end

    // Return the vector of extensions
    return _combined_exts;
}