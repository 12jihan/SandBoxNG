#pragma once
#include <vulkan/vulkan.h>

#include <string>
#include <vector>

class VulkanManager {
   public:
    void init();
    void clean();

   private:
    const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};
    VkResult result = VK_SUCCESS;
    VkInstance instance;
    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;
    // std::vector<const char*> validation_layers;
    // std::vector<const char*> req_ext;

    void create_instance();
    void _app_info();
    void _create_info();
    void check_ext_support();
    bool check_validation_layer_support();
    bool verify_ext_support();
};