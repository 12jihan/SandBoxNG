#include "./includes/Vk_Validation_Layer_Handler.hpp"

#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>
// #include <cstdint>

const std::vector<const char*> inst_val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

bool Vk_Validation_Layer_Handler::check_instance_validation_layers_support() {
    uint32_t _count;
    vkEnumerateInstanceLayerProperties(&_count, nullptr);

    std::vector<VkLayerProperties> avail_layers(_count);
    vkEnumerateInstanceLayerProperties(&_count, avail_layers.data());

    std::cout << "|-------------------|" << std::endl;
    std::cout << "|  Instance Layers  |" << std::endl;
    std::cout << "|-------------------|" << std::endl;
    for (const char* layer_name : inst_val_layers) {
        std::cout << "\t- " << layer_name << std::endl;
        bool layer_found = false;
        for (const auto& layer_props : avail_layers) {
            if (strcmp(layer_name, layer_props.layerName)) {
                layer_found = true;
                break;
            }
        }

        if (!layer_found) {
            return false;
        }
    }
    std::cout << "|-------------------|" << std::endl;
    return true;
}

void Vk_Validation_Layer_Handler::get_device_validation_layers(VkPhysicalDevice physical_device) {
    uint32_t _count = 0;
    vkEnumerateDeviceLayerProperties(physical_device, &_count, nullptr);

    std::vector<VkLayerProperties> avail_layers(_count);
    vkEnumerateDeviceLayerProperties(physical_device, &_count, avail_layers.data());

    std::cout << "|-------------------|" << std::endl;
    std::cout << "|   Device Layers   |" << std::endl;
    std::cout << "|-------------------|" << std::endl;
    for (auto layer : avail_layers) {
        std::cout << "\t- " << layer.layerName << ":" << std::endl;
        std::cout << "\t- " << layer.description << std::endl;
    };
    std::cout << "|-------------------|" << std::endl;
}

