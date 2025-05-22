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
		if (uic.BeginColumn(Protect("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Aimbot");
				uic.ToggleButton(Protect("Enable"), &Aimbot::m_bEnableAimbot);
				uic.ToggleButton(Protect("Fov Based"), &Aimbot::m_bFovBased);
				uic.ToggleButton(Protect("Show Fov Circle"), &Aimbot::m_bShowFovCircle);
				uic.ToggleButton(Protect("Visible Check"), &Aimbot::m_bEnableVisibilityCheck);
				uic.ToggleButton(Protect("Team Check"), &Aimbot::m_bEnableTeamCheck);
				uic.ToggleButton(Protect("Sniper Check"), &Aimbot::m_bEnableSniperScopeCheck);
				uic.ToggleButton(Protect("SR Check"), &Aimbot::m_bEnableSniperRifleScopeCheck);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.ColorEditor(Protect("Fov"), &Aimbot::m_clFOVCircleColor);
				uic.Slider<float>(Protect("Smoothness"), &Aimbot::m_flSmoothness, 2.0f, 10.0f);
				uic.Slider<float>(Protect("FOV"), &Aimbot::m_flFOV, 1.0f, 460.0f);
				uic.Slider<float>(Protect("Circle Thickness"), &Aimbot::m_flFOVCircleThickness, 0.0f, 4.0f);
				uic.LeaveLine(1);
				uic.RadioButtonGroup(Protect("Mode"), &Aimbot::m_iCurrentAimbotModeIndex, Aimbot::m_AvailableAimbotModes, IM_ARRAYSIZE(Aimbot::m_AvailableAimbotModes), true);
				if (Aimbot::m_iCurrentAimbotModeIndex == HOLD) {
					uic.LeaveLine(1);
					ImGui::TextColored(ImColor(255, 255, 255, 255), "Hotkey");
					uic.Hotkey(&Aimbot::m_iCurrentKEY);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateAimTriggerBotUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(Protect("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			bool enable_trigger_bot = TRIGGER_BOT::m_bEnableTriggerBot.load();
			bool enable_trigger_bot_team_check = TRIGGER_BOT::m_bEnableTeamCheck.load();

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Triggerbot");

				if (uic.ToggleButton(Protect("Enable"), &enable_trigger_bot)) {
					TRIGGER_BOT::m_bEnableTriggerBot.store(enable_trigger_bot);
				}

				if (uic.ToggleButton(Protect("Team Check"), &enable_trigger_bot_team_check)) {
					TRIGGER_BOT::m_bEnableTeamCheck.store(enable_trigger_bot_team_check);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.Slider(Protect("Delay"), &TRIGGER_BOT::m_flTriggerDelay, 0.0f, 1000.0f);
				uic.Slider(Protect("Fire Rate"), &TRIGGER_BOT::m_flTriggerFireRate, 0.0f, 1000.0f);
				uic.LeaveLine(1);
				uic.RadioButtonGroup(Protect("Mode"), &TRIGGER_BOT::m_iCurrentTriggerModeIndex, TRIGGER_BOT::m_AvailableFireModes, IM_ARRAYSIZE(TRIGGER_BOT::m_AvailableFireModes), true);
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
		if (uic.BeginColumn(Protect("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("RCS");
				uic.ToggleButton(Protect("Enable"), &SRCS::m_bEnableSRCS);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.Slider(Protect("YAW"), &SRCS::m_flYAW, 1.0f, 3.0f);
				uic.Slider(Protect("PITCH"), &SRCS::m_flPITCH, 1.0f, 3.0f);
				uic.LeaveLine(1);
				uic.RadioButtonGroup(Protect("Mode"), &SRCS::m_iCurrentSRCSModeIndex, SRCS::m_AvailableModes, IM_ARRAYSIZE(SRCS::m_AvailableModes), true);
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
		if (uic.BeginColumn(Protect("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Player");
				uic.ToggleButton(Protect("Enable"), &ESP::PLAYER::m_bEnablePlayerEsp);
				uic.ToggleButton(Protect("Box"), &ESP::PLAYER::m_bEnableBox);
				uic.ToggleButton(Protect("Filled"), &ESP::PLAYER::m_bEnableBoxFilled);
				uic.ToggleButton(Protect("Image"), &ESP::PLAYER::m_bEnableBoxImage);
				uic.ToggleButton(Protect("Lines"), &ESP::PLAYER::m_bEnableSnapLines);
				uic.ToggleButton(Protect("Health"), &ESP::PLAYER::m_bEnableHealthBar);
				uic.ToggleButton(Protect("Text"), &ESP::PLAYER::m_bEnableHealthText);
				uic.ToggleButton(Protect("Armor"), &ESP::PLAYER::m_bEnableArmorBar);
				uic.ToggleButton(Protect("Bone"), &ESP::PLAYER::m_bEnableBones);
				uic.ToggleButton(Protect("Joint"), &ESP::PLAYER::m_bEnableBonesJoints);
				uic.ToggleButton(Protect("Head"), &ESP::PLAYER::m_bEnableHead);
				uic.ToggleButton(Protect("Filled##head"), &ESP::PLAYER::m_bEnableHeadFilled);
				uic.ToggleButton(Protect("Rays"), &ESP::PLAYER::m_bEnableEyeRays);
				uic.ToggleButton(Protect("Names"), &ESP::PLAYER::m_bEnableNames);
				uic.ToggleButton(Protect("Distance"), &ESP::PLAYER::m_bEnableDistanceEsp);
				uic.ToggleButton(Protect("Crosshair"), &CROSSHAIR::m_bEnableCrosshair);
				uic.ToggleButton(Protect("Team Check"), &ESP::PLAYER::m_bTeamCheck);
				uic.ToggleButton(Protect("Dormant Check"), &ESP::PLAYER::m_bDormantCheck);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.ColorEditor(Protect("Box"), &ESP::PLAYER::m_clBoxUnfilledColor);
				uic.ColorEditor(Protect("Fill"), &ESP::PLAYER::m_clBoxFilledColor);
				uic.ColorEditor(Protect("Line"), &ESP::PLAYER::m_clLineColor);
				uic.ColorEditor(Protect("Point"), &ESP::PLAYER::m_clLinePointColor);
				uic.ColorEditor(Protect("Name"), &ESP::PLAYER::m_clNameColor);
				uic.ColorEditor(Protect("Stroke##name"), &ESP::PLAYER::m_clNameStrokeColor);
				uic.ColorEditor(Protect("Health"), &ESP::PLAYER::m_clHealthTextColor);
				uic.ColorEditor(Protect("Stroke##health"), &ESP::PLAYER::m_clHealthTextStrokeColor);
				uic.ColorEditor(Protect("Armor"), &ESP::PLAYER::m_clArmorBarColor);
				uic.ColorEditor(Protect("Stroke"), &ESP::PLAYER::m_clDistanceTextStrokeColor);
				uic.ColorEditor(Protect("Bone"), &ESP::PLAYER::m_clBoneColor);
				uic.ColorEditor(Protect("Head"), &ESP::PLAYER::m_clBoneHeadColor);
				uic.ColorEditor(Protect("Joint"), &ESP::PLAYER::m_clBoneJointsColor);
				uic.ColorEditor(Protect("Distance"), &ESP::PLAYER::m_clDistanceTextColor);
				uic.Slider(Protect("Crosshair Size"), &CROSSHAIR::CrossHairSize, 0.0f, 40.0f);
				uic.Slider(Protect("Box Thickness"), &ESP::PLAYER::m_flBoxUnfilledThickness, 0.0f, 3.0f);
				uic.Slider(Protect("Box Radius"), &ESP::PLAYER::m_flBoxRounding, 0.0f, 6.0f);
				uic.Slider(Protect("Line Thickness"), &ESP::PLAYER::m_flLinesThickness, 0.0f, 3.0f);
				uic.Slider(Protect("Bone Thickness"), &ESP::PLAYER::m_flBonesThickness, 0.0f, 3.0f);
				uic.Slider(Protect("Joint Radius"), &ESP::PLAYER::m_flJointRadius, 0.0f, 3.0f);
				uic.RadioButtonGroup(Protect(" Line Position"), &ESP::PLAYER::m_iCurrentLinePosIndex, ESP::PLAYER::m_AvailableSnapLinesPos, IM_ARRAYSIZE(ESP::PLAYER::m_AvailableSnapLinesPos), false);
				uic.RadioButtonGroup(Protect(" Box Texture"), &ESP::PLAYER::m_iCurrentImageIndex, ESP::PLAYER::m_AvailableImages, IM_ARRAYSIZE(ESP::PLAYER::m_AvailableImages), false);
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateVisualWeaponsUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(Protect("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Weapons");
				uic.ToggleButton(Protect("Equipped Weapons"), &ESP::WEAPONS::m_bEnableEquippedWeaponEsp);
				uic.ToggleButton(Protect("Hitsound"), &HITSERVICE::m_bEnableHitsound);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.ColorEditor(Protect("Color"), &ESP::WEAPONS::m_clEquippedWeaponIconColor);
				uic.ColorEditor(Protect("Stroke"), &ESP::WEAPONS::m_clEquippedWeaponIconStrokeColor);
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}

	void CreateVisualWorldUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(Protect("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("World");
				uic.ToggleButton(Protect("Dropped Weapons"), &ESP::WORLD::m_bEnableDroppedWeaponEsp);
				uic.ToggleButton(Protect("Projectiles"), &ESP::WORLD::m_bEnableProjectilesEsp);
				uic.ToggleButton(Protect("Entities"), &ESP::WORLD::m_bEnableEntitiesEsp);
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.ColorEditor(Protect("Dropped Weapon"), &ESP::WORLD::m_clDroppedWeaponColor);
				uic.ColorEditor(Protect("Stroke##weapon"), &ESP::WORLD::m_clDroppedWeaponStrokeColor);
				uic.ColorEditor(Protect("Projectiles"), &ESP::WORLD::m_clProjectilesColor);
				uic.ColorEditor(Protect("Stroke##projectile"), &ESP::WORLD::m_clProjectilesStrokeColor);
			}
			uic.EndFrame();
		}

		uic.EndColumn();
	}
	
	void CreateMiscExploitsUI() {
		ImGui::SetCursorPos(ImVec2(220, 70));
		if (uic.BeginColumn(Protect("##left-column"), ImVec2((500.0f / 2.0f), 0))) {
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

				if (uic.ToggleButton(Protect("Change Flash Alpha"), &flash_alpha_override)) {
					MEMORY::m_bEnableFlashAlphaOverride.store(flash_alpha_override);
				}

				if (uic.ToggleButton(Protect("Change Smoke Alpha"), &smoke_alpha_override)) {
					MEMORY::m_bEnableSmokeAlphaOverride.store(smoke_alpha_override);
				}

				if (uic.ToggleButton(Protect("Change Smoke Color"), &smoke_color_override)) {
					MEMORY::m_bEnableSmokeColorOverride.store(smoke_color_override);
				}

				if (uic.ToggleButton(Protect("Change Camera FOV"), &camera_fov_override)) {
					MEMORY::m_bEnableCameraFovOverride.store(camera_fov_override);
				}

				if (uic.ToggleButton(Protect("Change Exposure"), &exposure_override)) {
					MEMORY::m_bExposureOverride.store(exposure_override);
				}

				if (uic.ToggleButton(Protect("Change Sky Color"), &sky_color_override)) {
					MEMORY::m_bEnableSkyColorOverride.store(sky_color_override);
				}
			}
			uic.EndFrame();
		}

		uic.EndColumn();

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f); // 20px spacing

		if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((500.0f / 2.0f), 0))) {
			float total_height = ImGui::GetContentRegionAvail().y;
			float padding = 6.0f;
			float frame_height = (total_height - padding);

			if (uic.BeginFrame(1, ImVec2(0, frame_height - 5.0f))) {
				uic.DrawTitle("Configurations");
				uic.Slider<float>(Protect("Flash Alpha"), &MEMORY::m_flFlashAlpha, 0.0f, 255.0f);
				uic.Slider<int>(Protect("Camera FOV"), &MEMORY::m_iDefaultFOV, 1, 150);
				uic.Slider<float>(Protect("Exposure"), &MEMORY::m_flExposure, 0.0f, 1.0f);
				uic.ColorEditor(Protect("Sky Color"), (ImColor*) & MEMORY::m_clSkyColor);
				uic.ColorEditor(Protect("Smoke Color"), (ImColor*) & MEMORY::m_clSmokeColor);
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

		if (ImGui::Begin(xorstr_("Zero Memory | CS2 External"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings)) {
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

			uic.DrawProfile("CR7", (ImTextureID)RES_LOADER::IMAGES::T_ICON);

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