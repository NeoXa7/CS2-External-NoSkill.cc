#pragma once
#include <globals/imports.h>
#include <sdk/sdk.h>

namespace Utils
{
	namespace Draw
	{
        // Draw Border Box
        void Rectangle(
            const Vector2& position,
            const Vector2& size,
            float thickness = 2.0f,
            float rounding = 0.0f,
            ImColor color = ImColor(255, 255, 255, 255)
        );

        inline void ImageRectangle(ImTextureID image_id, const Vector2& position, const Vector2& size)
        {
            ImGui::GetBackgroundDrawList()->AddImage(image_id, position.ToImVec2(), { position.x + size.x,position.y + size.y });
        }

        // Draw Filled Box
        void FilledRectangle(
            const Vector2& position,
            const Vector2& size,
            float borderThickness = 2.0f,
            float rounding = 0.0f,
            ImColor fillColor = ImColor(255, 0, 0, 128),
            ImColor borderColor = ImColor(255, 255, 255, 255)
        );

        // Draw Line
        void Line(
            const Vector2& from,
            const Vector2& to,
            float thickness = 1.0f,
            ImColor color = ImColor(255, 255, 255, 255)
        );
        
        // Draw Line with an end point
        void LineWithPoint(
            const Vector2& from,
            const Vector2& to,
            float thickness = 1.0f,
            float point_radius = 3.0f,
            ImColor color = ImColor(255, 255, 255, 255),
            ImColor point_color = ImColor(255, 255, 255, 255)
        );

        // Draw arrow
        void Arrow(
            const Vector2& from,
            const Vector2& to,
            float base_point_radius,
            float line_thickness,
            float base_arrow_size,
            ImColor line_color = ImColor(255, 255, 255),
            ImColor point_color = ImColor(10, 10, 10),
            ImColor arrow_color = ImColor(10, 10, 10)
        );

        // Draw Horizontal Healthbar
        void HorizontalBar(
            const Vector2& top_left,
            const Vector2& bottom_right,
            bool upward,
            int health,
            float health_bar_height,
            float offset,
            ImColor health_fill_color
        );

        // Draw Vertical Healthbar
        void VerticalBar(
            const Vector2& top_left,
            const Vector2& bottom_right,
            int health,
            float health_bar_width = 2.0f, 
            float offset = 6.0f,
            ImColor health_fill_color = ImColor(0, 255, 0, 255)
        );

        // Draw Text
        void Text(
            std::string text,
            Vector2 pos,
            float font_size = 15.0f,
            bool keep_center = true,
            ImColor color = ImColor(255, 255, 255, 255)
        );

        // Draw Text with Stroke
        void TextWithStroke(
            const std::string& text,
            Vector2 position,
            float stroke_thickness = 1.0f,
            ImColor text_color = ImColor(255, 255, 255, 255),
            ImColor stroke_color = ImColor(0, 0, 0, 255)
        );

        // Draw Circle
        void Circle(
            float x,
            float y,
            float radius,
            float thickness = 1.0f,
            int segments = 0,
            ImColor color = ImColor(255, 255, 255, 255)
        );

        // Draw filled Circle
        void CircleFilled(
            float x,
            float y,
            float radius,
            ImColor color = ImColor(255, 255, 255, 255)
        );

        namespace CSGO {
            void EyeRay(
                CEntity& entities,
                float line_length,
                float point_radius = 5.0f,
                float line_thickness = 2.0f,
                float arrow_size = 12.0f,
                ImColor line_color = ImColor(255, 255, 255),
                ImColor point_color = ImColor(10, 10, 10),
                ImColor arrow_color = ImColor(10, 10, 10)
            );

            void Bones(
                CEntity& entities,
                float BoneThickness = 2.0f,
                bool Head = false,
                bool HeadFilled = false, 
                bool ShowBoneJoints = false,
                float JointRadius = 2.0f, 
                ImColor BoneColor = ImColor(255, 255, 255),
                ImColor HeadBoneColor = ImColor(255, 255, 255),
                ImColor BoneJointsColor = ImColor(255, 255, 255)
            );
        }
	}
}