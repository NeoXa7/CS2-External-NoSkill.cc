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
	}
}