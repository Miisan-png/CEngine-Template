#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct Frame {
    SDL_Rect sourceRect;
    float duration;       // Duration in seconds
};

struct Animation {
    std::string name;
    std::vector<Frame> frames;
    bool looping = true;
    float speed = 1.0f;
};

class SpriteAnimation {
private:
    SDL_Texture* spritesheet;
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimation;
    float currentTime = 0.0f;
    int currentFrame = 0;
    SDL_Renderer* renderer;
    bool flipped = false;
    SDL_FPoint position{0.0f, 0.0f};
    SDL_FPoint scale{1.0f, 1.0f};

public:
    explicit SpriteAnimation(SDL_Renderer* renderer);
    ~SpriteAnimation();
    
    bool loadSpritesheet(const std::string& path);
    void addAnimation(const std::string& name, const std::vector<Frame>& frames, bool looping = true);
    void play(const std::string& name);
    void update(float deltaTime);
    void render();
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void setFlip(bool flip);
};