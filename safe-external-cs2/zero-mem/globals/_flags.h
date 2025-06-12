#pragma once

namespace _FLAGS_ {
	inline bool m_bEnableCheats = true;
	inline bool m_bRememberME = true;
	inline bool m_bAnimateUI = true;
	inline bool m_bShowText = true;
	inline bool m_bShowWarnings = true;
	inline bool m_bShowConsole = true;
	inline bool m_bAutomaticUpdate = true;
	inline float m_flAnimationSpeed = 1.25f;

	inline int m_iCurrentReadingModeIndex = 1;
	inline const char* m_AvailableReadingModes[] = { "Kernel", "Normal" };

	inline int m_iEndProgramKey = DEFAULT_PANIC_KEY_DESTROY_PROGRAM;
	inline int m_iVisibilityToggleKey = DEFAULT_PANIC_KEY_HIDE_MENU;
	inline int m_iLoadUnloadCheatsKey = DEFAULT_KEY_LOAD_UNLOAD_CHEATS;
}