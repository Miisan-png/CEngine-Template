#include "SpriteAnimationEditor.hpp"

void SpriteAnimationEditor::autoSliceFrames() {
    editorFrames.clear();
    
    int textureW, textureH;
    SDL_QueryTexture(previewTexture, nullptr, nullptr, &textureW, &textureH);
    
    for (int y = margin; y + frameHeight <= textureH; y += frameHeight + spacing) {
        for (int x = margin; x + frameWidth <= textureW; x += frameWidth + spacing) {
            EditorFrame frame;
            frame.rect = {x, y, frameWidth, frameHeight};
            frame.duration = frameDuration;
            editorFrames.push_back(frame);
        }
    }
}

void SpriteAnimationEditor::draw() {
    if (!target) return;

    ImGui::Begin("Sprite Animation Editor");
    
    if (ImGui::CollapsingHeader("Grid Settings")) {
        ImGui::InputInt("Frame Width", &frameWidth);
        ImGui::InputInt("Frame Height", &frameHeight);
        ImGui::InputInt("Spacing", &spacing);
        ImGui::InputInt("Margin", &margin);
        ImGui::InputFloat("Default Duration", &frameDuration, 0.01f, 0.1f);
        
        if (ImGui::Button("Auto Slice")) {
            autoSliceFrames();
        }
    }

    if (ImGui::CollapsingHeader("Animations")) {
        if (ImGui::Button("New Animation")) {
            ImGui::OpenPopup("New Animation");
        }

        if (ImGui::BeginPopup("New Animation")) {
            static char animName[32] = "";
            ImGui::InputText("Name", animName, 32);
            
            if (ImGui::Button("Create")) {
                if (strlen(animName) > 0) {
                    std::vector<Frame> frames;
                    for (const auto& ef : editorFrames) {
                        if (ef.selected) {
                            frames.push_back({ef.rect, ef.duration});
                        }
                    }
                    target->addAnimation(animName, frames);
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::EndPopup();
        }
    }

    if (ImGui::CollapsingHeader("Frames")) {
        ImGui::BeginChild("FrameGrid", ImVec2(0, 200), true);
        float cellSize = 64.0f;
        
        for (size_t i = 0; i < editorFrames.size(); i++) {
            auto& frame = editorFrames[i];
            
            ImGui::PushID(static_cast<int>(i));
            if (i > 0) ImGui::SameLine();
            
            ImGui::BeginGroup();
            if (ImGui::Selectable("##frame", frame.selected, 0, ImVec2(cellSize, cellSize))) {
                frame.selected = !frame.selected;
            }
            
            ImGui::Text("Frame %zu", i);
            ImGui::EndGroup();
            ImGui::PopID();
            
            if ((i + 1) % 5 == 0) ImGui::NewLine();
        }
        ImGui::EndChild();
    }

    ImGui::End();
}