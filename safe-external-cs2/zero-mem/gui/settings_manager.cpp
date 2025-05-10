#include "settings_manager.h"

void SettingsManager::SaveSettings() {
	ini._CreateDirectories(base_directory);
	ini._CreateFile(file_name);

	ini.Store<bool>(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bRemember"), _FLAGS_::m_bRememberME);
	ini.Store<bool>(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bAnimateUI"), _FLAGS_::m_bAnimateUI);
	ini.Store<bool>(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bAutomaticUpdate"), _FLAGS_::m_bAutomaticUpdate);
	ini.Store<bool>(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bShowText"), _FLAGS_::m_bShowText);
	ini.Store<float>(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_flAnimationSpeed"), _FLAGS_::m_flAnimationSpeed);

	ini._WriteDataToFile(file_name);
}

void SettingsManager::LoadSettings() {
	if (ini._ReadDataFromFile(file_name)) {
		_FLAGS_::m_bRememberME = ini.GetBool(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bRemember"));
		_FLAGS_::m_bAutomaticUpdate = ini.GetBool(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bAutomaticUpdate"));
		_FLAGS_::m_bAnimateUI = ini.GetBool(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bAnimateUI"));
		_FLAGS_::m_bShowText = ini.GetBool(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_bShowText"));
		_FLAGS_::m_flAnimationSpeed = ini.GetFloat(xorstr_("PROGRAM_RELEASE_X64"), xorstr_("m_flAnimationSpeed"));
	}
}