cmake_minimum_required(VERSION 3.16)
project(C___Game_Engine_Configs)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.1
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${SDL2_SOURCE_DIR}/include
)

target_link_libraries(imgui PUBLIC
        SDL2::SDL2
)

# Source files for the game
set(GAME_SOURCES
        src/main.cpp
        src/Game/Game.cpp
        src/Game/Game.hpp
)

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        src/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Game
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        imgui
)

# Optional: Copy assets if you have any
# file(COPY ${CMAKE_SOURCE_DIR}/src/Game/assets DESTINATION ${CMAKE_BINARY_DIR})