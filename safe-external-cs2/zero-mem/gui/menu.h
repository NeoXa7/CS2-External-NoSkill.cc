#pragma once
#include <globals/imports.h>
#include <globals/utils.h>
#include <utils/resource_loader.h>
#include "animation.h"
#include "custom.h"
#include <utils/updater.h>
#include "settings_manager.h"
#include <globals/_flags.h>
#include <key_auth_system.h>
#include <cheats/_import.h>
#include <cheats/_config.h>
#include <gui/gifs.h>

Animation fade_in_fade_out(150.0f, 255.0f, _FLAGS_::m_flAnimationSpeed, false);
Animation pulse(255.0f, 255.0f, _FLAGS_::m_flAnimationSpeed, false);

enum TAB_INDEX : int {
	AIM_AIMBOT,
	AIM_TRIGGERBOT,
	AIM_RCS,
	VISUAL_PLAYER,
	VISUAL_WEAPON,
	VISUAL_WORLD,
	MISC_EXPLOITS,
	MISC_SCRIPT,
	MISC_SETTINGS
};


class Menu
{
private:
	UIComponents& uic = Instance<UIComponents>::Get();
	bool show_player_list = false;

	std::vector<std::string> aim_buttons = { "Aimbot", "Triggerbot", "RCS"};
	std::vector<int> aim_button_ids = { AIM_AIMBOT, AIM_TRIGGERBOT, AIM_RCS};
	std::vector<ImTextureID> aim_button_icons = {
		(ImTextureID)RES_LOADER::IMAGES::TARGET_ICON,
		(ImTextureID)RES_LOADER::IMAGES::MOUSE_ICON,
		(ImTextureID)RES_LOADER::IMAGES::ARROW_ICON
	};
	
	std::vector<std::string> visuals_buttons = { "Player", "Weapon", "World"};
	std::vector<int> visual_button_ids = { VISUAL_PLAYER, VISUAL_WEAPON, VISUAL_WORLD };
	std::vector<ImTextureID> visual_button_icons = {
		(ImTextureID)RES_LOADER::IMAGES::PERSON_ICON,
		(ImTextureID)RES_LOADER::IMAGES::GUN_ICON,
		(ImTextureID)RES_LOADER::IMAGES::WORLD_ICON
	};
	
	std::vector<std::string> misc_buttons = { "Exploits", "Scripts", "Settings"};
	std::vector<int> misc_button_ids = { MISC_EXPLOITS, MISC_SCRIPT, MISC_SETTINGS };
	std::vector<ImTextureID> misc_button_icons = {
		(ImTextureID)RES_LOADER::IMAGES::EXPLOITS_ICON,
		(ImTextureID)RES_LOADER::IMAGES::SCRIPTS_ICON,
		(ImTextureID)RES_LOADER::IMAGES::SETTINGS_ICON
	};

	void CreateAimAimbotUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Aimbot");
				uic.ToggleButton(PROTECT("Enable"), &AIMBOT::m_bEnableAimbot);
				uic.ToggleButton(PROTECT("Fov Based"), &AIMBOT::m_bFovBased);
				uic.ToggleButton(PROTECT("Show Fov Circle"), &AIMBOT::m_bShowFovCircle);
				uic.ToggleButton(PROTECT("Team Check"), &AIMBOT::m_bEnableTeamCheck);
				uic.ToggleButton(PROTECT("Sniper Check"), &AIMBOT::m_bEnableSniperScopeCheck);
				uic.ToggleButton(PROTECT("SR Check"), &AIMBOT::m_bEnableSniperRifleScopeCheck);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.ColorEditor(PROTECT("Fov"), &AIMBOT::m_clFOVCircleColor);
				uic.Slider<float>(PROTECT("Smoothness"), &AIMBOT::m_flSmoothness, 2.0f, 10.0f);
				uic.Slider<float>(PROTECT("FOV"), &AIMBOT::m_flFOV, 1.0f, 460.0f);
				uic.Slider<float>(PROTECT("Circle Thickness"), &AIMBOT::m_flFOVCircleThickness, 0.0f, 4.0f);
				uic.LeaveLine(2);
				uic.ComboBox(
					PROTECT(" Aim Position"),
					AIMBOT::m_AimPositions[AIMBOT::m_iCurrentAimPosIndex],
					&AIMBOT::m_iCurrentAimPosIndex,
					AIMBOT::m_AimPositions,
					IM_ARRAYSIZE(AIMBOT::m_AimPositions)
				);

				uic.LeaveLine(1);
				uic.RadioButtonGroup(PROTECT("Mode"), &AIMBOT::m_iCurrentAimbotModeIndex, AIMBOT::m_AvailableAimbotModes, IM_ARRAYSIZE(AIMBOT::m_AvailableAimbotModes), true);
				if (AIMBOT::m_iCurrentAimbotModeIndex == HOLD) {
					uic.LeaveLine(1);
					ImGui::TextColored(ImColor(255, 255, 255, 255), "Hotkey");
					uic.Hotkey(&AIMBOT::m_iCurrentKEY);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateAimTriggerBotUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			bool enable_trigger_bot = TRIGGER_BOT::m_bEnableTriggerBot.load();
			bool enable_trigger_bot_team_check = TRIGGER_BOT::m_bEnableTeamCheck.load();

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Triggerbot");

				if (uic.ToggleButton(PROTECT("Enable"), &enable_trigger_bot)) {
					TRIGGER_BOT::m_bEnableTriggerBot.store(enable_trigger_bot);
				}

				if (uic.ToggleButton(PROTECT("Team Check"), &enable_trigger_bot_team_check)) {
					TRIGGER_BOT::m_bEnableTeamCheck.store(enable_trigger_bot_team_check);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.Slider(PROTECT("Delay"), &TRIGGER_BOT::m_flTriggerDelay, 0.0f, 1000.0f);
				uic.Slider(PROTECT("Fire Rate"), &TRIGGER_BOT::m_flTriggerFireRate, 0.0f, 1000.0f);
				uic.LeaveLine(1);
				uic.RadioButtonGroup(PROTECT("Mode"), &TRIGGER_BOT::m_iCurrentTriggerModeIndex, TRIGGER_BOT::m_AvailableFireModes, IM_ARRAYSIZE(TRIGGER_BOT::m_AvailableFireModes), true);
				if (TRIGGER_BOT::m_iCurrentTriggerModeIndex == HOLD) {
					uic.LeaveLine(1);
					ImGui::TextColored(ImColor(255, 255, 255, 255), "Hotkey");
					uic.Hotkey(&TRIGGER_BOT::m_iCurrentTriggerKey);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateAimRCSUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("RCS");
				uic.ToggleButton(PROTECT("Enable"), &SRCS::m_bEnableSRCS);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.Slider(PROTECT("YAW"), &SRCS::m_flYAW, 1.0f, 3.0f);
				uic.Slider(PROTECT("PITCH"), &SRCS::m_flPITCH, 1.0f, 3.0f);
				uic.LeaveLine(1);
				uic.RadioButtonGroup(PROTECT("Mode"), &SRCS::m_iCurrentSRCSModeIndex, SRCS::m_AvailableModes, IM_ARRAYSIZE(SRCS::m_AvailableModes), true);
				if (SRCS::m_iCurrentSRCSModeIndex == HOLD) {
					uic.LeaveLine(1);
					ImGui::TextColored(ImColor(255, 255, 255, 255), "Hotkey");
					uic.Hotkey(&SRCS::m_iCurrentSRCSKey);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateVisualPlayerUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Player");
				uic.ToggleButton(PROTECT("Enable"), &ESP::PLAYER::m_bEnablePlayerEsp);
				uic.ToggleButton(PROTECT("Box"), &ESP::PLAYER::m_bEnableBox);
				uic.ToggleButton(PROTECT("Filled"), &ESP::PLAYER::m_bEnableBoxFilled);
				uic.ToggleButton(PROTECT("Image"), &ESP::PLAYER::m_bEnableBoxImage);
				uic.ToggleButton(PROTECT("Lines"), &ESP::PLAYER::m_bEnableSnapLines);
				uic.ToggleButton(PROTECT("Health"), &ESP::PLAYER::m_bEnableHealthBar);
				uic.ToggleButton(PROTECT("Text"), &ESP::PLAYER::m_bEnableHealthText);
				uic.ToggleButton(PROTECT("Armor"), &ESP::PLAYER::m_bEnableArmorBar);
				uic.ToggleButton(PROTECT("Bone"), &ESP::PLAYER::m_bEnableBones);
				uic.ToggleButton(PROTECT("Joint"), &ESP::PLAYER::m_bEnableBonesJoints);
				uic.ToggleButton(PROTECT("Head"), &ESP::PLAYER::m_bEnableHead);
				uic.ToggleButton(PROTECT("Filled##head"), &ESP::PLAYER::m_bEnableHeadFilled);
				uic.ToggleButton(PROTECT("Rays"), &ESP::PLAYER::m_bEnableEyeRays);
				uic.ToggleButton(PROTECT("Names"), &ESP::PLAYER::m_bEnableNames);
				uic.ToggleButton(PROTECT("Distance"), &ESP::PLAYER::m_bEnableDistanceEsp);
				uic.ToggleButton(PROTECT("Crosshair"), &CROSSHAIR::m_bEnableCrosshair);
				uic.ToggleButton(PROTECT("Team Check"), &ESP::PLAYER::m_bTeamCheck);
				uic.ToggleButton(PROTECT("Dormant Check"), &ESP::PLAYER::m_bDormantCheck);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.ColorEditor(PROTECT("Box"), &ESP::PLAYER::m_clBoxUnfilledColor);
				uic.ColorEditor(PROTECT("Fill"), &ESP::PLAYER::m_clBoxFilledColor);
				uic.ColorEditor(PROTECT("Line"), &ESP::PLAYER::m_clLineColor);
				uic.ColorEditor(PROTECT("Point"), &ESP::PLAYER::m_clLinePointColor);
				uic.ColorEditor(PROTECT("Name"), &ESP::PLAYER::m_clNameColor);
				uic.ColorEditor(PROTECT("Stroke##name"), &ESP::PLAYER::m_clNameStrokeColor);
				uic.ColorEditor(PROTECT("Health"), &ESP::PLAYER::m_clHealthTextColor);
				uic.ColorEditor(PROTECT("Stroke##health"), &ESP::PLAYER::m_clHealthTextStrokeColor);
				uic.ColorEditor(PROTECT("Armor"), &ESP::PLAYER::m_clArmorBarColor);
				uic.ColorEditor(PROTECT("Stroke"), &ESP::PLAYER::m_clDistanceTextStrokeColor);
				uic.ColorEditor(PROTECT("Bone"), &ESP::PLAYER::m_clBoneColor);
				uic.ColorEditor(PROTECT("Head"), &ESP::PLAYER::m_clBoneHeadColor);
				uic.ColorEditor(PROTECT("Joint"), &ESP::PLAYER::m_clBoneJointsColor);
				uic.ColorEditor(PROTECT("Distance"), &ESP::PLAYER::m_clDistanceTextColor);
				uic.ColorEditor(PROTECT("Crosshair"), &CROSSHAIR::m_clCrossHairColor);
				uic.Slider(PROTECT("Crosshair Size"), &CROSSHAIR::m_flCrossHairSize, 0.0f, 40.0f);
				uic.Slider(PROTECT("Box Thickness"), &ESP::PLAYER::m_flBoxUnfilledThickness, 0.0f, 3.0f);
				uic.Slider(PROTECT("Box Radius"), &ESP::PLAYER::m_flBoxRounding, 0.0f, 6.0f);
				uic.Slider(PROTECT("Line Thickness"), &ESP::PLAYER::m_flLinesThickness, 0.0f, 3.0f);
				uic.Slider(PROTECT("Bone Thickness"), &ESP::PLAYER::m_flBonesThickness, 0.0f, 3.0f);
				uic.Slider(PROTECT("Joint Radius"), &ESP::PLAYER::m_flJointRadius, 0.0f, 3.0f);
				uic.RadioButtonGroup(PROTECT(" Line Position"), &ESP::PLAYER::m_iCurrentLinePosIndex, ESP::PLAYER::m_AvailableSnapLinesPos, IM_ARRAYSIZE(ESP::PLAYER::m_AvailableSnapLinesPos), false);
				uic.RadioButtonGroup(PROTECT(" Box Texture"), &ESP::PLAYER::m_iCurrentImageIndex, ESP::PLAYER::m_AvailableImages, IM_ARRAYSIZE(ESP::PLAYER::m_AvailableImages), false);
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateVisualWeaponsUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Weapons");
				uic.ToggleButton(PROTECT("Equipped Weapons"), &ESP::WEAPONS::m_bEnableEquippedWeaponEsp);
				uic.ToggleButton(PROTECT("Hitsound"), &HITSERVICE::m_bEnableHitsound);
				uic.LeaveLine(2);
				HITSERVICE::ScanDirectoryForFile(PROTECT(".wav"));

				if (!HITSERVICE::wav_files.empty()) {
					static int m_iSelectedHitSoundIndex = 0;
					std::vector<const char*> wav_files_cstr;

					for (const auto& file : HITSERVICE::wav_files) {
						wav_files_cstr.push_back(file.c_str());
					}

					uic.ComboBox(
						PROTECT("HitSound (.wav)"),
						HITSERVICE::wav_files[m_iSelectedHitSoundIndex].c_str(),
						&m_iSelectedHitSoundIndex,
						wav_files_cstr.data(),
						wav_files_cstr.size()
					);
					HITSERVICE::file_name = HITSERVICE::wav_files[m_iSelectedHitSoundIndex];
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.ColorEditor(PROTECT("Color"), &ESP::WEAPONS::m_clEquippedWeaponIconColor);
				uic.ColorEditor(PROTECT("Stroke"), &ESP::WEAPONS::m_clEquippedWeaponIconStrokeColor);
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateVisualWorldUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("World");
				uic.ToggleButton(PROTECT("Dropped Weapons"), &ESP::WORLD::m_bEnableDroppedWeaponEsp);
				uic.ToggleButton(PROTECT("Projectiles"), &ESP::WORLD::m_bEnableProjectilesEsp);
				uic.ToggleButton(PROTECT("Entities"), &ESP::WORLD::m_bEnableEntitiesEsp);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle(PROTECT("Configurations"));
				uic.ColorEditor(PROTECT("Dropped Weapon"), &ESP::WORLD::m_clDroppedWeaponColor);
				uic.ColorEditor(PROTECT("Stroke##weapon"), &ESP::WORLD::m_clDroppedWeaponStrokeColor);
				uic.ColorEditor(PROTECT("Projectiles"), &ESP::WORLD::m_clProjectilesColor);
				uic.ColorEditor(PROTECT("Stroke##projectile"), &ESP::WORLD::m_clProjectilesStrokeColor);
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateMiscExploitsUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			bool flash_alpha_override = MEMORY::m_bEnableFlashAlphaOverride.load();
			bool smoke_alpha_override = MEMORY::m_bEnableSmokeAlphaOverride.load();
			bool smoke_color_override = MEMORY::m_bEnableSmokeColorOverride.load();
			bool camera_fov_override = MEMORY::m_bEnableCameraFovOverride.load();
			bool exposure_override = MEMORY::m_bExposureOverride.load();
			bool sky_color_override = MEMORY::m_bEnableSkyColorOverride.load();

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Exploits");
				ImGui::PushStyleColor(ImGuiCol_Text, ImColor(237, 67, 67, 255).Value);
				ImGui::TextWrapped("These exploits are a one-way ticket to a  1000%% guaranteed ban. Use them at your  own risk, genius. Restart the game after  enabling it if you change your mind and  want to disable it.");
				uic.LeaveLine(1);
				ImGui::PopStyleColor(1);

				if (uic.ToggleButton(PROTECT("Override Flash Alpha"), &flash_alpha_override)) {
					MEMORY::m_bEnableFlashAlphaOverride.store(flash_alpha_override);
				}

				if (uic.ToggleButton(PROTECT("Override Smoke Alpha"), &smoke_alpha_override)) {
					MEMORY::m_bEnableSmokeAlphaOverride.store(smoke_alpha_override);
				}

				if (uic.ToggleButton(PROTECT("Override Smoke Color"), &smoke_color_override)) {
					MEMORY::m_bEnableSmokeColorOverride.store(smoke_color_override);
				}

				if (uic.ToggleButton(PROTECT("Override Camera FOV"), &camera_fov_override)) {
					MEMORY::m_bEnableCameraFovOverride.store(camera_fov_override);
				}

				if (uic.ToggleButton(PROTECT("Override Exposure"), &exposure_override)) {
					MEMORY::m_bExposureOverride.store(exposure_override);
				}

				if (uic.ToggleButton(PROTECT("Override Sky Color"), &sky_color_override)) {
					MEMORY::m_bEnableSkyColorOverride.store(sky_color_override);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.Slider<float>(PROTECT("Flash Alpha"), &MEMORY::m_flFlashAlpha, 0.0f, 255.0f);
				uic.Slider<int>(PROTECT("Camera FOV"), &MEMORY::m_iDefaultFOV, 1, 150);
				uic.Slider<float>(PROTECT("Exposure"), &MEMORY::m_flExposure, 0.0f, 1.0f);
				uic.ColorEditor(PROTECT("Sky Color"), (ImColor*)&MEMORY::m_clSkyColor);
				uic.ColorEditor(PROTECT("Smoke Color"), (ImColor*)&MEMORY::m_clSmokeColor);
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateMiscSettingsUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(PROTECT("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Offsets");

				ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 200).Value);

				if (uic.Button("Download Latest", 150.0f, 30.0f)) {
					std::thread download_thread(&Updater::DownloadOffsets, &Instance<Updater>::Get());
					download_thread.detach();
				}

				if (uic.Button("Reload", 150.0f, 30.0f)) {
					Instance<Updater>::Get().UpdateOffsets();
				}

				//ImGui::TextWrapped(PROTECT("If you're unable to download/update offsets using the button above,try downloading them manually- from the provided links and put them into- the offsets folder!"));

				ImGui::TextLinkOpenURL(PROTECT("Offsets.json"), "https://raw.githubusercontent.com/a2x/cs2-dumper/refs/heads/main/output/offsets.json");
				ImGui::TextLinkOpenURL(PROTECT("ClientDll.json"), "https://raw.githubusercontent.com/a2x/cs2-dumper/refs/heads/main/output/client_dll.json");
				ImGui::TextLinkOpenURL(PROTECT("Buttons.json"), "https://raw.githubusercontent.com/a2x/cs2-dumper/refs/heads/main/output/buttons.json");

				uic.LeaveLine(2);
				uic.DrawTitle(PROTECT("Settings"));

				uic.ToggleButton(PROTECT("Automatic Update"), &_FLAGS_::m_bAutomaticUpdate);
				uic.ToggleButton(PROTECT("Show Overlay Texts"), &_FLAGS_::m_bShowText);

				if (uic.Button("Save", 150.0f, 30.0f)) {
					settings.SaveSettings();
				}

				ImGui::PopStyleColor();
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(PROTECT("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configs");

				ConfigManager& configs = Instance<ConfigManager>::Get();

				configs.ScanDirectoryForFile(CONFIG_FILE_EXTENSION);

				static char buffer[MAX_BUFFER_SIZE * 2] = "Config Name";

				ImGui::SetNextItemWidth(150.0f);
				uic.InputBoxWithPlaceholder(PROTECT("##config_name"), "Config Name", buffer, sizeof(buffer));

				if (uic.Button(PROTECT("Save Config"), 150.0f, 30.0f)) {
					configs.file_name = buffer;
					configs.CreateConfig();
				}

				uic.LeaveLine();

				if (uic.Button(PROTECT("Load Config"), 150.0f, 30.0f)) {
					configs.LoadConfig();
				}

				uic.LeaveLine();

				if (!configs.ConfigFiles.empty()) {
					static int SELECTED_CONFIG_INI_FILE_INDEX = 0;
					std::vector<const char*> config_files_cstr;

					for (unsigned int i = 0; i < configs.ConfigFiles.size(); ++i) {
						config_files_cstr.push_back(configs.ConfigFiles[i].c_str());
					}

					std::string SELECTED_FILE_NAME = config_files_cstr[SELECTED_CONFIG_INI_FILE_INDEX];
					uic.ComboBox(
						PROTECT(" Select File"),
						SELECTED_FILE_NAME.c_str(),
						&SELECTED_CONFIG_INI_FILE_INDEX,
						config_files_cstr.data(),
						config_files_cstr.size()
					);
					//uic.ComboBox(PROTECT("Select File"), SELECTED_FILE_NAME.c_str(), &SELECTED_CONFIG_INI_FILE_INDEX, config_files_cstr.data(), config_files_cstr.size(), 0.0f);
					configs.file_name = config_files_cstr[SELECTED_CONFIG_INI_FILE_INDEX];

					if (uic.Button("Delete", 150.0f, 30.0f)) {
						std::string path = "bin\\configs\\" + configs.file_name;
						fs::remove(path);
					}
				}

				uic.LeaveLine(2);

				uic.DrawTitle("Hotkeys");

				uic.Hotkey(&_FLAGS_::m_iEndProgramKey, ImVec2(130.0f, 25.0f));
				ImGui::SameLine(0, -2.0f);
				ImGui::TextColored(ImColor(255,255,255, 200), "Panic Key (Exits)");

				uic.Hotkey(&_FLAGS_::m_iVisibilityToggleKey, ImVec2(130.0f, 25.0f));
				ImGui::SameLine(0, -2.0f);
				ImGui::TextColored(ImColor(255, 255, 255, 200), "Visibility Toggle");

				uic.Hotkey(&_FLAGS_::m_iLoadUnloadCheatsKey, ImVec2(130.0f, 25.0f));
				ImGui::SameLine(0, -2.0f);
				ImGui::TextColored(ImColor(255, 255, 255, 200), "Load/Unload");

				uic.LeaveLine(1);
				if (uic.Button("Save", 130.0f, 30.0f)) {
					settings.SaveSettings();
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

public:
	bool m_bVisible = true;
	
	void Render() {	
		uic.SetStyles();
		ImGui::SetNextWindowSize(ImVec2(750, 520));

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin(PROTECT("Zero Memory | CS2 External"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings)) {
			uic.WindowPosition = ImGui::GetWindowPos();
			uic.WindowSize= ImGui::GetWindowSize();
			uic.CursorPosition = ImGui::GetCursorPos();
			uic.DrawList = ImGui::GetWindowDrawList();

			static int SELECTED_BUTTON = 0;

			ImGui::PushFont(RES_LOADER::FONTS::PANAROMA_UI_FONT);

			Instance<Particles>::Get().DrawRandomConstellationParticles();
			uic.DrawHeader(0.0f, 60.0f);
			uic.DrawSideBar(0.0f, 200.0f);

			ImGui::SetCursorPos(ImVec2(20, 50));
			ImGui::TextColored(ImColor(255, 255, 255, (SELECTED_BUTTON == 0 || SELECTED_BUTTON == 1 || SELECTED_BUTTON == 2) ? 195 : 55), "AIM");
			uic.DrawList->AddLine(
				ImVec2(ImGui::GetCursorScreenPos().x + 50.f, ImGui::GetCursorScreenPos().y - 8.0f),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x - 630.0f, ImGui::GetCursorScreenPos().y - 8.0f),
				ImColor(255, 255, 255, (SELECTED_BUTTON == 0 || SELECTED_BUTTON == 1 || SELECTED_BUTTON == 2) ? 195 : 55),
				2.0f
			);
			uic.DrawVerticalButtons(aim_buttons, aim_button_ids, SELECTED_BUTTON, aim_button_icons, 180.0f, 30.0f, 8.0f);

			ImGui::SetCursorPos(ImVec2(20, 185));
			ImGui::TextColored(ImColor(255, 255, 255, (SELECTED_BUTTON == 3 || SELECTED_BUTTON == 4 || SELECTED_BUTTON == 5) ? 195 : 55), "VISUAL");
			uic.DrawList->AddLine(
				ImVec2(ImGui::GetCursorScreenPos().x + 65.f, ImGui::GetCursorScreenPos().y - 8.0f),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x - 615.0f, ImGui::GetCursorScreenPos().y - 8.0f),
				ImColor(255, 255, 255, (SELECTED_BUTTON == 3 || SELECTED_BUTTON == 4 || SELECTED_BUTTON == 5) ? 195 : 55),
				2.0f
			);
			uic.DrawVerticalButtons(visuals_buttons, visual_button_ids, SELECTED_BUTTON, visual_button_icons, 180.0f, 30.0f, 8.0f);

			ImGui::SetCursorPos(ImVec2(20, 320));
			ImGui::TextColored(ImColor(255, 255, 255, (SELECTED_BUTTON == 6 || SELECTED_BUTTON == 7 || SELECTED_BUTTON == 8) ? 195 : 55), "MISC");
			uic.DrawList->AddLine(
				ImVec2(ImGui::GetCursorScreenPos().x + 55.f, ImGui::GetCursorScreenPos().y - 8.0f),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x - 630.0f, ImGui::GetCursorScreenPos().y - 8.0f),
				ImColor(255, 255, 255, (SELECTED_BUTTON == 6 || SELECTED_BUTTON == 7 || SELECTED_BUTTON == 8) ? 195 : 55),
				2.0f
			);
			uic.DrawVerticalButtons(this->misc_buttons, this->misc_button_ids, SELECTED_BUTTON, this->misc_button_icons, 180.0f, 30.0f, 8.0f);

			ImGui::SetCursorPos(ImVec2(20, 520));
			uic.DrawList->AddLine(
				ImVec2(ImGui::GetCursorScreenPos().x - 50.0f, ImGui::GetCursorScreenPos().y - 60.0f),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x - 550.0f, ImGui::GetCursorScreenPos().y - 60.0f),
				ImColor(255, 255, 255, 55),
				2.0f
			);

			for (int i = 0; i < KAA.user_data.subscriptions.size(); i++) {
				auto sub = KAA.user_data.subscriptions.at(i);
				uic.DrawProfile2(LocalPlayer.Name, (LocalPlayer.Team == T_TERRORIST ? T_COLOR : CT_COLOR), tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry))).c_str());
			}

			ImGui::PopStyleVar(1);

			//ImGui::SetCursorPos(ImVec2(220, 70)); // Position right of sidebar
			//ImGui::BeginChild("ContentPanel", ImVec2(510, 440), false); // Reserve space

			//ImGui::EndChild();

			switch (SELECTED_BUTTON) {
			case AIM_AIMBOT : 
				this->CreateAimAimbotUI();
				break;
			case AIM_TRIGGERBOT:
				this->CreateAimTriggerBotUI();
				break;
			case AIM_RCS :
				this->CreateAimRCSUI();
				break;
			case VISUAL_PLAYER :
				this->CreateVisualPlayerUI();
				break;
			case VISUAL_WEAPON:
				this->CreateVisualWeaponsUI();
				break;
			case VISUAL_WORLD :
				this->CreateVisualWorldUI();
				break;
			case MISC_EXPLOITS:
				this->CreateMiscExploitsUI();
				break;
			case MISC_SCRIPT:
				break;
			case MISC_SETTINGS:
				this->CreateMiscSettingsUI();
				break;
			}

			ImGui::PopFont();
		}

		ImGui::End();

	}

	void RenderList(std::vector<CEntity>& list) {
		//if(this->show_player_list)
		//	//this->CreatePlayerListUI(list);
	}
};