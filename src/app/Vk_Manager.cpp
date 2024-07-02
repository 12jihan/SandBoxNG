#include "./includes/Vk_Manager.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>
#include <map>
#include <vector>

#include "./includes/Vk_Debugger.hpp"
#include "./includes/Vk_Device.hpp"
#include "./includes/Vk_Ext_Handler.hpp"
#include "./includes/Vk_Instance.hpp"

// #define NDEBUG

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char *> instance_val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

const std::vector<const char *> instance_exts = {
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

const std::vector<const char *> device_exts = {
    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
};

void Vk_Manager::init(WindowManager &window) {
    _window = window;
    _ext_handler._check_instance_ext_support();
    _instancer.init();
    _debugger.setup_debug_messenger(_instancer.get_instance(), enableValidationLayers);
    _window_surface.init(_instancer.get_instance(), _window.get_window());
    _device.init(_instancer.get_instance(), _window_surface.get_surface(), enableValidationLayers);
    // _ext_handler._check_device_ext_support(_device.get_physical_device());
}

void Vk_Manager::clean() {
    _window_surface.clean();
    _device.clean();
    _debugger.clean(_instancer.get_instance());
    _instancer.clean();
}

void Vk_Manager::get_device_vals() {
    uint32_t layer_count = 0;
    vkEnumerateDeviceLayerProperties(physical_device, &layer_count, nullptr);

    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateDeviceLayerProperties(physical_device, &layer_count, avail_layers.data());

    std::cout << "|----------------------------|" << std::endl;
    std::cout << "|  Device Validation Layers  |" << std::endl;
    std::cout << "|----------------------------|" << std::endl;
    for (auto layer : avail_layers) {
        std::cout << "+\t" << layer.layerName << std::endl;
    }
    std::cout << "|----------------------------|" << std::endl;
}