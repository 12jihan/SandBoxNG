#include "./includes/VulkanManager.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>
#include <map>
#include <vector>

// #define NDEBUG

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool is_complete() {
        return graphicsFamily.has_value();
    }
};

void VulkanManager::init() {
    check_ext_support();
    check_validation_layer_support();
    create_instance();
    setup_debug_msgr();
    pick_physical_device();
    create_logical_device();
}

void VulkanManager::create_instance() {
    // Check to see if validation layers are available
    if (enable_validation_layers && !check_validation_layer_support()) {
        throw new std::runtime_error("Validation layers requested, but not available!");
    }
    // Create the application information
    _app_info();
    // Create Instance information
    _create_info();
}

void VulkanManager::clean() {
    vkDestroyDevice(device, nullptr);
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    vkDestroyInstance(instance, nullptr);
}

void VulkanManager::check_ext_support() {
    // Enumeration for the amount of extensions available
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

    // Create a vector to hold the extension types and queries the extensions
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
}

void VulkanManager::_app_info() {
    // Create application information
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext = nullptr;
    app_info.pApplicationName = "SandboxNG";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 3, 0);
    app_info.pEngineName = "Sandbox_NG_VK";
    app_info.engineVersion = VK_MAKE_VERSION(1, 3, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;
}

void VulkanManager::_create_info() {
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;
    // Set macOS compatibility flag

    create_info.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    create_info.pApplicationInfo = &app_info;

    // Get required extensions
    const char* inst_ext = "VK_KHR_get_physical_device_properties2";
    uint32_t glfw_ext_count = 1;
    const char** glfw_exts;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    create_info.enabledExtensionCount = glfw_ext_count;
    create_info.ppEnabledExtensionNames = glfw_exts;

    auto extensions = get_req_exts();
    create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    create_info.ppEnabledExtensionNames = extensions.data();

    // Compatibility required extensions
    VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};
    if (enable_validation_layers) {
        create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        create_info.ppEnabledLayerNames = validation_layers.data();
        pop_debug_msgr_create_info(debug_create_info);
        create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
    } else {
        create_info.enabledLayerCount = 0;
        create_info.pNext = nullptr;
    }

    // result = vkCreateInstance(&create_info, nullptr, &instance);
    if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!\n\t- Error Code: " + std::to_string(result));
    }
}

bool VulkanManager::check_validation_layer_support() {
    // Enumerate layer count
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    // Enumerate available layers
    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, avail_layers.data());

    for (const char* layer_name : validation_layers) {
        bool layer_found = false;

        for (const auto& layer_props : avail_layers) {
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

bool VulkanManager::verify_ext_support() {
    return false;
}

std::vector<const char*> VulkanManager::get_req_exts() {
    uint32_t glfw_ext_count = 0;
    const char** glfw_ext;
    glfw_ext = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    std::vector<const char*> extensions(glfw_ext, glfw_ext + glfw_ext_count);
    extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    // If debugging is enabled, add the debug extension
    if (enable_validation_layers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void VulkanManager::setup_debug_msgr() {
    if (!enable_validation_layers) return;

    VkDebugUtilsMessengerCreateInfoEXT msgr_create_info{};
    pop_debug_msgr_create_info(msgr_create_info);

    if (CreateDebugUtilsMessengerEXT(instance, &msgr_create_info, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void VulkanManager::pop_debug_msgr_create_info(VkDebugUtilsMessengerCreateInfoEXT& msgr_create_info) {
    msgr_create_info = {};
    msgr_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    msgr_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    msgr_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    msgr_create_info.pfnUserCallback = debug_callback;
}

bool VulkanManager::is_device_suitable(VkPhysicalDevice device) {
    VulkanManager::QueueFamilyIndices indices = find_queue_families(device);

    return indices.is_complete();
}

void VulkanManager::pick_physical_device() {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
    if (device_count == 0) throw std::runtime_error("failed to find GPUs with Vulkan support!");
    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

    for (const auto& device : devices) {
        VkPhysicalDeviceProperties device_props;
        VkPhysicalDeviceFeatures device_feats;
        vkGetPhysicalDeviceProperties(device, &device_props);
        vkGetPhysicalDeviceFeatures(device, &device_feats);

        if (is_device_suitable(device)) {
            physical_device = device;
            break;
        }
    }

    if (physical_device == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

VulkanManager::QueueFamilyIndices VulkanManager::find_queue_families(VkPhysicalDevice device) {
    VulkanManager::QueueFamilyIndices indices;
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());
    // Logic to find queue family indices to populate struct with
    int i = 0;
    for (const auto& queue_family : queue_families) {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.is_complete()) {
            break;
        }

        i++;
    }
    return indices;
}

void VulkanManager::create_logical_device() {
    QueueFamilyIndices indices = find_queue_families(physical_device);

    // Specifying the queues to be created
    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = indices.graphicsFamily.value();
    queue_create_info.queueCount = 1;

    // setting the queues priority using floating point numbers
    float queue_priority = 1.0f;
    queue_create_info.pQueuePriorities = &queue_priority;

    // specifying the device features
    VkPhysicalDeviceFeatures device_features{};

    // Create the logical device
    VkDeviceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pQueueCreateInfos = &queue_create_info;
    create_info.queueCreateInfoCount = 1;
    create_info.pEnabledFeatures = &device_features;

    std::vector<const char*> _validation_layers = {
        "VK_KHR_portability_subset",
    };

    // Device extensions
    create_info.enabledExtensionCount = 1;

    if (enable_validation_layers) {
        create_info.enabledLayerCount = static_cast<uint32_t>(_validation_layers.size());
        create_info.ppEnabledLayerNames = _validation_layers.data();
    } else {
        create_info.enabledExtensionCount = 0;
        create_info.ppEnabledLayerNames = nullptr;
    }

    if (vkCreateDevice(physical_device, &create_info, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphics_queue);
}