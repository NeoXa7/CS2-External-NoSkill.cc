#pragma once
#include <libs/my_libs/ini.h>
#include <libs/xorstr.h>
#include <globals/defs.h>
#include <globals/_flags.h>


class SettingsManager {
private:
	SIMPLE_INI ini;
	std::string base_directory = std::string(BASE_DIRECTORY) + "\\";

public:
	std::string file_name = base_directory + xorstr_("Settings") + std::string(SETTINGS_FILE_EXTENSION);
	
	void SaveSettings();
	void LoadSettings();

}; inline SettingsManager settings;