#include "SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation(SDL_Renderer* renderer) : renderer(renderer), spritesheet(nullptr) {}

SpriteAnimation::~SpriteAnimation() {
    if (spritesheet) {
        SDL_DestroyTexture(spritesheet);
    }
}

bool SpriteAnimation::loadSpritesheet(const std::string& path) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) return false;

    spritesheet = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return spritesheet != nullptr;
}

void SpriteAnimation::addAnimation(const std::string& name, const std::vector<Frame>& frames, bool looping) {
    animations[name] = Animation{name, frames, looping};
}

void SpriteAnimation::play(const std::string& name) {
    if (currentAnimation != name) {
        currentAnimation = name;
        currentFrame = 0;
        currentTime = 0.0f;
    }
}

void SpriteAnimation::update(float deltaTime) {
    if (animations.empty() || currentAnimation.empty()) return;

    auto& anim = animations[currentAnimation];
    currentTime += deltaTime * anim.speed;

    while (currentTime >= anim.frames[currentFrame].duration) {
        currentTime -= anim.frames[currentFrame].duration;
        currentFrame++;

        if (currentFrame >= anim.frames.size()) {
            if (anim.looping) {
                currentFrame = 0;
            } else {
                currentFrame = anim.frames.size() - 1;
                break;
            }
        }
    }
}

void SpriteAnimation::render() {
    if (animations.empty() || currentAnimation.empty()) return;

    auto& anim = animations[currentAnimation];
    const auto& frame = anim.frames[currentFrame];

    SDL_FRect destRect{
        position.x,
        position.y,
        frame.sourceRect.w * scale.x,
        frame.sourceRect.h * scale.y
    };

    SDL_RenderCopyExF(
        renderer,
        spritesheet,
        &frame.sourceRect,
        &destRect,
        0.0,              // rotation angle
        nullptr,          // rotation center
        flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
}

void SpriteAnimation::setPosition(float x, float y) {
    position = {x, y};
}

void SpriteAnimation::setScale(float x, float y) {
    scale = {x, y};
}

void SpriteAnimation::setFlip(bool flip) {
    flipped = flip;
}