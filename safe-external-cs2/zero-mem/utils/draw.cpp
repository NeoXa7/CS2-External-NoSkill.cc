#include <pch.h>
#include "draw.h"

namespace Utils
{
	namespace Draw
	{
        void Rectangle(const Vector2& position, const Vector2& size, float thickness, float rounding, ImColor color)
        {
            ImGui::GetBackgroundDrawList()->AddRect(position.ToImVec2(), { position.x + size.x,position.y + size.y }, color, rounding, ImDrawFlags_None, thickness);
        }

        void FilledRectangle(const Vector2& position, const Vector2& size, float border_thickness, float rounding, ImColor fill_color, ImColor border_color)
        {
            ImGui::GetBackgroundDrawList()->AddRectFilled(position.ToImVec2(), { position.x + size.x,position.y + size.y }, fill_color, rounding, ImDrawFlags_None);
            ImGui::GetBackgroundDrawList()->AddRect(position.ToImVec2(), { position.x + size.x,position.y + size.y }, border_color, rounding, ImDrawFlags_None, border_thickness);
        }

        void Line(const Vector2& from, const Vector2& to, float thickness, ImColor color)
        {
            ImGui::GetBackgroundDrawList()->AddLine(from.ToImVec2(), to.ToImVec2(), color, thickness);
        }

        void LineWithPoint(const Vector2& from, const Vector2& to, float thickness, float base_point_radius, ImColor color, ImColor point_color)
        {
            Vector2 dir = to - from;
            float length = dir.Length();
            if (length < 1.0f) return;

            // Inverse scaling: point is bigger when closer, smaller when farther
            float inverse_scale = 1.0f / length;
            float point_radius = std::clamp(inverse_scale * 300.0f, 3.0f, base_point_radius); // 300.0f is an arbitrary scaling constant

            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);
            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), point_radius, point_color);
        }

        void Arrow(const Vector2& from, const Vector2& to, float base_point_radius, float line_thickness, float base_arrow_size, ImColor line_color, ImColor point_color, ImColor arrow_color)
        {
            Vector2 dir = to - from;
            float length = dir.Length();
            if (length < 1.0f) return;

            dir /= length;

            // scaled arrow and point sizes based on distance
            float arrow_size = std::clamp(length * 0.1f, 6.0f, base_arrow_size);
            float point_radius = std::clamp(length * 0.05f, 3.0f, base_point_radius);

            Vector2 arrow_offset = dir * arrow_size;
            Vector2 adjusted_to = to - arrow_offset;

            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(from.x, from.y), point_radius, point_color);
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(adjusted_to.x, adjusted_to.y), line_color, line_thickness);

            // arrow
            Vector2 perp = { -dir.y, dir.x };
            Vector2 tip = to;
            Vector2 left = tip - dir * arrow_size + perp * (arrow_size * 0.5f);
            Vector2 right = tip - dir * arrow_size - perp * (arrow_size * 0.5f);

            ImGui::GetBackgroundDrawList()->AddTriangleFilled(
                ImVec2(tip.x, tip.y),
                ImVec2(left.x, left.y),
                ImVec2(right.x, right.y),
                arrow_color
            );
        }

        void VerticalBar(const Vector2& top_left, const Vector2& bottom_right, int health, float health_bar_width, float offset, ImColor health_fill_color)
        {
            float boxHeight = bottom_right.y - top_left.y;
            float healthHeight = (health / 100.0f) * boxHeight;
            float BGRectThickness = 1.0f;

            ImVec2 borderTopLeft(top_left.x - health_bar_width - offset - BGRectThickness, top_left.y - BGRectThickness);
            ImVec2 borderBottomRight(top_left.x - offset + BGRectThickness, bottom_right.y + BGRectThickness);
            ImColor BGColor = ImColor(10, 10, 10, 175);
            ImGui::GetBackgroundDrawList()->AddRectFilled(borderTopLeft, borderBottomRight, BGColor, 0.0f, ImDrawFlags_None);

            // draw the actual health bar
            ImVec2 healthTopLeft(top_left.x - health_bar_width - offset, bottom_right.y - healthHeight);
            ImVec2 healthBottomRight(top_left.x - offset, bottom_right.y);
            ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, health_fill_color, 0.0f, ImDrawFlags_None);
        }

        void HorizontalBar(const Vector2& top_left, const Vector2& bottom_right, bool upward, int health, float health_bar_height, float offset, ImColor health_fill_color)
        {
            float boxWidth = bottom_right.x - top_left.x;
            float healthWidth = (health / 100.0f) * boxWidth;
            float BGRectThickness = 1.0f;
            ImColor bgColor = ImColor(10, 10, 10, 175);

            // background above the box
            if (upward) {
                ImVec2 bgTopLeft(top_left.x - BGRectThickness, top_left.y - offset - health_bar_height - BGRectThickness);
                ImVec2 bgBottomRight(bottom_right.x + BGRectThickness, top_left.y - offset + BGRectThickness);

                ImGui::GetBackgroundDrawList()->AddRectFilled(bgTopLeft, bgBottomRight, bgColor);

                ImVec2 healthTopLeft(top_left.x, top_left.y - offset - health_bar_height);
                ImVec2 healthBottomRight(top_left.x + healthWidth, top_left.y - offset);
                ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, health_fill_color);
            }
            else {
                ImVec2 bgTopLeft(top_left.x - BGRectThickness, bottom_right.y + offset);
                ImVec2 bgBottomRight(bottom_right.x + BGRectThickness, bottom_right.y + offset + health_bar_height);

                ImGui::GetBackgroundDrawList()->AddRectFilled(bgTopLeft, bgBottomRight, bgColor, 0.0f, ImDrawFlags_None);

                ImVec2 healthTopLeft(top_left.x, bottom_right.y + offset);
                ImVec2 healthBottomRight(top_left.x + healthWidth, bottom_right.y + offset + health_bar_height);
                ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, health_fill_color, 0.0f, ImDrawFlags_None);
            }
        }


        void Text(std::string text, Vector2 pos, float font_size, bool keep_center, ImColor color)
        {
            if (!keep_center)
            {
                ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), font_size, pos.ToImVec2(), color, text.c_str());
            }
            else
            {
                float TextWidth = ImGui::GetFont()->CalcTextSizeA(font_size, FLT_MAX, 0.f, text.c_str()).x;
                ImVec2 Pos_ = { pos.x - TextWidth / 2, pos.y };
                ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), font_size, Pos_, color, text.c_str());
            }
        }

        void TextWithStroke(const std::string& text, Vector2 position, float stroke_thickness, ImColor text_color, ImColor stroke_color)
        {
            ImVec2 pos = ImVec2(position.x, position.y);

            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - stroke_thickness, pos.y), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + stroke_thickness, pos.y), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y - stroke_thickness), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y + stroke_thickness), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - stroke_thickness, pos.y - stroke_thickness), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + stroke_thickness, pos.y - stroke_thickness), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - stroke_thickness, pos.y + stroke_thickness), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + stroke_thickness, pos.y + stroke_thickness), stroke_color, text.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y), text_color, text.c_str());
        }

        void Circle(float x, float y, float radius, float thickness, int segments, ImColor color)
        {
            ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, segments, thickness);
        }

        void CircleFilled(float x, float y, float radius, ImColor color) {
            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, 0);
        }

        namespace CSGO {
            void EyeRay(CEntity& entities, float line_length, float point_radius, float line_thickness, float arrow_size, ImColor line_color, ImColor point_color, ImColor arrow_color)
            {
                Vector3 ChestPosition3D = entities.GetBone3D(CHEST);
                Vector3 delta = entities.HeadPosition3D - ChestPosition3D;
                float yaw = atan2(delta.y, delta.x) * (180.0f / M_PI);
                float pitch = 0.0f;

                Vector3 forward_vector = Maths::AngleToVector({ pitch, yaw, 0 }) * line_length;
                if (forward_vector.IsZero()) return;

                Vector2 StartPosition = entities.HeadPosition2D;
                if (StartPosition.IsZero()) return;

                Vector3 EndPosition = (entities.HeadPosition3D + forward_vector).WorldToScreen(Instance<CGame>::Get().ViewMatrix);
                if (EndPosition.IsZero()) return;

                // draw ray
                Draw::Arrow(StartPosition, EndPosition.ToVector2(), point_radius, line_thickness, arrow_size, line_color, point_color, arrow_color);
            }

            void Bones(CEntity& entities, float BoneThickness, bool Head, bool HeadFilled, bool ShowBoneJoints, float JointRadius, ImColor BoneColor, ImColor HeadBoneColor, ImColor BoneJointsColor)
            {
                if (entities.Position2D.x <= 0 || entities.Position2D.y <= 0 || entities.HeadPosition2D.x <= 0 || entities.HeadPosition2D.y <= 0)
                    return;

                for (DWORD i = 0; i < sizeof(BoneConnectionList::Connections) / sizeof(BoneConnectionList::Connections[0]); i++) {
                    DWORD dwBone1 = BoneConnectionList::Connections[i].bone1;
                    DWORD dwBone2 = BoneConnectionList::Connections[i].bone2;

                    Vector3 m_vecBone1 = mem.Read<Vector3>(entities.pBoneMatrix + dwBone1 * 32);
                    Vector3 m_vecBone2 = mem.Read<Vector3>(entities.pBoneMatrix + dwBone2 * 32);

                    Vector3 Bone1_2D = m_vecBone1.WorldToScreen(Instance<CGame>::Get().ViewMatrix);
                    Vector3 Bone2_2D = m_vecBone2.WorldToScreen(Instance<CGame>::Get().ViewMatrix);

                    if (Bone1_2D.x <= 0 || Bone1_2D.y <= 0 || Bone2_2D.x <= 0 || Bone2_2D.y <= 0) {
                        continue; // Skip drawing if any of the bones are not visible on screen
                    }

                    float Head_Height = (entities.Position2D.y - entities.HeadPosition2D.y) / 8;

                    if (!ShowBoneJoints) {
                        Draw::Line(Bone1_2D.ToVector2(), Bone2_2D.ToVector2(), BoneThickness, BoneColor);
                    }
                    else {
                        Draw::LineWithPoint(Bone1_2D.ToVector2(), Bone2_2D.ToVector2(), BoneThickness, JointRadius, BoneColor, BoneJointsColor);
                    }

                    if (!HeadFilled && Head) {
                        Draw::Circle(entities.HeadPosition2D.x, entities.HeadPosition2D.y, Head_Height, BoneThickness, 0, HeadBoneColor);
                    }
                    else if (Head) {
                        Draw::CircleFilled(entities.HeadPosition2D.x, entities.HeadPosition2D.y, Head_Height, HeadBoneColor);
                    }

                }
            }

        }
	}
}