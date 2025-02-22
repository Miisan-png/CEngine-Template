#pragma once
#include "../Game/scripts/SpriteAnimation.hpp"
#include <imgui.h>
#include <vector>

class SpriteAnimationEditor {
private:
    SpriteAnimation* target = nullptr;
    SDL_Texture* previewTexture = nullptr;
    std::string selectedAnimation;
    
    // Editor state
    int frameWidth = 32;
    int frameHeight = 32;
    int spacing = 0;
    int margin = 0;
    float frameDuration = 0.1f;
    bool autoSlice = true;
    
    struct EditorFrame {
        SDL_Rect rect;
        float duration;
        bool selected = false;
    };
    
    std::vector<EditorFrame> editorFrames;
    void autoSliceFrames();

public:
    void setTarget(SpriteAnimation* animation) { target = animation; }
    void draw();
};