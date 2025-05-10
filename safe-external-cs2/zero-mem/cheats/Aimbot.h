#pragma once
#include <sdk/sdk.h>
#include <sdk/defs.h>
#include <utils/mouse.h>
#include <sdk/maths/maths.h>
#include <utils/draw.h>

namespace Aimbot {
	inline bool m_bEnableAimbot = true;
	inline bool m_bEnableHotkey = true;
	inline bool m_bEnableTeamCheck = true;
	inline bool m_bEnableVisibilityCheck = true;
	inline bool m_bFovBased = true;
	inline bool m_bShowFovCircle = true;
	inline bool m_bRandomizeAimPosition = true;

	inline float m_flSmoothness = 2.0f;
	inline float m_flFOV = 60.0f;
	inline float m_flFOVCircleThickness = 2.0f;

	inline ImColor m_clFOVCircleColor = ImColor(255, 255, 255, 255);

	inline int m_iCurrentKEY = VK_LSHIFT;

	inline INPUT_MODE m_imAimbotMode = HOLD;
	inline int m_iCurrentAimbotModeIndex = 1;
	inline const char* m_AvailableAimbotModes[] = { "Auto", "Hold" };

	inline const char* m_AimPositions[] = {
		"HEAD",
		"PELVIS",
		"NECK",
		"CHEST",
		"STOMACH",
		"LSHOULDER",
		"LARM",
		"LHAND",
		"RSHOULDER",
		"RARM",
		"RHAND",
		"LTHIGH",
		"LCALF",
		"LFOOT",
		"RTHIGH",
		"RCALF",
		"RFOOT",
	};
	inline int m_iCurrentAimPosIndex = 0; // HEAD
	inline Vector3 AimPosition3D;

	Vector2 FindClosest(std::vector<CEntity>& list);
	void Move(Vector2 target);
	void RUN(std::vector<CEntity>& list);
}