#include "./includes/Blk_Tools.hpp"

#include <vector>

bool Blk_Tools::vector_contains(const std::vector<const char*>& vec, const char* element) {
    return std::find_if(vec.begin(), vec.end(), [element](const char* str) {
               return std::strcmp(str, element) == 0;
           }) != vec.end();
};