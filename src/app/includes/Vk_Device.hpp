#pragma once

#include <iostream>
#include <optional>
#include <vector>

class Vk_Device {
   public:
   private:
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool is_complete() {
            return graphicsFamily.has_value();
        }
    };

    void pick_physical_device();
    void create_logical_device();
    void find_queue_family();
};