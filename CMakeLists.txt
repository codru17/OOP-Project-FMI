cmake_minimum_required(VERSION 3.14)

project(OOP-Project-FMI LANGUAGES CXX)

# Use C++17 everywhere, no compiler-specific extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect every .cpp under src/ (CONFIGURE_DEPENDS re-scans when files are added)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(OOP-Project-FMI ${SOURCES})

# Lets code include headers as "model/Pacient.h" instead of "../../include/model/Pacient.h"
target_include_directories(OOP-Project-FMI PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Extra warnings help catch mistakes early
if(MSVC)
    target_compile_options(OOP-Project-FMI PRIVATE /W4)
else()
    target_compile_options(OOP-Project-FMI PRIVATE -Wall -Wextra -Wpedantic)
endif()
