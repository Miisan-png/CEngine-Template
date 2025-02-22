#pragma once
#include "SpriteAnimation.hpp"
#include <memory>

class Player {
private:
    std::unique_ptr<SpriteAnimation> sprite;
    float x = 0.0f, y = 0.0f;
    float velocityX = 0.0f, velocityY = 0.0f;
    bool grounded = false;

public:
    explicit Player(SDL_Renderer* renderer);
    void update(float deltaTime);
    void render();
    
    // Control methods
    void moveLeft();
    void moveRight();
    void jump();
    void stop();
};