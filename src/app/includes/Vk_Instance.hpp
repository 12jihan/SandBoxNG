#pragma once

#include <vulkan/vulkan.h>

#include <vector>

#include "Vk_Debugger.hpp"
#include "Vk_Ext_Handler.hpp"

class Vk_Instance {
   private:
    Vk_Debugger _debugger;
    Vk_Ext_Handler _ext_handler;

    VkInstance instance;
    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;

    void _create_instance();
    void _app_info();
    void _create_info();
    bool _check_validation_layer_support();
    void _setup_extensions();
    std::vector<const char*> _get_req_exts();

   public:
    void init();
    void clean();
    VkInstance& get_instance();
    VkResult result = VK_SUCCESS;
    void log_inst_layers();
};