#include <vulkan/vulkan.h>

#include <vector>

class Vk_Validation_Layer_Handler {
   private:
    uint32_t _count = 0;

   public:
    bool check_instance_validation_layers_support();
    void get_device_validation_layers(VkPhysicalDevice physical_device);
    void add_layer(const char* layer_name);
};