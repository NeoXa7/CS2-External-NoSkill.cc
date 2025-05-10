#pragma once
#include <libs/my_libs/ini.h>
#include <cheats/_import.h>

class ConfigManager {
private:
	SIMPLE_INI ini;
	std::string base_directory = xorstr_("bin\\");
	std::string configs_directory = xorstr_("configs\\");

public:
	ConfigManager() {}
	~ConfigManager() {}

	ConfigManager(const ConfigManager&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;


	std::string file_name = xorstr_("your-file-name");
	std::vector<std::string> ConfigFiles;

public:
	void CreateConfig() {
		ini._CreateDirectories(base_directory + configs_directory);
		ini._CreateFile(base_directory + configs_directory + file_name + CONFIG_FILE_EXTENSION);

		("SAVING DATA");
		{
			// VISUALS
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnablePlayerEsp"), ESP::PLAYER::m_bEnablePlayerEsp);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableBox"), ESP::PLAYER::m_bEnableBox);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableBoxFilled"), ESP::PLAYER::m_bEnableBoxFilled);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableSnapLines"), ESP::PLAYER::m_bEnableSnapLines);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableHealthBar"), ESP::PLAYER::m_bEnableHealthBar);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableHealthText"), ESP::PLAYER::m_bEnableHealthText);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableArmorBar"), ESP::PLAYER::m_bEnableArmorBar);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableBones"), ESP::PLAYER::m_bEnableBones);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableBonesJoints"), ESP::PLAYER::m_bEnableBonesJoints);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableHead"), ESP::PLAYER::m_bEnableHead);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableHeadFilled"), ESP::PLAYER::m_bEnableHeadFilled);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableEyeRays"), ESP::PLAYER::m_bEnableEyeRays);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableNames"), ESP::PLAYER::m_bEnableNames);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bEnableDistanceEsp"), ESP::PLAYER::m_bEnableDistanceEsp);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bTeamCheck"), ESP::PLAYER::m_bTeamCheck);
			ini.Store<bool>(xorstr_("VISUALS"), xorstr_("m_bDormantCheck"), ESP::PLAYER::m_bDormantCheck);
			ini.Store<float>(xorstr_("VISUALS"), xorstr_("m_flBoxRounding"), ESP::PLAYER::m_flBoxRounding);
			ini.Store<float>(xorstr_("VISUALS"), xorstr_("m_flBoxUnfilledThickness"), ESP::PLAYER::m_flBoxUnfilledThickness);
			ini.Store<float>(xorstr_("VISUALS"), xorstr_("m_flBonesThickness"), ESP::PLAYER::m_flBonesThickness);
			ini.Store<float>(xorstr_("VISUALS"), xorstr_("m_flLinesThickness"), ESP::PLAYER::m_flLinesThickness);
			ini.Store<float>(xorstr_("VISUALS"), xorstr_("m_flJointRadius"), ESP::PLAYER::m_flJointRadius);
			ini.Store<int>(xorstr_("VISUALS"), xorstr_("m_iCurrentLinePosIndex"), ESP::PLAYER::m_iCurrentLinePosIndex);

			// TRIGGER_BOT
			ini.Store<bool>(xorstr_("TRIGGERBOT"), xorstr_("m_bEnableTriggerBot"), TRIGGER_BOT::m_bEnableTriggerBot);
			ini.Store<bool>(xorstr_("TRIGGERBOT"), xorstr_("m_bEnableTeamCheck"), TRIGGER_BOT::m_bEnableTeamCheck);
			ini.Store<int>(xorstr_("TRIGGERBOT"), xorstr_("m_iCurrentTriggerModeIndex"), TRIGGER_BOT::m_iCurrentTriggerModeIndex);
			ini.Store<int>(xorstr_("TRIGGERBOT"), xorstr_("m_iCurrentTriggerKey"), TRIGGER_BOT::m_iCurrentTriggerKey);
			ini.Store<float>(xorstr_("TRIGGERBOT"), xorstr_("m_flTriggerDelay"), TRIGGER_BOT::m_flTriggerDelay);
			ini.Store<float>(xorstr_("TRIGGERBOT"), xorstr_("m_flTriggerFireRate"), TRIGGER_BOT::m_flTriggerFireRate);

			// SRCS
			ini.Store<bool>(xorstr_("SRCS"), xorstr_("(m_bEnableSRCS"), SRCS::m_bEnableSRCS);
			ini.Store<int>(xorstr_("SRCS"), xorstr_("(m_iCurrentSRCSModeIndex"), SRCS::m_iCurrentSRCSModeIndex);
			ini.Store<int>(xorstr_("SRCS"), xorstr_("(m_iCurrentSRCSKey"), SRCS::m_iCurrentSRCSKey);
			ini.Store<float>(xorstr_("SRCS"), xorstr_("(m_flYAW"), SRCS::m_flYAW);
			ini.Store<float>(xorstr_("SRCS"), xorstr_("(m_flPITCH"), SRCS::m_flPITCH);

			//AUTOFIRE
			/*ini.Store<bool>(xorstr_("AUTOFIRE"), xorstr_("m_bEnableAutofire"), AUTOFIRE::m_bEnableAutofire);
			ini.Store<int>(xorstr_("AUTOFIRE"), xorstr_("m_iCurrentAutoFireModeIndex"), AUTOFIRE::m_iCurrentAutoFireModeIndex);
			ini.Store<int>(xorstr_("AUTOFIRE"), xorstr_("m_iCurrentAutoFireStateIndex"), AUTOFIRE::m_iCurrentAutoFireStateIndex);
			ini.Store<int>(xorstr_("AUTOFIRE"), xorstr_("m_iCurrentAutoFireKey"), AUTOFIRE::m_iCurrentAutoFireKey);
			ini.Store<float>(xorstr_("AUTOFIRE"), xorstr_("m_flAutoFireDelay"), AUTOFIRE::m_flAutoFireDelay);
			ini.Store<float>(xorstr_("AUTOFIRE"), xorstr_("m_flAutoFireRate"), AUTOFIRE::m_flAutoFireRate);*/

			// HITSERVICE
			ini.Store<bool>(xorstr_("WEAPON"), xorstr_("m_bEnableEquippedWeaponEsp"), ESP::PLAYER::m_bEnableEquippedWeaponEsp);
			ini.Store<bool>(xorstr_("WEAPON"), xorstr_("m_bEnableHitsound"), HITSERVICE::m_bEnableHitsound);
		}

		("Saving Color Data");
		{
			// VISUALS
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clBoxFilledColor"), ESP::PLAYER::m_clBoxFilledColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clBoxUnfilledColor"), ESP::PLAYER::m_clBoxUnfilledColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clLineColor"), ESP::PLAYER::m_clLineColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clLinePointColor"), ESP::PLAYER::m_clLinePointColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clNameColor"), ESP::PLAYER::m_clNameColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clNameStrokeColor"), ESP::PLAYER::m_clNameStrokeColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clArmorBarColor"), ESP::PLAYER::m_clArmorBarColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clDistanceTextColor"), ESP::PLAYER::m_clDistanceTextColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clDistanceTextStrokeColor"), ESP::PLAYER::m_clDistanceTextStrokeColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clHealthTextColor"), ESP::PLAYER::m_clHealthTextColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clHealthTextStrokeColor"), ESP::PLAYER::m_clHealthTextStrokeColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clBoneColor"), ESP::PLAYER::m_clBoneColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clBoneHeadColor"), ESP::PLAYER::m_clBoneHeadColor);
			ini.StoreColor(xorstr_("VISUALS"), xorstr_("m_clBoneJointsColor"), ESP::PLAYER::m_clBoneJointsColor);

			// WEAPONS
			ini.StoreColor(xorstr_("WEAPON"), xorstr_("m_clEquippedWeaponIconColor"), ESP::PLAYER::m_clEquippedWeaponIconColor);
			ini.StoreColor(xorstr_("WEAPON"), xorstr_("m_clEquippedWeaponIconStrokeColor"), ESP::PLAYER::m_clEquippedWeaponIconStrokeColor);
		}

		ini._WriteDataToFile(base_directory + configs_directory + file_name + CONFIG_FILE_EXTENSION);
	}

	void LoadConfig() {
		if (ini._ReadDataFromFile(base_directory + configs_directory + file_name)) {
			("Loading Data");
			{
				// VISUALS
				ESP::PLAYER::m_bEnablePlayerEsp		= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnablePlayerEsp"));
				ESP::PLAYER::m_bEnableBox			= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableBox"));
				ESP::PLAYER::m_bEnableBoxFilled		= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableBoxFilled"));
				ESP::PLAYER::m_bEnableSnapLines		= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableSnapLines"));
				ESP::PLAYER::m_bEnableHealthBar		= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableHealthBar"));
				ESP::PLAYER::m_bEnableHealthText	= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableHealthText"));
				ESP::PLAYER::m_bEnableArmorBar		= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableArmorBar"));
				ESP::PLAYER::m_bEnableBones			= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableBones"));
				ESP::PLAYER::m_bEnableHead			= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableHead"));
				ESP::PLAYER::m_bEnableHeadFilled	= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableHeadFilled"));
				ESP::PLAYER::m_bEnableEyeRays		= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableEyeRays"));
				ESP::PLAYER::m_bEnableNames			= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableNames"));
				ESP::PLAYER::m_bEnableDistanceEsp	= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bEnableDistanceEsp"));
				ESP::PLAYER::m_bTeamCheck			= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bTeamCheck"));
				ESP::PLAYER::m_bDormantCheck		= ini.GetBool(xorstr_("VISUALS"), xorstr_("m_bDormantCheck"));

				ESP::PLAYER::m_flBoxUnfilledThickness	= ini.GetFloat(xorstr_("VISUALS"), xorstr_("m_flBoxUnfilledThickness"));
				ESP::PLAYER::m_flBoxRounding			= ini.GetFloat(xorstr_("VISUALS"), xorstr_("m_flBoxRounding"));
				ESP::PLAYER::m_flLinesThickness			= ini.GetFloat(xorstr_("VISUALS"), xorstr_("m_flLinesThickness"));
				ESP::PLAYER::m_flBonesThickness			= ini.GetFloat(xorstr_("VISUALS"), xorstr_("m_flBonesThickness"));
				ESP::PLAYER::m_flJointRadius			= ini.GetFloat(xorstr_("VISUALS"), xorstr_("m_flJointRadius"));

				// TRIGGER_BOT
				TRIGGER_BOT::m_bEnableTriggerBot		= ini.GetBool(xorstr_("TRIGGERBOT"), xorstr_("m_bEnableTriggerBot"));
				TRIGGER_BOT::m_bEnableTeamCheck			= ini.GetBool(xorstr_("TRIGGERBOT"), xorstr_("m_bEnableTeamCheck"));
				TRIGGER_BOT::m_iCurrentTriggerModeIndex = ini.GetInt(xorstr_("TRIGGERBOT"), xorstr_("m_iCurrentTriggerModeIndex"));
				TRIGGER_BOT::m_iCurrentTriggerKey		= ini.GetInt(xorstr_("TRIGGERBOT"), xorstr_("m_iCurrentTriggerKey"));
				TRIGGER_BOT::m_flTriggerDelay			= ini.GetFloat(xorstr_("TRIGGERBOT"), xorstr_("m_flTriggerDelay"));
				TRIGGER_BOT::m_flTriggerFireRate		= ini.GetFloat(xorstr_("TRIGGERBOT"), xorstr_("m_flTriggerFireRate"));

				// SRCS 
				SRCS::m_bEnableSRCS				= ini.GetBool(xorstr_("SRCS"), xorstr_("m_bEnableSRCS"));
				SRCS::m_iCurrentSRCSModeIndex	= ini.GetInt(xorstr_("SRCS"), xorstr_("m_iCurrentSRCSModeIndex"));
				SRCS::m_iCurrentSRCSKey			= ini.GetInt(xorstr_("SRCS"), xorstr_("m_iCurrentSRCSKey"));
				SRCS::m_flYAW					= ini.GetFloat(xorstr_("SRCS"), xorstr_("m_flYAW"));
				SRCS::m_flPITCH					= ini.GetFloat(xorstr_("SRCS"), xorstr_("m_flPITCH"));

				//AUTOFIRE
			/*	AUTOFIRE::m_bEnableAutofire				= ini.GetBool(xorstr_("AUTOFIRE"), xorstr_("m_bEnableAutofire"));
				AUTOFIRE::m_iCurrentAutoFireModeIndex	= ini.GetInt(xorstr_("AUTOFIRE"), xorstr_("m_iCurrentAutoFireModeIndex"));
				AUTOFIRE::m_iCurrentAutoFireStateIndex	= ini.GetInt(xorstr_("AUTOFIRE"), xorstr_("m_iCurrentAutoFireStateIndex"));
				AUTOFIRE::m_iCurrentAutoFireKey			= ini.GetInt(xorstr_("AUTOFIRE"), xorstr_("m_iCurrentAutoFireKey"));
				AUTOFIRE::m_flAutoFireDelay				= ini.GetFloat(xorstr_("AUTOFIRE"), xorstr_("m_flAutoFireDelay"));
				AUTOFIRE::m_flAutoFireRate				= ini.GetFloat(xorstr_("AUTOFIRE"), xorstr_("m_flAutoFireRate"));*/

				// WEAPONS
				ESP::PLAYER::m_bEnableEquippedWeaponEsp = ini.GetBool(xorstr_("WEAPON"), xorstr_("m_bEnableEquippedWeaponEsp"));
				HITSERVICE::m_bEnableHitsound			= ini.GetBool(xorstr_("WEAPON"), xorstr_("m_bEnableHitsound"));
			}

			("Loading Color Data");
			{
				// VISUALS
				ESP::PLAYER::m_clBoxFilledColor			= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clBoxFilledColor"));
				ESP::PLAYER::m_clBoxUnfilledColor		= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clBoxUnfilledColor"));
				ESP::PLAYER::m_clLineColor				= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clLineColor"));
				ESP::PLAYER::m_clLinePointColor			= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clLinePointColor"));
				ESP::PLAYER::m_clNameColor				= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clNameColor"));
				ESP::PLAYER::m_clNameStrokeColor		= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clNameStrokeColor"));
				ESP::PLAYER::m_clArmorBarColor			= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clArmorBarColor"));
				ESP::PLAYER::m_clDistanceTextColor		= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clDistanceTextColor"));
				ESP::PLAYER::m_clHealthTextColor		= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clHealthTextColor"));
				ESP::PLAYER::m_clHealthTextStrokeColor	= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clHealthTextStrokeColor"));
				ESP::PLAYER::m_clBoneColor				= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clBoneColor"));
				ESP::PLAYER::m_clBoneHeadColor			= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clBoneHeadColor"));
				ESP::PLAYER::m_clBoneJointsColor		= ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clBoneJointsColor"));
				ESP::PLAYER::m_clDistanceTextStrokeColor = ini.GetColor(xorstr_("VISUALS"), xorstr_("m_clDistanceTextStrokeColor"));

				// WEAPONS
				ESP::PLAYER::m_clEquippedWeaponIconColor		= ini.GetColor(xorstr_("WEAPON"), xorstr_("m_clEquippedWeaponIconColor"));
				ESP::PLAYER::m_clEquippedWeaponIconStrokeColor	= ini.GetColor(xorstr_("WEAPON"), xorstr_("m_clEquippedWeaponIconStrokeColor"));
			}
		}
	}

	void ScanDirectoryForFile(const char* extension) {
		ConfigFiles.clear();
		if (!fs::exists(base_directory + configs_directory)) {
			std::cout << xorstr_("Directory does not exist: ") << base_directory + configs_directory << std::endl;
			return;
		}
		try {
			for (const auto& entry : fs::directory_iterator(base_directory + configs_directory)) {
				if (entry.is_regular_file() && entry.path().extension() == extension) {
					ConfigFiles.push_back(entry.path().filename().string());
				}
			}
		}
		catch (const std::exception& e) {
			std::cout << xorstr_("Error scanning directory: ") << e.what() << std::endl;
		}
	}

}; 

