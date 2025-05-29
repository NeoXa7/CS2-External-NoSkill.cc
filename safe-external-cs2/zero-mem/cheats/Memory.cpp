#include <pch.h>
#include "Memory.h"

namespace MEMORY {
	void RUN() {
		if (m_bEnableFlashAlphaOverride) {
			mem.Write<float>(LocalPlayer.C_CSPlayerPawn + Offsets::m_flFlashMaxAlpha, m_flFlashAlpha);
		}

		if (m_bEnableFakeBhop) {
			if (GetAsyncKeyState(m_iBhopKEY) & 0x8000) {
				if (LocalPlayer.Flags == S_STANDING) {
					mem.Write<int>(SourceEngine.ClientDll + Offsets::m_iJump, 65537);
					Sleep(10);
					mem.Write<int>(SourceEngine.ClientDll + Offsets::m_iJump, 256);
				}
			}
		}

		if (m_bEnableCameraFovOverride) {
			override_fov = true;
			uint16_t desired_fov = m_iDefaultFOV;
			uint16_t current_fov = mem.Read<uint16_t>(LocalPlayer.pCameraService + Offsets::m_iFOV);

			if (!LocalPlayer.IsScoped) {
				if (current_fov != desired_fov) {
					mem.Write(LocalPlayer.pCameraService + Offsets::m_iFOV, desired_fov);
				}
			}
		}
		else {
			override_fov = false;
		}

		if (!override_fov) {
			mem.Write(LocalPlayer.C_CSPlayerPawn + 0x22D4, true);
		}

		int loops = 0;
		while (true)
		{
			if (loops > 15) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				uintptr_t pEntityList = mem.Read<uintptr_t>(SourceEngine.ClientDll + Offsets::dwEntityList);
				for (size_t i = 64; i < 1024; i++)
				{
					UINT_PTR EntityListEntry = mem.Read<UINT_PTR>(pEntityList + 8LL * ((i & 0x7FFF) >> 9) + 16);
					if (!EntityListEntry)
						continue;

					UINT_PTR Controller = mem.Read<UINT_PTR>(EntityListEntry + 120LL * (i & 0x1FF)); // Item Entity
					if (!Controller)
						continue;

					char type[1024] = {};
					mem.ReadRaw(mem.Read<UINT_PTR>(mem.Read<UINT_PTR>(Controller + 0x10) + 0x20), type, sizeof(type));

					if (strcmp(type, SMOKE_GRENADE_PROJECTILE) == 0) {
						mem.Write<bool>(Controller + C_SmokeGrenadeProjectile::m_bDidSmokeEffect, (MEMORY::m_bEnableSmokeAlphaOverride) ? true : false);

						if (MEMORY::m_bEnableSmokeColorOverride) {
							mem.Write<Vector3>(Controller + C_SmokeGrenadeProjectile::m_vSmokeColor, m_clSmokeColor);
						}
					}

					if (strcmp(type, POST_PROCESSING_VOLUME) == 0) {
						if (MEMORY::m_bExposureOverride) {
							mem.Write<float>(Controller + C_PostProcessingVolume::m_flMinExposure, MEMORY::m_flExposure);
							mem.Write<float>(Controller + C_PostProcessingVolume::m_flMaxExposure, MEMORY::m_flExposure);
						}
					}

					if (strcmp(type, C_ENV_SKY) == 0) {
						if (MEMORY::m_bEnableSkyColorOverride) {
							mem.Write<Vector3>(Controller + C_EnvSky::m_vTintColor, MEMORY::m_clSkyColor);
						}
					}
				}
				loops = 0;
			}

			++loops;
		}
	}
}