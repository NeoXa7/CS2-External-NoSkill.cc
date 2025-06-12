#pragma once
#pragma once
#include <sdk/sdk.h>
#include <utils/process.h>
#include <utils/mouse.h>

namespace AUTOFIRE {
	inline bool m_bEnableAutofire = true;

	inline INPUT_MODE m_imAutoFireMode = HOLD;
	inline int m_iCurrentAutoFireModeIndex = 1;
	inline const char* m_AvailableFireModes[] = { "Auto", "Hold" };

	inline int m_iCurrentAutoFireStateIndex = 1;
	inline const char* m_AvailableAutoFireStates[] = { "Jumping", "Croching", "Standing", };

	inline int m_iCurrentAutoFireKey = VK_LSHIFT;
	inline float m_flAutoFireDelay = NULL_FLOAT;
	inline float m_flAutoFireRate = NULL_FLOAT;

	inline int state = S_INAIR;

	void RUN();
}