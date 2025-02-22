#pragma once
#include <SDL.h>
#include <imgui.h>
#include <memory>
#include "scripts/Player.hpp"
#include "../Editor/SpriteAnimationEditor.hpp"

class Game {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    ImGuiIO* io = nullptr;
    bool isRunning = true;

    std::unique_ptr<Player> player;
    std::unique_ptr<SpriteAnimationEditor> editor;
    
    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;
    float targetFrameRate = 60.0f;
    float frameDelay = 1000.0f / targetFrameRate;

    // Initialize systems
    void initSDL();
    void initImGui();
    void handleInput();
    void cleanup();

public:
    Game();
    ~Game();

    // godot inispried

    void _ready();        // Called when game starts
    void _process();      // Called every frame for non-physics updates
    void _physicsProcess(); // Called every physics frame
    void _input();        // Called when input events occur
    void _draw();         // Called when it's time to draw

    void run();           // Main game loop
    SDL_Renderer* getRenderer() const { return renderer; }
};