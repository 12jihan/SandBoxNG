#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class VulkanManager {
   public:
    void init();
    void clean();

   private:
    VkResult result = VK_SUCCESS;
    VkInstance instance;
    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;
    // std::vector<const char*> validation_layers;
    // std::vector<const char*> req_ext;

    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback();
    
    void debug_messenger_callback();
    void create_instance();
    void _app_info();
    void _create_info();
    bool check_validation_layer();
    bool check_validation_support();
    void check_ext_support();
};