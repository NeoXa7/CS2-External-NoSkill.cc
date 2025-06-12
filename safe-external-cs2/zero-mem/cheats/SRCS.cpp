#include <pch.h>
#include "SRCS.h"

void SRCS::RUN() {
	if (SRCS::m_bEnableSRCS) {
		float APA = LocalPlayer.AimPunchAngle;

		float aimPunch_x = APA;
		float aimPunch_y = mem.Read<float>(LocalPlayer.C_CSPlayerPawn + APA + 0x4);

		if (LocalPlayer.ShotsFired > 1)
		{
			auto delta_x = (aimPunch_x - SRCS::m_flOldPunchAngleX) * -1.0f;
			auto delta_y = (aimPunch_y - SRCS::m_flOldPunchAngleY) * -1.0f;

			auto mouse_x = static_cast<int>((delta_y * SRCS::m_flYAW / LocalPlayer.MouseSensitivity) / -0.022f);
			auto mouse_y = static_cast<int>((delta_x * SRCS::m_flPITCH / LocalPlayer.MouseSensitivity) / 0.022f);

			if (SRCS::m_iCurrentSRCSModeIndex == 0) {
				SRCS::m_imSRCSMode = AUTO;
			}
			else if (SRCS::m_iCurrentSRCSModeIndex == 1) {
				SRCS::m_imSRCSMode = HOLD;
			}

			if (SRCS::m_imSRCSMode == HOLD && (GetAsyncKeyState(SRCS::m_iCurrentSRCSKey) & 0x8000)) {
				MOUSE::MOVE(mouse_x, mouse_y);
			}
			else if (SRCS::m_imSRCSMode == AUTO) {
				MOUSE::MOVE(mouse_x, mouse_y);
			}

			SRCS::m_flOldPunchAngleX = aimPunch_x;
			SRCS::m_flOldPunchAngleY = aimPunch_y;
		}
		else
		{
			SRCS::m_flOldPunchAngleX = aimPunch_x;
			SRCS::m_flOldPunchAngleY = aimPunch_y;
		}
	}
}