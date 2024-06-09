#pragma once

#include <iostream>
#include <vector>

class VulkanValidation {
   public:
    void init();

   private:
    const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};
    bool check_validation_support();
};