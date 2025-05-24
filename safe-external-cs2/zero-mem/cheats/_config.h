#pragma once
#include <libs/my_libs/ini.h>
#include <cheats/_import.h>

class ConfigManager {
private:
	SIMPLE_INI ini;
	std::string base_directory = PROTECT("bin\\");
	std::string configs_directory = PROTECT("configs\\");

public:
	ConfigManager() {}
	~ConfigManager() {}

	ConfigManager(const ConfigManager&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;


	std::string file_name = PROTECT("your-file-name");
	std::vector<std::string> ConfigFiles;

public:
	void CreateConfig() {
		ini._CreateDirectories(base_directory + configs_directory);
		ini._CreateFile(base_directory + configs_directory + file_name + CONFIG_FILE_EXTENSION);

		("SAVING DATA");
		{
			// VISUALS
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnablePlayerEsp"), ESP::PLAYER::m_bEnablePlayerEsp);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableBox"), ESP::PLAYER::m_bEnableBox);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableBoxFilled"), ESP::PLAYER::m_bEnableBoxFilled);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableBoxImage"), ESP::PLAYER::m_bEnableBoxImage);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableSnapLines"), ESP::PLAYER::m_bEnableSnapLines);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableHealthBar"), ESP::PLAYER::m_bEnableHealthBar);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableHealthText"), ESP::PLAYER::m_bEnableHealthText);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableArmorBar"), ESP::PLAYER::m_bEnableArmorBar);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableBones"), ESP::PLAYER::m_bEnableBones);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableBonesJoints"), ESP::PLAYER::m_bEnableBonesJoints);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableHead"), ESP::PLAYER::m_bEnableHead);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableHeadFilled"), ESP::PLAYER::m_bEnableHeadFilled);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableEyeRays"), ESP::PLAYER::m_bEnableEyeRays);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableNames"), ESP::PLAYER::m_bEnableNames);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bEnableDistanceEsp"), ESP::PLAYER::m_bEnableDistanceEsp);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bTeamCheck"), ESP::PLAYER::m_bTeamCheck);
			ini.Store<bool>(PROTECT("VISUALS"), PROTECT("m_bDormantCheck"), ESP::PLAYER::m_bDormantCheck);
			ini.Store<float>(PROTECT("VISUALS"), PROTECT("m_flBoxRounding"), ESP::PLAYER::m_flBoxRounding);
			ini.Store<float>(PROTECT("VISUALS"), PROTECT("m_flBoxUnfilledThickness"), ESP::PLAYER::m_flBoxUnfilledThickness);
			ini.Store<float>(PROTECT("VISUALS"), PROTECT("m_flBonesThickness"), ESP::PLAYER::m_flBonesThickness);
			ini.Store<float>(PROTECT("VISUALS"), PROTECT("m_flLinesThickness"), ESP::PLAYER::m_flLinesThickness);
			ini.Store<float>(PROTECT("VISUALS"), PROTECT("m_flJointRadius"), ESP::PLAYER::m_flJointRadius);
			ini.Store<int>(PROTECT("VISUALS"), PROTECT("m_iCurrentLinePosIndex"), ESP::PLAYER::m_iCurrentLinePosIndex);
			ini.Store<int>(PROTECT("VISUALS"), PROTECT("m_iCurrentImageIndex"), ESP::PLAYER::m_iCurrentImageIndex);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clCrosshairColor"), CROSSHAIR::m_clCrossHairColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clBoxFilledColor"), ESP::PLAYER::m_clBoxFilledColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clBoxUnfilledColor"), ESP::PLAYER::m_clBoxUnfilledColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clLineColor"), ESP::PLAYER::m_clLineColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clLinePointColor"), ESP::PLAYER::m_clLinePointColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clNameColor"), ESP::PLAYER::m_clNameColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clNameStrokeColor"), ESP::PLAYER::m_clNameStrokeColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clArmorBarColor"), ESP::PLAYER::m_clArmorBarColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clDistanceTextColor"), ESP::PLAYER::m_clDistanceTextColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clDistanceTextStrokeColor"), ESP::PLAYER::m_clDistanceTextStrokeColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clHealthTextColor"), ESP::PLAYER::m_clHealthTextColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clHealthTextStrokeColor"), ESP::PLAYER::m_clHealthTextStrokeColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clBoneColor"), ESP::PLAYER::m_clBoneColor);
			ini.StoreColor(PROTECT("VISUALS"), PROTECT("m_clBoneHeadColor"), ESP::PLAYER::m_clBoneHeadColor);

			// CROSSHAIR
			ini.Store<bool>(PROTECT("CROSSHAIR"), PROTECT("m_bEnableCrosshair"), CROSSHAIR::m_bEnableCrosshair);
			ini.Store<float>(PROTECT("CROSSHAIR"), PROTECT("m_flCrossHairSize"), CROSSHAIR::m_flCrossHairSize);
			ini.StoreColor(PROTECT("CROSSHAIR"), PROTECT("m_clCrossHairColor"), CROSSHAIR::m_clCrossHairColor);

			// AIMBOT
			ini.Store<bool>(PROTECT("AIMBOT"), PROTECT("m_bEnableAimbot"), AIMBOT::m_bEnableAimbot);
			ini.Store<bool>(PROTECT("AIMBOT"), PROTECT("m_bEnableTeamCheck"), AIMBOT::m_bEnableTeamCheck);
			ini.Store<bool>(PROTECT("AIMBOT"), PROTECT("m_bEnableSniperScopeCheck"), AIMBOT::m_bEnableSniperScopeCheck);
			ini.Store<bool>(PROTECT("AIMBOT"), PROTECT("m_bEnableSniperRifleScopeCheck"), AIMBOT::m_bEnableSniperRifleScopeCheck);
			ini.Store<bool>(PROTECT("AIMBOT"), PROTECT("m_bFovBased"), AIMBOT::m_bFovBased);
			ini.Store<bool>(PROTECT("AIMBOT"), PROTECT("m_bShowFovCircle"), AIMBOT::m_bShowFovCircle);
			ini.Store<bool>(PROTECT("AIMBOT"), PROTECT("m_bRandomizeAimPosition"), AIMBOT::m_bRandomizeAimPosition);
			ini.Store<float>(PROTECT("AIMBOT"), PROTECT("m_flSmoothness"), AIMBOT::m_flSmoothness);
			ini.Store<float>(PROTECT("AIMBOT"), PROTECT("m_flFOV"), AIMBOT::m_flFOV);
			ini.Store<float>(PROTECT("AIMBOT"), PROTECT("m_flFOVCircleThickness"), AIMBOT::m_flFOVCircleThickness);
			ini.Store<int>(PROTECT("AIMBOT"), PROTECT("m_iCurrentKEY"), AIMBOT::m_iCurrentKEY);
			ini.Store<int>(PROTECT("AIMBOT"), PROTECT("m_iCurrentAimbotModeIndex"), AIMBOT::m_iCurrentAimbotModeIndex);
			ini.Store<int>(PROTECT("AIMBOT"), PROTECT("m_iCurrentAimPosIndex"), AIMBOT::m_iCurrentAimPosIndex);
			ini.StoreColor(PROTECT("AIMBOT"), PROTECT("m_clFOVCircleColor"), AIMBOT::m_clFOVCircleColor);

			// TRIGGER_BOT
			ini.Store<std::atomic<bool>>(PROTECT("TRIGGERBOT"), PROTECT("m_bEnableTriggerBot"), TRIGGER_BOT::m_bEnableTriggerBot);
			ini.Store<std::atomic<bool>>(PROTECT("TRIGGERBOT"), PROTECT("m_bEnableTeamCheck"), TRIGGER_BOT::m_bEnableTeamCheck);
			ini.Store<int>(PROTECT("TRIGGERBOT"), PROTECT("m_iCurrentTriggerModeIndex"), TRIGGER_BOT::m_iCurrentTriggerModeIndex);
			ini.Store<int>(PROTECT("TRIGGERBOT"), PROTECT("m_iCurrentTriggerKey"), TRIGGER_BOT::m_iCurrentTriggerKey);
			ini.Store<float>(PROTECT("TRIGGERBOT"), PROTECT("m_flTriggerDelay"), TRIGGER_BOT::m_flTriggerDelay);
			ini.Store<float>(PROTECT("TRIGGERBOT"), PROTECT("m_flTriggerFireRate"), TRIGGER_BOT::m_flTriggerFireRate);

			// SRCS
			ini.Store<bool>(PROTECT("SRCS"), PROTECT("m_bEnableSRCS"), SRCS::m_bEnableSRCS);
			ini.Store<int>(PROTECT("SRCS"), PROTECT("m_iCurrentSRCSModeIndex"), SRCS::m_iCurrentSRCSModeIndex);
			ini.Store<int>(PROTECT("SRCS"), PROTECT("m_iCurrentSRCSKey"), SRCS::m_iCurrentSRCSKey);
			ini.Store<float>(PROTECT("SRCS"), PROTECT("m_flYAW"), SRCS::m_flYAW);
			ini.Store<float>(PROTECT("SRCS"), PROTECT("m_flPITCH"), SRCS::m_flPITCH);

			//AUTOFIRE
			/*ini.Store<bool>(PROTECT("AUTOFIRE"), PROTECT("m_bEnableAutofire"), AUTOFIRE::m_bEnableAutofire);
			ini.Store<int>(PROTECT("AUTOFIRE"), PROTECT("m_iCurrentAutoFireModeIndex"), AUTOFIRE::m_iCurrentAutoFireModeIndex);
			ini.Store<int>(PROTECT("AUTOFIRE"), PROTECT("m_iCurrentAutoFireStateIndex"), AUTOFIRE::m_iCurrentAutoFireStateIndex);
			ini.Store<int>(PROTECT("AUTOFIRE"), PROTECT("m_iCurrentAutoFireKey"), AUTOFIRE::m_iCurrentAutoFireKey);
			ini.Store<float>(PROTECT("AUTOFIRE"), PROTECT("m_flAutoFireDelay"), AUTOFIRE::m_flAutoFireDelay);
			ini.Store<float>(PROTECT("AUTOFIRE"), PROTECT("m_flAutoFireRate"), AUTOFIRE::m_flAutoFireRate);*/

			// WEAPON
			ini.Store<bool>(PROTECT("WEAPON"), PROTECT("m_bEnableEquippedWeaponEsp"), ESP::WEAPONS::m_bEnableEquippedWeaponEsp);
			ini.Store<bool>(PROTECT("WEAPON"), PROTECT("m_bEnableHitsound"), HITSERVICE::m_bEnableHitsound);
			ini.StoreColor(PROTECT("WEAPON"), PROTECT("m_clEquippedWeaponIconColor"), ESP::WEAPONS::m_clEquippedWeaponIconColor);
			ini.StoreColor(PROTECT("WEAPON"), PROTECT("m_clEquippedWeaponIconStrokeColor"), ESP::WEAPONS::m_clEquippedWeaponIconStrokeColor);
		}

		ini._WriteDataToFile(base_directory + configs_directory + file_name + CONFIG_FILE_EXTENSION);
	}

	void LoadConfig() {
		if (ini._ReadDataFromFile(base_directory + configs_directory + file_name)) {
			// VISUALS
			ESP::PLAYER::m_bEnablePlayerEsp = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnablePlayerEsp"));
			ESP::PLAYER::m_bEnableBox = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableBox"));
			ESP::PLAYER::m_bEnableBoxFilled = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableBoxFilled"));
			ESP::PLAYER::m_bEnableBoxImage = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableBoxImage"));
			ESP::PLAYER::m_bEnableSnapLines = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableSnapLines"));
			ESP::PLAYER::m_bEnableHealthBar = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableHealthBar"));
			ESP::PLAYER::m_bEnableHealthText = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableHealthText"));
			ESP::PLAYER::m_bEnableArmorBar = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableArmorBar"));
			ESP::PLAYER::m_bEnableBones = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableBones"));
			ESP::PLAYER::m_bEnableBonesJoints = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableBonesJoints"));
			ESP::PLAYER::m_bEnableHead = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableHead"));
			ESP::PLAYER::m_bEnableHeadFilled = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableHeadFilled"));
			ESP::PLAYER::m_bEnableEyeRays = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableEyeRays"));
			ESP::PLAYER::m_bEnableNames = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableNames"));
			ESP::PLAYER::m_bEnableDistanceEsp = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bEnableDistanceEsp"));
			ESP::PLAYER::m_bTeamCheck = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bTeamCheck"));
			ESP::PLAYER::m_bDormantCheck = ini.GetBool(PROTECT("VISUALS"), PROTECT("m_bDormantCheck"));
			ESP::PLAYER::m_flBoxUnfilledThickness = ini.GetFloat(PROTECT("VISUALS"), PROTECT("m_flBoxUnfilledThickness"));
			ESP::PLAYER::m_flBoxRounding = ini.GetFloat(PROTECT("VISUALS"), PROTECT("m_flBoxRounding"));
			ESP::PLAYER::m_flLinesThickness = ini.GetFloat(PROTECT("VISUALS"), PROTECT("m_flLinesThickness"));
			ESP::PLAYER::m_flBonesThickness = ini.GetFloat(PROTECT("VISUALS"), PROTECT("m_flBonesThickness"));
			ESP::PLAYER::m_flJointRadius = ini.GetFloat(PROTECT("VISUALS"), PROTECT("m_flJointRadius"));
			ESP::PLAYER::m_iCurrentLinePosIndex = ini.GetInt(PROTECT("VISUALS"), PROTECT("m_iCurrentLinePosIndex"));
			ESP::PLAYER::m_iCurrentImageIndex = ini.GetInt(PROTECT("VISUALS"), PROTECT("m_iCurrentImageIndex"));
			ESP::PLAYER::m_clBoxFilledColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clBoxFilledColor"));
			ESP::PLAYER::m_clBoxUnfilledColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clBoxUnfilledColor"));
			ESP::PLAYER::m_clLineColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clLineColor"));
			ESP::PLAYER::m_clLinePointColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clLinePointColor"));
			ESP::PLAYER::m_clNameColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clNameColor"));
			ESP::PLAYER::m_clNameStrokeColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clNameStrokeColor"));
			ESP::PLAYER::m_clArmorBarColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clArmorBarColor"));
			ESP::PLAYER::m_clDistanceTextColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clDistanceTextColor"));
			ESP::PLAYER::m_clHealthTextColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clHealthTextColor"));
			ESP::PLAYER::m_clHealthTextStrokeColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clHealthTextStrokeColor"));
			ESP::PLAYER::m_clBoneColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clBoneColor"));
			ESP::PLAYER::m_clBoneHeadColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clBoneHeadColor"));
			ESP::PLAYER::m_clBoneJointsColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clBoneJointsColor"));
			ESP::PLAYER::m_clDistanceTextStrokeColor = ini.GetColor(PROTECT("VISUALS"), PROTECT("m_clDistanceTextStrokeColor"));

			// CROSSHAIR
			CROSSHAIR::m_bEnableCrosshair = ini.GetBool(PROTECT("CROSSHAIR"), PROTECT("m_bEnableCrosshair"));
			CROSSHAIR::m_clCrossHairColor = ini.GetColor(PROTECT("CROSSHAIR"), PROTECT("m_clCrossHairColor"));
			CROSSHAIR::m_flCrossHairSize = ini.GetFloat(PROTECT("CROSSHAIR"), PROTECT("m_flCrossHairSize"));

			// TRIGGER_BOT
			TRIGGER_BOT::m_bEnableTriggerBot = ini.GetBool(PROTECT("TRIGGERBOT"), PROTECT("m_bEnableTriggerBot"));
			TRIGGER_BOT::m_bEnableTeamCheck = ini.GetBool(PROTECT("TRIGGERBOT"), PROTECT("m_bEnableTeamCheck"));
			TRIGGER_BOT::m_iCurrentTriggerModeIndex = ini.GetInt(PROTECT("TRIGGERBOT"), PROTECT("m_iCurrentTriggerModeIndex"));
			TRIGGER_BOT::m_iCurrentTriggerKey = ini.GetInt(PROTECT("TRIGGERBOT"), PROTECT("m_iCurrentTriggerKey"));
			TRIGGER_BOT::m_flTriggerDelay = ini.GetFloat(PROTECT("TRIGGERBOT"), PROTECT("m_flTriggerDelay"));
			TRIGGER_BOT::m_flTriggerFireRate = ini.GetFloat(PROTECT("TRIGGERBOT"), PROTECT("m_flTriggerFireRate"));

			// SRCS 
			SRCS::m_bEnableSRCS = ini.GetBool(PROTECT("SRCS"), PROTECT("m_bEnableSRCS"));
			SRCS::m_iCurrentSRCSModeIndex = ini.GetInt(PROTECT("SRCS"), PROTECT("m_iCurrentSRCSModeIndex"));
			SRCS::m_iCurrentSRCSKey = ini.GetInt(PROTECT("SRCS"), PROTECT("m_iCurrentSRCSKey"));
			SRCS::m_flYAW = ini.GetFloat(PROTECT("SRCS"), PROTECT("m_flYAW"));
			SRCS::m_flPITCH = ini.GetFloat(PROTECT("SRCS"), PROTECT("m_flPITCH"));

			// AIMBOT 
			AIMBOT::m_bEnableAimbot = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bEnableAimbot"));
			AIMBOT::m_bEnableTeamCheck = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bEnableTeamCheck"));
			AIMBOT::m_bEnableSniperScopeCheck = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bEnableSniperScopeCheck"));
			AIMBOT::m_bEnableSniperRifleScopeCheck = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bEnableSniperRifleScopeCheck"));
			AIMBOT::m_bEnableVisibilityCheck = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bEnableVisibilityCheck"));
			AIMBOT::m_bFovBased = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bFovBased"));
			AIMBOT::m_bShowFovCircle = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bShowFovCircle"));
			AIMBOT::m_bRandomizeAimPosition = ini.GetBool(PROTECT("AIMBOT"), PROTECT("m_bRandomizeAimPosition"));
			AIMBOT::m_flSmoothness = ini.GetFloat(PROTECT("AIMBOT"), PROTECT("m_flSmoothness"));
			AIMBOT::m_flFOV = ini.GetFloat(PROTECT("AIMBOT"), PROTECT("m_flFOV"));
			AIMBOT::m_flFOVCircleThickness = ini.GetFloat(PROTECT("AIMBOT"), PROTECT("m_flFOVCircleThickness"));
			AIMBOT::m_clFOVCircleColor = ini.GetColor(PROTECT("AIMBOT"), PROTECT("m_clFOVCircleColor"));
			AIMBOT::m_iCurrentKEY = ini.GetInt(PROTECT("AIMBOT"), PROTECT("m_iCurrentKEY"));
			AIMBOT::m_iCurrentAimbotModeIndex = ini.GetInt(PROTECT("AIMBOT"), PROTECT("m_iCurrentAimbotModeIndex"));
			AIMBOT::m_iCurrentAimPosIndex = ini.GetInt(PROTECT("AIMBOT"), PROTECT("m_iCurrentAimPosIndex"));

			// WEAPONS
			ESP::WEAPONS::m_bEnableEquippedWeaponEsp = ini.GetBool(PROTECT("WEAPON"), PROTECT("m_bEnableEquippedWeaponEsp"));
			HITSERVICE::m_bEnableHitsound = ini.GetBool(PROTECT("WEAPON"), PROTECT("m_bEnableHitsound"));
			ESP::WEAPONS::m_clEquippedWeaponIconColor = ini.GetColor(PROTECT("WEAPON"), PROTECT("m_clEquippedWeaponIconColor"));
			ESP::WEAPONS::m_clEquippedWeaponIconStrokeColor = ini.GetColor(PROTECT("WEAPON"), PROTECT("m_clEquippedWeaponIconStrokeColor"));
		}
	}

	void ScanDirectoryForFile(const char* extension) {
		ConfigFiles.clear();
		if (!fs::exists(base_directory + configs_directory)) {
			std::cout << PROTECT("Directory does not exist: ") << base_directory + configs_directory << std::endl;
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
			std::cout << PROTECT("Error scanning directory: ") << e.what() << std::endl;
		}
	}

}; 

