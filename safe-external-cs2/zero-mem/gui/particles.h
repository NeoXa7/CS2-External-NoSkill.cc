#include <globals/imports.h>

//
//
//  thanks CHAT-GPT :)
//  for the particle system .............
//
//

// Star particle
struct ParticleData {
    ImVec2 rel_pos;       // Relative to window
    ImVec2 jitter_offset; // Animated offset
};

inline void SeedRand() {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }
}

class Particles {
public:
    void DrawRandomConstellationParticles(int particleCount = 200, float maxDist = 50.0f, float jitterAmount = 2.5f) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) return;

        SeedRand();

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 win_pos = window->Pos;
        ImVec2 win_size = window->Size;

        static std::vector<ParticleData> particles;
        static ImVec2 last_size;

        // Initialize or resize particle list
        if (particles.empty() || particles.size() != particleCount || win_size.x != last_size.x || win_size.y != last_size.y) {
            particles.clear();
            for (int i = 0; i < particleCount; ++i) {
                float x = ((float)(rand() % 10000) / 10000.0f);
                float y = ((float)(rand() % 10000) / 10000.0f);
                particles.push_back({ ImVec2(x, y), ImVec2(0, 0) });
            }
            last_size = win_size;
        }

        float t = ImGui::GetTime();

        std::vector<ImVec2> abs_positions;
        abs_positions.reserve(particles.size());

        for (int i = 0; i < particles.size(); ++i) {
            ParticleData& p = particles[i];

            // Simple animated jitter
            p.jitter_offset.x = sin(t * 2.f + i) * jitterAmount;
            p.jitter_offset.y = cos(t * 2.f + i * 0.5f) * jitterAmount;

            ImVec2 abs = ImVec2(
                win_pos.x + p.rel_pos.x * win_size.x + p.jitter_offset.x,
                win_pos.y + p.rel_pos.y * win_size.y + p.jitter_offset.y
            );
            abs_positions.push_back(abs);
        }

        // Draw soft lines between close particles
        for (size_t i = 0; i < abs_positions.size(); ++i) {
            for (size_t j = i + 1; j < abs_positions.size(); ++j) {
                float dx = abs_positions[i].x - abs_positions[j].x;
                float dy = abs_positions[i].y - abs_positions[j].y;
                float dist_sq = dx * dx + dy * dy;

                if (dist_sq < maxDist * maxDist) {
                    float dist = sqrtf(dist_sq);
                    float alpha = 1.0f - (dist / maxDist);
                    ImU32 line_col = IM_COL32(205, 13, 117, (int)(alpha * 100));
                    draw_list->AddLine(abs_positions[i], abs_positions[j], line_col);
                }
            }
        }

        // Draw particles (glow + center)
        for (auto& pos : abs_positions) {
            draw_list->AddCircleFilled(pos, 4.f, IM_COL32(205, 13, 117, 40));   // soft glow
            draw_list->AddCircleFilled(pos, 2.f, IM_COL32(205, 13, 117, 200));  // core
        }
    }
};