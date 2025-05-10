#pragma once
#include <globals/imports.h>

namespace MOUSE {
    inline void MOVE(int dx, int dy) {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dx = dx;
        input.mi.dy = dy;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        input.mi.time = 0;
        input.mi.dwExtraInfo = GetMessageExtraInfo();
        SendInput(1, &input, sizeof(INPUT));
    }

    inline void LeftClick() {
        INPUT input[2] = {};

        // Mouse down
        input[0].type = INPUT_MOUSE;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        // Mouse up
        input[1].type = INPUT_MOUSE;
        input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        SendInput(2, input, sizeof(INPUT));
    }

    inline void MOVE_ABSOLUTE(int x, int y) {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

        input.mi.dx = (x * 65535) / GetSystemMetrics(SM_CXSCREEN);
        input.mi.dy = (y * 65535) / GetSystemMetrics(SM_CYSCREEN);
        SendInput(1, &input, sizeof(INPUT));
    }

    inline void MoveMouseToClosestEnemy(Vector2 target) {
        if (target.x <= 0.0f || target.y <= 0.0f)
            return;

        Vector2 screen_center = {
            static_cast<float>(GetSystemMetrics(SM_CXSCREEN)) / 2.0f,
            static_cast<float>(GetSystemMetrics(SM_CYSCREEN)) / 2.0f
        };

        float delta_x = target.x - screen_center.x;
        float delta_y = target.y - screen_center.y;

        MOVE_ABSOLUTE(static_cast<int>(target.x), static_cast<int>(target.y));
    }
}