#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class Vk_Instance {
   public:
    void init();
    void clean();
    VkResult result = VK_SUCCESS;

   private:
    VkInstance instance;
    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;

    void _create_instance();
    void _app_info();
    void _create_info();

    std::vector<const char*> _get_req_exts();
};