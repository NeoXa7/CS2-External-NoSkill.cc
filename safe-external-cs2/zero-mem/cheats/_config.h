#pragma once
#include <libs/my_libs/ini.h>
#include <cheats/_import.h>

class ConfigManager {
private:
	SIMPLE_INI ini;
	std::string base_directory = Protect("bin\\");
	std::string configs_directory = Protect("configs\\");

public:
	ConfigManager() {}
	~ConfigManager() {}

	ConfigManager(const ConfigManager&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;


	std::string file_name = Protect("your-file-name");
	std::vector<std::string> ConfigFiles;

public:
	void CreateConfig() {
		ini._CreateDirectories(base_directory + configs_directory);
		ini._CreateFile(base_directory + configs_directory + file_name + CONFIG_FILE_EXTENSION);

		("SAVING DATA");
		{
			// VISUALS
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnablePlayerEsp"), ESP::PLAYER::m_bEnablePlayerEsp);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableBox"), ESP::PLAYER::m_bEnableBox);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableBoxFilled"), ESP::PLAYER::m_bEnableBoxFilled);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableSnapLines"), ESP::PLAYER::m_bEnableSnapLines);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableHealthBar"), ESP::PLAYER::m_bEnableHealthBar);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableHealthText"), ESP::PLAYER::m_bEnableHealthText);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableArmorBar"), ESP::PLAYER::m_bEnableArmorBar);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableBones"), ESP::PLAYER::m_bEnableBones);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableBonesJoints"), ESP::PLAYER::m_bEnableBonesJoints);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableHead"), ESP::PLAYER::m_bEnableHead);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableHeadFilled"), ESP::PLAYER::m_bEnableHeadFilled);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableEyeRays"), ESP::PLAYER::m_bEnableEyeRays);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableNames"), ESP::PLAYER::m_bEnableNames);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bEnableDistanceEsp"), ESP::PLAYER::m_bEnableDistanceEsp);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bTeamCheck"), ESP::PLAYER::m_bTeamCheck);
			ini.Store<bool>(Protect("VISUALS"), Protect("m_bDormantCheck"), ESP::PLAYER::m_bDormantCheck);
			ini.Store<float>(Protect("VISUALS"), Protect("m_flBoxRounding"), ESP::PLAYER::m_flBoxRounding);
			ini.Store<float>(Protect("VISUALS"), Protect("m_flBoxUnfilledThickness"), ESP::PLAYER::m_flBoxUnfilledThickness);
			ini.Store<float>(Protect("VISUALS"), Protect("m_flBonesThickness"), ESP::PLAYER::m_flBonesThickness);
			ini.Store<float>(Protect("VISUALS"), Protect("m_flLinesThickness"), ESP::PLAYER::m_flLinesThickness);
			ini.Store<float>(Protect("VISUALS"), Protect("m_flJointRadius"), ESP::PLAYER::m_flJointRadius);
			ini.Store<int>(Protect("VISUALS"), Protect("m_iCurrentLinePosIndex"), ESP::PLAYER::m_iCurrentLinePosIndex);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clBoxFilledColor"), ESP::PLAYER::m_clBoxFilledColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clBoxUnfilledColor"), ESP::PLAYER::m_clBoxUnfilledColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clLineColor"), ESP::PLAYER::m_clLineColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clLinePointColor"), ESP::PLAYER::m_clLinePointColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clNameColor"), ESP::PLAYER::m_clNameColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clNameStrokeColor"), ESP::PLAYER::m_clNameStrokeColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clArmorBarColor"), ESP::PLAYER::m_clArmorBarColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clDistanceTextColor"), ESP::PLAYER::m_clDistanceTextColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clDistanceTextStrokeColor"), ESP::PLAYER::m_clDistanceTextStrokeColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clHealthTextColor"), ESP::PLAYER::m_clHealthTextColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clHealthTextStrokeColor"), ESP::PLAYER::m_clHealthTextStrokeColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clBoneColor"), ESP::PLAYER::m_clBoneColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clBoneHeadColor"), ESP::PLAYER::m_clBoneHeadColor);
			ini.StoreColor(Protect("VISUALS"), Protect("m_clBoneJointsColor"), ESP::PLAYER::m_clBoneJointsColor);

			// AIMBOT
			ini.Store<bool>(Protect("AIMBOT"), Protect("m_bEnableAimbot"), Aimbot::m_bEnableAimbot);
			ini.Store<bool>(Protect("AIMBOT"), Protect("m_bEnableTeamCheck"), Aimbot::m_bEnableTeamCheck);
			ini.Store<bool>(Protect("AIMBOT"), Protect("m_bEnableVisibilityCheck"), Aimbot::m_bEnableVisibilityCheck);
			ini.Store<bool>(Protect("AIMBOT"), Protect("m_bFovBased"), Aimbot::m_bFovBased);
			ini.Store<bool>(Protect("AIMBOT"), Protect("m_bShowFovCircle"), Aimbot::m_bShowFovCircle);
			ini.Store<bool>(Protect("AIMBOT"), Protect("m_bRandomizeAimPosition"), Aimbot::m_bRandomizeAimPosition);
			ini.Store<float>(Protect("AIMBOT"), Protect("m_flSmoothness"), Aimbot::m_flSmoothness);
			ini.Store<float>(Protect("AIMBOT"), Protect("m_flFOV"), Aimbot::m_flFOV);
			ini.Store<float>(Protect("AIMBOT"), Protect("m_flFOVCircleThickness"), Aimbot::m_flFOVCircleThickness);
			ini.Store<int>(Protect("AIMBOT"), Protect("m_iCurrentAimbotModeIndex"), Aimbot::m_iCurrentAimbotModeIndex);
			ini.Store<int>(Protect("AIMBOT"), Protect("m_iCurrentAimPosIndex"), Aimbot::m_iCurrentAimPosIndex);
			ini.StoreColor(Protect("AIMBOT"), Protect("m_clFOVCircleColor"), Aimbot::m_clFOVCircleColor);

			// TRIGGER_BOT
			ini.Store<std::atomic<bool>>(Protect("TRIGGERBOT"), Protect("m_bEnableTriggerBot"), TRIGGER_BOT::m_bEnableTriggerBot);
			ini.Store<std::atomic<bool>>(Protect("TRIGGERBOT"), Protect("m_bEnableTeamCheck"), TRIGGER_BOT::m_bEnableTeamCheck);
			ini.Store<int>(Protect("TRIGGERBOT"), Protect("m_iCurrentTriggerModeIndex"), TRIGGER_BOT::m_iCurrentTriggerModeIndex);
			ini.Store<int>(Protect("TRIGGERBOT"), Protect("m_iCurrentTriggerKey"), TRIGGER_BOT::m_iCurrentTriggerKey);
			ini.Store<float>(Protect("TRIGGERBOT"), Protect("m_flTriggerDelay"), TRIGGER_BOT::m_flTriggerDelay);
			ini.Store<float>(Protect("TRIGGERBOT"), Protect("m_flTriggerFireRate"), TRIGGER_BOT::m_flTriggerFireRate);

			// SRCS
			ini.Store<bool>(Protect("SRCS"), Protect("m_bEnableSRCS"), SRCS::m_bEnableSRCS);
			ini.Store<int>(Protect("SRCS"), Protect("m_iCurrentSRCSModeIndex"), SRCS::m_iCurrentSRCSModeIndex);
			ini.Store<int>(Protect("SRCS"), Protect("m_iCurrentSRCSKey"), SRCS::m_iCurrentSRCSKey);
			ini.Store<float>(Protect("SRCS"), Protect("m_flYAW"), SRCS::m_flYAW);
			ini.Store<float>(Protect("SRCS"), Protect("m_flPITCH"), SRCS::m_flPITCH);

			//AUTOFIRE
			/*ini.Store<bool>(Protect("AUTOFIRE"), Protect("m_bEnableAutofire"), AUTOFIRE::m_bEnableAutofire);
			ini.Store<int>(Protect("AUTOFIRE"), Protect("m_iCurrentAutoFireModeIndex"), AUTOFIRE::m_iCurrentAutoFireModeIndex);
			ini.Store<int>(Protect("AUTOFIRE"), Protect("m_iCurrentAutoFireStateIndex"), AUTOFIRE::m_iCurrentAutoFireStateIndex);
			ini.Store<int>(Protect("AUTOFIRE"), Protect("m_iCurrentAutoFireKey"), AUTOFIRE::m_iCurrentAutoFireKey);
			ini.Store<float>(Protect("AUTOFIRE"), Protect("m_flAutoFireDelay"), AUTOFIRE::m_flAutoFireDelay);
			ini.Store<float>(Protect("AUTOFIRE"), Protect("m_flAutoFireRate"), AUTOFIRE::m_flAutoFireRate);*/

			// WEAPON
			ini.Store<bool>(Protect("WEAPON"), Protect("m_bEnableEquippedWeaponEsp"), ESP::WEAPONS::m_bEnableEquippedWeaponEsp);
			ini.Store<bool>(Protect("WEAPON"), Protect("m_bEnableHitsound"), HITSERVICE::m_bEnableHitsound);
			ini.StoreColor(Protect("WEAPON"), Protect("m_clEquippedWeaponIconColor"), ESP::WEAPONS::m_clEquippedWeaponIconColor);
			ini.StoreColor(Protect("WEAPON"), Protect("m_clEquippedWeaponIconStrokeColor"), ESP::WEAPONS::m_clEquippedWeaponIconStrokeColor);
		}

		ini._WriteDataToFile(base_directory + configs_directory + file_name + CONFIG_FILE_EXTENSION);
	}

	void LoadConfig() {
		if (ini._ReadDataFromFile(base_directory + configs_directory + file_name)) {
			("Loading Data");
			{
				// VISUALS
				ESP::PLAYER::m_bEnablePlayerEsp		= ini.GetBool(Protect("VISUALS"), Protect("m_bEnablePlayerEsp"));
				ESP::PLAYER::m_bEnableBox			= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableBox"));
				ESP::PLAYER::m_bEnableBoxFilled		= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableBoxFilled"));
				ESP::PLAYER::m_bEnableSnapLines		= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableSnapLines"));
				ESP::PLAYER::m_bEnableHealthBar		= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableHealthBar"));
				ESP::PLAYER::m_bEnableHealthText	= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableHealthText"));
				ESP::PLAYER::m_bEnableArmorBar		= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableArmorBar"));
				ESP::PLAYER::m_bEnableBones			= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableBones"));
				ESP::PLAYER::m_bEnableHead			= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableHead"));
				ESP::PLAYER::m_bEnableHeadFilled	= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableHeadFilled"));
				ESP::PLAYER::m_bEnableEyeRays		= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableEyeRays"));
				ESP::PLAYER::m_bEnableNames			= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableNames"));
				ESP::PLAYER::m_bEnableDistanceEsp	= ini.GetBool(Protect("VISUALS"), Protect("m_bEnableDistanceEsp"));
				ESP::PLAYER::m_bTeamCheck			= ini.GetBool(Protect("VISUALS"), Protect("m_bTeamCheck"));
				ESP::PLAYER::m_bDormantCheck		= ini.GetBool(Protect("VISUALS"), Protect("m_bDormantCheck"));
				ESP::PLAYER::m_flBoxUnfilledThickness	= ini.GetFloat(Protect("VISUALS"), Protect("m_flBoxUnfilledThickness"));
				ESP::PLAYER::m_flBoxRounding			= ini.GetFloat(Protect("VISUALS"), Protect("m_flBoxRounding"));
				ESP::PLAYER::m_flLinesThickness			= ini.GetFloat(Protect("VISUALS"), Protect("m_flLinesThickness"));
				ESP::PLAYER::m_flBonesThickness			= ini.GetFloat(Protect("VISUALS"), Protect("m_flBonesThickness"));
				ESP::PLAYER::m_flJointRadius			= ini.GetFloat(Protect("VISUALS"), Protect("m_flJointRadius"));
				ESP::PLAYER::m_clBoxFilledColor = ini.GetColor(Protect("VISUALS"), Protect("m_clBoxFilledColor"));
				ESP::PLAYER::m_clBoxUnfilledColor = ini.GetColor(Protect("VISUALS"), Protect("m_clBoxUnfilledColor"));
				ESP::PLAYER::m_clLineColor = ini.GetColor(Protect("VISUALS"), Protect("m_clLineColor"));
				ESP::PLAYER::m_clLinePointColor = ini.GetColor(Protect("VISUALS"), Protect("m_clLinePointColor"));
				ESP::PLAYER::m_clNameColor = ini.GetColor(Protect("VISUALS"), Protect("m_clNameColor"));
				ESP::PLAYER::m_clNameStrokeColor = ini.GetColor(Protect("VISUALS"), Protect("m_clNameStrokeColor"));
				ESP::PLAYER::m_clArmorBarColor = ini.GetColor(Protect("VISUALS"), Protect("m_clArmorBarColor"));
				ESP::PLAYER::m_clDistanceTextColor = ini.GetColor(Protect("VISUALS"), Protect("m_clDistanceTextColor"));
				ESP::PLAYER::m_clHealthTextColor = ini.GetColor(Protect("VISUALS"), Protect("m_clHealthTextColor"));
				ESP::PLAYER::m_clHealthTextStrokeColor = ini.GetColor(Protect("VISUALS"), Protect("m_clHealthTextStrokeColor"));
				ESP::PLAYER::m_clBoneColor = ini.GetColor(Protect("VISUALS"), Protect("m_clBoneColor"));
				ESP::PLAYER::m_clBoneHeadColor = ini.GetColor(Protect("VISUALS"), Protect("m_clBoneHeadColor"));
				ESP::PLAYER::m_clBoneJointsColor = ini.GetColor(Protect("VISUALS"), Protect("m_clBoneJointsColor"));
				ESP::PLAYER::m_clDistanceTextStrokeColor = ini.GetColor(Protect("VISUALS"), Protect("m_clDistanceTextStrokeColor"));





				// TRIGGER_BOT
				TRIGGER_BOT::m_bEnableTriggerBot		= ini.GetBool(Protect("TRIGGERBOT"), Protect("m_bEnableTriggerBot"));
				TRIGGER_BOT::m_bEnableTeamCheck			= ini.GetBool(Protect("TRIGGERBOT"), Protect("m_bEnableTeamCheck"));
				TRIGGER_BOT::m_iCurrentTriggerModeIndex = ini.GetInt(Protect("TRIGGERBOT"), Protect("m_iCurrentTriggerModeIndex"));
				TRIGGER_BOT::m_iCurrentTriggerKey		= ini.GetInt(Protect("TRIGGERBOT"), Protect("m_iCurrentTriggerKey"));
				TRIGGER_BOT::m_flTriggerDelay			= ini.GetFloat(Protect("TRIGGERBOT"), Protect("m_flTriggerDelay"));
				TRIGGER_BOT::m_flTriggerFireRate		= ini.GetFloat(Protect("TRIGGERBOT"), Protect("m_flTriggerFireRate"));

				// SRCS 
				SRCS::m_bEnableSRCS				= ini.GetBool(Protect("SRCS"), Protect("m_bEnableSRCS"));
				SRCS::m_iCurrentSRCSModeIndex	= ini.GetInt(Protect("SRCS"), Protect("m_iCurrentSRCSModeIndex"));
				SRCS::m_iCurrentSRCSKey			= ini.GetInt(Protect("SRCS"), Protect("m_iCurrentSRCSKey"));
				SRCS::m_flYAW					= ini.GetFloat(Protect("SRCS"), Protect("m_flYAW"));
				SRCS::m_flPITCH					= ini.GetFloat(Protect("SRCS"), Protect("m_flPITCH"));

				//AUTOFIRE
			/*	AUTOFIRE::m_bEnableAutofire				= ini.GetBool(Protect("AUTOFIRE"), Protect("m_bEnableAutofire"));
				AUTOFIRE::m_iCurrentAutoFireModeIndex	= ini.GetInt(Protect("AUTOFIRE"), Protect("m_iCurrentAutoFireModeIndex"));
				AUTOFIRE::m_iCurrentAutoFireStateIndex	= ini.GetInt(Protect("AUTOFIRE"), Protect("m_iCurrentAutoFireStateIndex"));
				AUTOFIRE::m_iCurrentAutoFireKey			= ini.GetInt(Protect("AUTOFIRE"), Protect("m_iCurrentAutoFireKey"));
				AUTOFIRE::m_flAutoFireDelay				= ini.GetFloat(Protect("AUTOFIRE"), Protect("m_flAutoFireDelay"));
				AUTOFIRE::m_flAutoFireRate				= ini.GetFloat(Protect("AUTOFIRE"), Protect("m_flAutoFireRate"));*/

				// WEAPONS
				ESP::WEAPONS::m_bEnableEquippedWeaponEsp = ini.GetBool(Protect("WEAPON"), Protect("m_bEnableEquippedWeaponEsp"));
				HITSERVICE::m_bEnableHitsound			= ini.GetBool(Protect("WEAPON"), Protect("m_bEnableHitsound"));
			}

			("Loading Color Data");
			{
				// VISUALS
				

				// WEAPONS
				ESP::WEAPONS::m_clEquippedWeaponIconColor		= ini.GetColor(Protect("WEAPON"), Protect("m_clEquippedWeaponIconColor"));
				ESP::WEAPONS::m_clEquippedWeaponIconStrokeColor	= ini.GetColor(Protect("WEAPON"), Protect("m_clEquippedWeaponIconStrokeColor"));
			}
		}
	}

	void ScanDirectoryForFile(const char* extension) {
		ConfigFiles.clear();
		if (!fs::exists(base_directory + configs_directory)) {
			std::cout << Protect("Directory does not exist: ") << base_directory + configs_directory << std::endl;
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
			std::cout << Protect("Error scanning directory: ") << e.what() << std::endl;
		}
	}

}; 

