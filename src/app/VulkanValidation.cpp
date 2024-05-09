#include "./includes/VulkanValidation.hpp"

#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

void VulkanValidation::init() {
    check_validation_support();
}

bool VulkanValidation::check_validation_support() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    std::cout << "Layer count: " << layer_count << std::endl;
    std::cout << "Layer count:\n\t " << available_layers.data() << std::endl;

    for (const char* layer_name : validation_layers) {
        bool layer_found = false;

        for (const auto& layer_props : available_layers) {
            if (strcmp(layer_name, layer_props.layerName) == 0) {
                layer_found = true;
                break;
            }
        }

        if (!layer_found) {
            return false;
        }
    }

    return true;
}