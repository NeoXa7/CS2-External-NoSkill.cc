#include <pch.h>
#include "Autofire.h"

namespace AUTOFIRE {
	void RUN() {
		if (AUTOFIRE::m_bEnableAutofire && Instance<Process>::Get().InForeground("Counter-Strike 2")) {
			switch (m_iCurrentAutoFireStateIndex) {
			case 0: state = S_INAIR; break;
			case 1: state = S_CROUCHING; break;
			case 2: state = S_STANDING; break;
			default: state = S_INAIR; break;
			}

			if (Instance<CLocalPlayer>::Get().Flags == state) {
				if (AUTOFIRE::m_iCurrentAutoFireModeIndex == 0) {
					AUTOFIRE::m_imAutoFireMode = AUTO;
				}
				else if (AUTOFIRE::m_iCurrentAutoFireModeIndex == 1) {
					AUTOFIRE::m_imAutoFireMode = HOLD;
				}

				if (AUTOFIRE::m_imAutoFireMode == HOLD && (GetAsyncKeyState(AUTOFIRE::m_iCurrentAutoFireKey) & 0x8000)) {
					FireMacro(0.0f, 0.0f);
				}
				else if (AUTOFIRE::m_imAutoFireMode == AUTO) {
					FireMacro(0.0f, 0.0f);
				}
			}
		}
	}
}