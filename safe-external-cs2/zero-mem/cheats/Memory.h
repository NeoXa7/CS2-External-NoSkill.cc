#pragma once
#include <sdk/sdk.h>
#include <sdk/defs.h>

namespace MEMORY { // this features will get you fucking banned
	inline std::atomic<bool> m_bEnableFlashAlphaOverride = false;
	inline std::atomic<bool> m_bEnableSmokeAlphaOverride = false;
	inline std::atomic<bool> m_bEnableSmokeColorOverride = false;
	inline std::atomic<bool> m_bEnableSkyColorOverride = false;
	inline std::atomic<bool> m_bEnableCameraFovOverride = false;
	inline std::atomic<bool> m_bExposureOverride = false;
	inline std::atomic<bool> m_bEnableFakeBhop = false;

	inline float m_flFlashAlpha = 50.0f;
	inline float m_flExposure = 0.75f;

	inline int m_iDefaultFOV = 90;
	inline int m_iBhopKEY = VK_SPACE;

	inline Vector3 m_clSkyColor = Vector3(255.f / 255.0f, 246.f / 255.f, 231.f / 255.f);
	inline Vector3 m_clSmokeColor = Vector3(255.f / 255.0f, 246.f / 255.f, 231.f / 255.f);

	inline bool override_fov = true;

	void RUN();
}
