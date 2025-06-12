#pragma once
#include "globals/imports.h"
#include <utils/functions.h>
#include <sdk/maths/vector.h>
#include <KDZero/kmemory.h>
#include <KDZero/kprocess.h>
#include <libs/xorstr.h>

#define BASE_DIRECTORY "bin"
#define CONFIG_FILE_EXTENSION ".ini"
#define SETTINGS_FILE_EXTENSION ".ini"
#define SOUND_FILE_EXTENSION ".wav"

#define EXIT exit(0)
#define DEFAULT_PANIC_KEY_DESTROY_PROGRAM VK_END
#define DEFAULT_PANIC_KEY_HIDE_MENU	VK_INSERT
#define DEFAULT_KEY_LOAD_UNLOAD_CHEATS VK_HOME

#define MAX_BUFFER_SIZE		120
#define GAME_METRIC_UNITS	100
#define M_PI				3.14159265358979323846 
#define NULL_FLOAT			0.0f

#define SCREEN_WIDTH	 GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT	 GetSystemMetrics(SM_CYSCREEN)
#define SCREEN_TOP_X     (static_cast<float>(SCREEN_WIDTH) / 2.0f)
#define SCREEN_TOP_Y     (NULL_FLOAT)
#define SCREEN_CENTER_X  (static_cast<float>(SCREEN_WIDTH) / 2.0f)
#define SCREEN_CENTER_Y  (static_cast<float>(SCREEN_HEIGHT) / 2.0f)
#define SCREEN_BOTTOM_X  (static_cast<float>(SCREEN_WIDTH) / 2.0f)
#define SCREEN_BOTTOM_Y  (static_cast<float>(SCREEN_HEIGHT))

#define I_CLOSE		"\xef\x80\x8d"	// U+F00D
#define I_MINIMIZE	"\xef\x81\xa8"	// U+F068
#define I_AIM		"\xef\x81\x9b"	// U+F05B
#define I_VISUALS	"\xef\x83\x80"	// U+F0C0
#define I_SETTINGS	"\xef\x82\x85"	// U+F085
#define I_LIST		"\xef\x83\x89"	// U+F0C9
#define I_SERVER	"\xef\x84\xa0"	// U+F120

#define PROTECT xorstr_
						   
inline KDZERO_MEMORY_MANAGER mem(xorstr_("cs2.exe"));