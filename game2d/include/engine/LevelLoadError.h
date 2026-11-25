#pragma once

#include <stdexcept>
#include <string>

class LevelLoadError:public std::runtime_error {
        public:
                LevelLoadError(const std::string& message) : std::runtime_error(message) {}
};

