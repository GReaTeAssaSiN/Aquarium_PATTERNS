cmake_minimum_required(VERSION 3.20)
project(Aquarium LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Emit compile_commands.json so editors (VS Code C/C++, clangd, etc.)
# can resolve include paths that come from target_include_directories()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SFML installed via Homebrew (brew install sfml)
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Collect all source files under src/ (CONFIGURE_DEPENDS re-globs on reconfigure,
# so newly added .cpp files are picked up without manually editing this list)
file(GLOB_RECURSE AQUARIUM_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(Aquarium
    main.cpp
    ${AQUARIUM_SOURCES}
)

target_include_directories(Aquarium PRIVATE src)

target_link_libraries(Aquarium PRIVATE SFML::Graphics SFML::Window SFML::System)

# Helpful compiler warnings while developing
target_compile_options(Aquarium PRIVATE -Wall -Wextra)
