#include "./includes/Vk_Manager.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>
#include <map>
#include <vector>

#include "./includes/Vk_Debugger.hpp"
#include "./includes/Vk_Instance.hpp"

// #define NDEBUG

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> instance_val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

const std::vector<const char*> instance_exts = {
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

const std::vector<const char*> device_exts = {
    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
};

void Vk_Manager::init() {
    check_ext_support();
    check_validation_layer_support();
    _instancer.init();
    _debugger.setup_debug_messenger(_instancer.get_instance(), enableValidationLayers);
    // setup_debug_msgr();
    pick_physical_device();
    create_logical_device();
}

// void Vk_Manager::create_instance() {
//     // Check to see if validation layers are available
//     if (enable_validation_layers && !check_validation_layer_support()) {
//         throw new std::runtime_error("Validation layers requested, but not available!");
//     }
//     // Create the application information
//     _app_info();
//     // Create Instance information
//     _create_info();
// }

void Vk_Manager::clean() {
    vkDestroyDevice(device, nullptr);
    DestroyDebugUtilsMessengerEXT(_instancer.get_instance(), debugMessenger, nullptr);
    vkDestroyInstance(_instancer.get_instance(), nullptr);
}

void Vk_Manager::check_ext_support() {
    // Enumeration for the amount of extensions available
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

    // Create a vector to hold the extension types and queries the extensions
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
    // Testing to see the vectors that are currently available
    // std::cout << "available extensions:\n " << std::endl;
    // for (auto ext : extensions) {
    //     std::cout << "- \t" << ext.extensionName << std::endl;
    // }
}

void Vk_Manager::_app_info() {
    // Create application information
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext = nullptr;
    app_info.pApplicationName = "SandboxNG";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Sandbox_NG_VK";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;
}

void Vk_Manager::_create_info() {
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;                                           // Ensure pNext is set to nullptr
    create_info.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;  // Set macOS compatibility flag
    create_info.pApplicationInfo = &app_info;

    auto extensions = get_req_exts();
    create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    create_info.ppEnabledExtensionNames = extensions.data();

    // Compatibility required extensions
    VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};
    if (enable_validation_layers) {
        create_info.enabledLayerCount = static_cast<uint32_t>(instance_val_layers.size());
        create_info.ppEnabledLayerNames = instance_val_layers.data();
        // Added the debugger here as well
        _debugger.pop_debug_msgr_create_info(debug_create_info);
        create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
    } else {
        create_info.enabledLayerCount = 0;
        create_info.pNext = nullptr;
    }

    if (vkCreateInstance(&create_info, nullptr, &_instancer.get_instance()) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!\n\t- Error Code: " + std::to_string(result));
    }
}

bool Vk_Manager::check_validation_layer_support() {
    // Enumerate layer count
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    // Enumerate available layers
    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, avail_layers.data());

    for (const char* layer_name : instance_val_layers) {
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

bool Vk_Manager::verify_ext_support() {
    return false;
}

std::vector<const char*> Vk_Manager::get_req_exts() {
    uint32_t glfw_ext_count = 0;
    const char** glfw_exts;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    // std::vector<const char*> extensions(glfw_exts, glfw_exts + glfw_ext_count);
    std::vector<const char*> extensions = instance_exts;
    extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    // Combine GLFW extensions with additional extensions
    std::vector<const char*> combined_extensions(glfw_exts, glfw_exts + glfw_ext_count);
    combined_extensions.insert(combined_extensions.end(), extensions.begin(), extensions.end());

    // If debugging is enabled, add the debug extension
    if (enable_validation_layers) {
        combined_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    // For testing purposes - start
    std::cout << "\nGetting all required extensions:" << std::endl;
    std::cout << "----------------------" << std::endl;
    for (auto& ext : combined_extensions) {
        std::cout << ext << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    // For testing purposes - end

    return combined_extensions;
}   

// void Vk_Manager::setup_debug_msgr() {
//     if (!enable_validation_layers) return;

//     VkDebugUtilsMessengerCreateInfoEXT msgr_create_info{};
//     // Added the debugger here
//     _debugger.pop_debug_msgr_create_info(msgr_create_info);
//     // pop_debug_msgr_create_info(msgr_create_info);

//     if (CreateDebugUtilsMessengerEXT(instance, &msgr_create_info, nullptr, &debugMessenger) != VK_SUCCESS) {
//         throw std::runtime_error("failed to set up debug messenger!");
//     }
// }

// void Vk_Manager::pop_debug_msgr_create_info(VkDebugUtilsMessengerCreateInfoEXT& msgr_create_info) {
//     msgr_create_info = {};
//     msgr_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
//     msgr_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
//     msgr_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
//     msgr_create_info.pfnUserCallback = debug_callback;
// }

bool Vk_Manager::is_device_suitable(VkPhysicalDevice device) {
    Vk_Manager::QueueFamilyIndices indices = find_queue_families(device);

    return indices.is_complete();
}

void Vk_Manager::pick_physical_device() {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(_instancer.get_instance(), &device_count, nullptr);
    if (device_count == 0) throw std::runtime_error("failed to find GPUs with Vulkan support!");
    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(_instancer.get_instance(), &device_count, devices.data());

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

Vk_Manager::QueueFamilyIndices Vk_Manager::find_queue_families(VkPhysicalDevice device) {
    Vk_Manager::QueueFamilyIndices indices;
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

void Vk_Manager::create_logical_device() {
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

    create_info.enabledExtensionCount = static_cast<uint32_t>(device_exts.size());
    create_info.ppEnabledExtensionNames = device_exts.data();

    create_info.pEnabledFeatures = &device_features;

    // const char* device_ext = "VK_KHR_portability_subset";

    // Testing a few things here:
    // get_device_exts();
    // get_device_vals();

    if (enable_validation_layers) {
        create_info.enabledLayerCount = static_cast<uint32_t>(instance_val_layers.size());
        create_info.ppEnabledLayerNames = instance_val_layers.data();
    } else {
        create_info.enabledExtensionCount = 0;
    }

    if (vkCreateDevice(physical_device, &create_info, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphics_queue);
}

bool Vk_Manager::verify_device_ext_support() {
    return false;
}

void Vk_Manager::get_device_exts() {
    // uint32_t ext_count = 0;
    // vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &ext_count, nullptr);

    // std::vector<VkExtensionProperties> avail_exts(ext_count);
    // vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &ext_count, avail_exts.data());
    // VkExtensionProperties portable_ext = {VK_KHR_portability_subset};
    // avail_exts.push_back(portable_ext);

    // std::cout << "device ext:" << std::endl;
    // for (auto ext : avail_exts) {
    //     std::cout << "-\t" << ext.extensionName << std::endl;
    // }
}

void Vk_Manager::get_device_vals() {
    uint32_t layer_count = 0;
    vkEnumerateDeviceLayerProperties(physical_device, &layer_count, nullptr);

    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateDeviceLayerProperties(physical_device, &layer_count, avail_layers.data());

    std::cout << "device layers:" << std::endl;
    for (auto layer : avail_layers) {
        std::cout << "-\t" << layer.layerName << std::endl;
    }
}