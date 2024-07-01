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

// const std::vector<const char*> exts = {
//     VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
// };

void Vk_Instance::init() {
    _setup_extensions();
    log_inst_layers();
    _create_instance();
}

void Vk_Instance::_setup_extensions() {
    _ext_handler.add_ext(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
};

void Vk_Instance::_create_instance() {
    bool _layer_support =  !_val_handler.check_validation_layers_support();
    if (enable_validation && _layer_support) {
        throw new std::runtime_error("Validation layers requested, but not available!");
    }
    _ext_handler.init(enable_validation);
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
    auto _exts = _ext_handler._get_required_exts();
    create_info.enabledExtensionCount = static_cast<uint32_t>(_exts.size());

    create_info.ppEnabledExtensionNames = _exts.data();
    VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};

    if (enable_validation) {
        create_info.enabledLayerCount = static_cast<uint32_t>(val_layers.size());
        create_info.ppEnabledLayerNames = val_layers.data();

        _debugger.pop_debug_msgr_create_info(debug_create_info);
        create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
    } else {
        create_info.enabledLayerCount = 0;
        create_info.pNext = nullptr;
    }

    VkResult result = vkCreateInstance(&create_info, nullptr, &instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!\n\t- Error Code: " + std::to_string(result));
    }
}

void Vk_Instance::clean() {
    vkDestroyInstance(instance, nullptr);
}

VkInstance& Vk_Instance::get_instance() {
    return instance;
}

//** For testing purposes - start

void Vk_Instance::log_inst_layers() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    std::vector<VkLayerProperties> layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, layers.data());

    std::cout << "|---------------------------|" << std::endl;
    std::cout << "| Available Instance Layers |" << std::endl;
    std::cout << "|---------------------------|\n"
              << std::endl;
    for (const auto& layer : layers) {
        std::cout << "\t- " << layer.layerName << ":" << std::endl;
        std::cout << "\t\t- " << layer.description << "\n"
                  << std::endl;
    }
    std::cout << "|---------------------------|" << std::endl;
}

//** For testing purposes - end