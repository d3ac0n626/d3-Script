#pragma once
#include "common.hpp"

using Callback = std::function<void()>;

namespace Utils {
    void Error(const std::string& s);

    bool EndsWith(const std::string& haystack, const std::string& needle);

    std::vector<std::string> GetFilesInDirectory(const char* directory);
    std::vector<std::string> SplitString(std::string str, const char* delimiter);
}
