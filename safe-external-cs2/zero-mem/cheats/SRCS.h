#pragma once
#include <sdk/sdk.h>
#include <sdk/defs.h>
#include <utils/mouse.h>

namespace SRCS {
	inline bool m_bEnableSRCS = true;
	inline INPUT_MODE m_imSRCSMode = AUTO;

	inline int m_iCurrentSRCSKey = VK_LBUTTON;
	inline int m_iCurrentSRCSModeIndex = 0;

	inline const char* m_AvailableModes[] = { "Auto", "Hold" };


	inline float m_flYAW = 2.0f;
	inline float m_flPITCH = 2.0f;
	inline float m_flOldPunchAngleX = NULL_FLOAT;
	inline float m_flOldPunchAngleY = NULL_FLOAT;


	void RUN();
}