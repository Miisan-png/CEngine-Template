#pragma once
#include <SDL.h>
#include <imgui.h>
#include <memory>

class Game {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    ImGuiIO* io = nullptr;
    bool isRunning = true;

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

    void _ready();        // Called when game starts
    void _process();      // Called every frame for non-physics updates
    void _physicsProcess(); // Called every physics frame
    void _input();        // Called when input events occur
    void _draw();         // Called when it's time to draw

    void run();           // Main game loop
    SDL_Renderer* getRenderer() const { return renderer; }
};