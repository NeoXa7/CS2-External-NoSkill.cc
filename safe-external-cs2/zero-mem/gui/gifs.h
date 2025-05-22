#pragma once
#include <globals/imports.h>

struct GIFInstance {
    std::vector<ID3D11ShaderResourceView*> frames;
    std::vector<float> delays;

    int currentFrame = 0;
    float frameTime = 0.0f;

    void Update(float deltaTime) {
        if (frames.empty()) return;

        frameTime += deltaTime;
        if (frameTime >= delays[currentFrame]) {
            frameTime -= delays[currentFrame];  // subtract instead of reset
            currentFrame = (currentFrame + 1) % frames.size();
        }
    }


    void Render(ImVec2 size) {
        if (!frames.empty()) {
            ImGui::Image((ImTextureID)frames[currentFrame], size);
        }
    }
};

GIFInstance LoadGif(const unsigned char* bytes, size_t size) {
    GIFInstance instance;

    int width, height, frames, comp;
    int* delays = nullptr;
    unsigned char* frame_data = stbi_load_gif_from_memory(bytes, size, &delays, &width, &height, &frames, &comp, 4);

    for (int i = 0; i < frames; i++) {
        unsigned char* frame = frame_data + (i * width * height * 4);
        auto tex = RES_LOADER::CreateTextureFromMemory(frame, width, height);
        instance.frames.push_back(tex);
        instance.delays.push_back(0.0f);
    }

    stbi_image_free(frame_data);
    return instance;
}
