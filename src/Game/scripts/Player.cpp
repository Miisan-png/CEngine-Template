#include "Player.hpp"

Player::Player(SDL_Renderer* renderer) {
    sprite = std::make_unique<SpriteAnimation>(renderer);
    
    sprite->loadSpritesheet("assets/sprites/todd.png");
    
    std::vector<Frame> idleFrames = {
        {{0, 0, 32, 32}, 0.1f},    // Example frame
        {{32, 0, 32, 32}, 0.1f}    // Example frame
    };
    sprite->addAnimation("idle", idleFrames);
    
    sprite->setPosition(100.0f, 100.0f);
    sprite->setScale(2.0f, 2.0f);
}

void Player::update(float deltaTime) {
    // Simple physics
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
    
    sprite->setPosition(x, y);
    sprite->update(deltaTime);
    
    if (velocityX > 0) sprite->setFlip(false);
    else if (velocityX < 0) sprite->setFlip(true);
}

void Player::render() {
    sprite->render();
}

void Player::moveLeft() {
    velocityX = -200.0f;
}

void Player::moveRight() {
    velocityX = 200.0f;
}

void Player::jump() {
    if (grounded) {
        velocityY = -400.0f;
        grounded = false;
    }
}

void Player::stop() {
    velocityX = 0.0f;
}