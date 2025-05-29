#include <pch.h>
#include "functions.h"

namespace Utils
{
	namespace Functions
	{
		int GetRefreshRate() {
			DEVMODE devMode = {};
			devMode.dmSize = sizeof(DEVMODE);

			if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode)) {
				return devMode.dmDisplayFrequency;
			}
			else {
				std::cerr << "Failed to get display settings.\n";
				return 0;
			}
		}

	}
}