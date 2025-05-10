#pragma once
#include <sdk/sdk.h>
#include <sdk/defs.h>

namespace MEMORY { // this features will get you fucking banned
	inline bool m_bEnableFlashAlphaOverride = false;
	inline bool m_bEnableFakeBhop = false;
	inline bool m_bEnableCameraFovOverride = false;
	inline bool m_bEnableNoSky = false;

	inline float m_flFlashAlpha = 50.0f;

	inline int m_iDefaultFOV = 90;
	inline int m_iBhopKEY = VK_SPACE;

	inline bool override_fov = true;

	void RUN();
}