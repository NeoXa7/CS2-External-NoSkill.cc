#pragma once
#include <sdk/sdk.h>
#include <sdk/defs.h>
#include <utils/functions.h>
#include <utils/mouse.h>
#include <utils/process.h>
#include <renderer/directx/directX11.h>

namespace TRIGGER_BOT {
	inline std::atomic<bool> m_bEnableTriggerBot = true;
	inline std::atomic<bool> m_bEnableTeamCheck = true;

	inline INPUT_MODE m_imTriggerMode = HOLD;
	inline int m_iCurrentTriggerModeIndex = 1;
	inline const char* m_AvailableFireModes[] = { "Auto", "Hold" };

	inline int m_iCurrentTriggerKey = VK_LSHIFT;
	inline float m_flTriggerDelay = NULL_FLOAT;
	inline float m_flTriggerFireRate = NULL_FLOAT;

	void RUN();
}