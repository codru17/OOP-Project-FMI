cmake_minimum_required(VERSION 3.24)

project(game2d LANGUAGES CXX)

# SFML 3 needs C++17; no compiler-specific extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# SFML 3 (graphics / window / audio) downloaded and built automatically.
# First configure needs internet and takes a few minutes; later builds reuse it.
# ---------------------------------------------------------------------------
include(FetchContent)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)          # static libs -> no DLLs to copy next to the .exe
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)         # networking not needed for a platformer
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)                                             # SYSTEM = our warnings flags don't apply to SFML headers
FetchContent_MakeAvailable(SFML)

# ---------------------------------------------------------------------------
# Our executable: every .cpp under src/ (engine/ + game/ + main.cpp)
# ---------------------------------------------------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(game2d ${SOURCES}
        include/engine/LevelLoadError.h
        include/engine/EntityFactory.h
        include/game/GameEntityFactory.h
        src/game/GameEntityFactory.cpp
        src/game/GameEntityFactory.cpp
        src/game/GameEntityFactory.cpp)

# Lets code include headers as "engine/Scene.h" instead of relative paths
target_include_directories(game2d PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(game2d PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

# Extra warnings help catch mistakes early
if(MSVC)
    target_compile_options(game2d PRIVATE /W4)
else()
    target_compile_options(game2d PRIVATE -Wall -Wextra -Wpedantic)
    # MinGW: link the C++ runtime statically so the .exe runs outside the dev terminal
    if(MINGW)
        target_link_options(game2d PRIVATE -static-libgcc -static-libstdc++)
    endif()
endif()

# Copy assets/ next to the executable on EVERY build (not only when the .exe is relinked),
# so editing only a level file (e.g. assets/levels/level1.txt) is picked up after Ctrl+F9
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:game2d>/assets
    COMMENT "Copying assets/ next to the executable")
add_dependencies(game2d copy_assets)
