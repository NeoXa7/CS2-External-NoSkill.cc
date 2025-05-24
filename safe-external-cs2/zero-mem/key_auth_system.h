#pragma once
#include <libs/lazy.h>
#include <libs/keyauth.cc/auth.hpp>
#include <libs/keyauth.cc/skStr.h>
#include <libs/keyauth.cc//utils.hpp>
#include <libs/xorstr.h>
#include <utils/console.h>

std::string name = xorstr_("NoSkill.cc");
std::string ownerid = xorstr_("bv6UWJfoiz");
std::string secret = xorstr_("9e06931b982d57acf48d8f92dd86d1687e4f78cc3a4d1097ce99e9fa601e5b1d");
std::string version = xorstr_("1.0");
std::string url = xorstr_("https://keyauth.win/api/1.3/");
std::string path = xorstr_("");

KeyAuth::api KAA(name, ownerid, version, url, path);

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S", &ctx); // %Z

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}

void sessionStatus() {
    KAA.check(true); // do NOT specify true usually, it is slower and will get you blocked from API
    if (!KAA.response.success) {
        LI_FN(printf).get()(KAA.response.message.c_str());
    }

    if (KAA.response.isPaid) {
        while (true) {
            Sleep(20000); // this MUST be included or else you get blocked from API
            KAA.check();
            if (!KAA.response.success) {
                LI_FN(printf).get()(KAA.response.message.c_str());
            }
        }
    }
}


const std::string compilation_date = (std::string)xorstr_(__DATE__);
const std::string compilation_time = (std::string)xorstr_(__TIME__);

//void SetupMenu() {
//	if (_FLAGS_::m_bAnimateUI) { // animation begins
//		pulse.Speed = _FLAGS_::m_flAnimationSpeed;
//		fade_in_fade_out.Speed = _FLAGS_::m_flAnimationSpeed;
//		fade_in_fade_out.AnimateFadeInFadeOut();
//		pulse.AnimateFadeInFadeOut();
//	}
//
//	uic.DrawBorder(uic.WindowPosition, uic.WindowSize, 0.0f, 1.0f, ImColor(23, 23, 23, 200));
//	uic.SetLogo((ImTextureID)(RES_LOADER::IMAGES::NO_SKILL_CC_LOGO), ImVec2(270, 50));
//
//	ImGui::PushFont(RES_LOADER::FONTS::FONT_AWESOME);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 100, 10));
//	if (ImGui::Button(I_MINIMIZE, ImVec2(40.0f, 0))) {
//		this->m_bVisible = false;
//	}
//
//	ImGui::SameLine();
//
//	ImGui::SetNextItemWidth(100.0f);
//	if (ImGui::Button(I_CLOSE, ImVec2(40.0f, 0))) {
//		EXIT;
//	}
//
//	ImGui::PopFont();
//}
//
//void ShowEndCredits() {
//	for (int i = 0; i < KAA.user_data.subscriptions.size(); i++) {
//		auto sub = KAA.user_data.subscriptions.at(i);
//		std::string label = xorstr_("NoSkill.cc | CS2 External v1.0 | Expire : ") + tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
//		uic.CenterText(label.c_str(), 550.0f, ImColor(255, 255, 255, (int)pulse.Alpha).Value);
//	}
//}
//
//void CreateVisualsUI() {
//	if (uic.BeginColumn(xorstr_("##left-column"), ImVec2((ImGui::GetContentRegionAvail().x / 2.0f), -20)))
//	{
//		if (uic.BeginFrame(1, ImVec2(0, (ImGui::GetContentRegionAvail().y)))) {
//			uic.CenterText(xorstr_("VISUALS FEATURES"), avg_pads, ImColor(255, 255, 255, 255).Value);
//			uic.Checkbox(xorstr_(" Player"), &ESP::PLAYER::m_bEnablePlayerEsp);
//			uic.Checkbox(xorstr_(" Box"), &ESP::PLAYER::m_bEnableBox);
//			uic.Checkbox(xorstr_(" Filled Box"), &ESP::PLAYER::m_bEnableBoxFilled);
//			uic.Checkbox(xorstr_(" Image Box"), &ESP::PLAYER::m_bEnableBoxImage);
//			uic.Checkbox(xorstr_(" Snap Lines"), &ESP::PLAYER::m_bEnableSnapLines);
//			uic.Checkbox(xorstr_(" Health Bar"), &ESP::PLAYER::m_bEnableHealthBar);
//			uic.Checkbox(xorstr_(" Health Text"), &ESP::PLAYER::m_bEnableHealthText);
//			uic.Checkbox(xorstr_(" Armor Bar"), &ESP::PLAYER::m_bEnableArmorBar);
//			uic.Checkbox(xorstr_(" Bones"), &ESP::PLAYER::m_bEnableBones);
//			uic.Checkbox(xorstr_(" Joints"), &ESP::PLAYER::m_bEnableBonesJoints);
//			uic.Checkbox(xorstr_(" Head"), &ESP::PLAYER::m_bEnableHead);
//			uic.Checkbox(xorstr_(" Head Filled"), &ESP::PLAYER::m_bEnableHeadFilled);
//			uic.Checkbox(xorstr_(" Weapon"), &ESP::PLAYER::m_bEnableEquippedWeaponEsp);
//			uic.Checkbox(xorstr_(" Eye Rays"), &ESP::PLAYER::m_bEnableEyeRays);
//			uic.Checkbox(xorstr_(" Names"), &ESP::PLAYER::m_bEnableNames);
//			uic.Checkbox(xorstr_(" Distance"), &ESP::PLAYER::m_bEnableDistanceEsp);
//			uic.Checkbox(xorstr_(" Crosshair"), &CROSSHAIR::m_bEnableCrosshair);
//			uic.Checkbox(xorstr_(" Foreground Check"), &Renderer::m_bForeGroundCheck);
//			uic.Checkbox(xorstr_(" Team Check"), &ESP::PLAYER::m_bTeamCheck);
//			uic.Checkbox(xorstr_(" Dormant Check"), &ESP::PLAYER::m_bDormantCheck);
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//
//	ImGui::SameLine();
//
//	if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((ImGui::GetContentRegionAvail().x), -20)))
//	{
//		if (uic.BeginFrame(2, ImVec2(0, (ImGui::GetContentRegionAvail().y)))) {
//			uic.CenterText(xorstr_("VISUALS CONFIGURATIONS"), avg_pads, ImColor(255, 255, 255, 255).Value);
//
//			uic.ColorEditor(xorstr_(" Box"), &ESP::PLAYER::m_clBoxUnfilledColor);
//			ImGui::SameLine();
//
//			uic.ColorEditor(xorstr_(" Box Fill"), &ESP::PLAYER::m_clBoxFilledColor);
//			ImGui::SameLine();
//
//			uic.ColorEditor(xorstr_(" Line"), &ESP::PLAYER::m_clLineColor);
//
//			uic.ColorEditor(xorstr_(" Line Point"), &ESP::PLAYER::m_clLinePointColor);
//			ImGui::SameLine();
//
//			uic.ColorEditor(xorstr_(" Name"), &ESP::PLAYER::m_clNameColor);
//			ImGui::SameLine();
//
//			uic.ColorEditor(xorstr_(" Name Stroke"), &ESP::PLAYER::m_clNameStrokeColor);
//
//			uic.ColorEditor(xorstr_(" Health Text"), &ESP::PLAYER::m_clHealthTextColor);
//			ImGui::SameLine();
//
//			uic.ColorEditor(xorstr_(" Health Text Stroke"), &ESP::PLAYER::m_clHealthTextStrokeColor);
//
//			uic.ColorEditor(xorstr_(" Armor"), &ESP::PLAYER::m_clArmorBarColor);
//			ImGui::SameLine();
//
//			uic.ColorEditor(xorstr_(" Distance"), &ESP::PLAYER::m_clDistanceTextColor);
//			uic.ColorEditor(xorstr_(" Distance Stroke"), &ESP::PLAYER::m_clDistanceTextStrokeColor);
//			uic.ColorEditor(xorstr_(" Bone"), &ESP::PLAYER::m_clBoneColor);
//			uic.ColorEditor(xorstr_(" Head Fill"), &ESP::PLAYER::m_clBoneHeadColor);
//			uic.ColorEditor(xorstr_(" Joints"), &ESP::PLAYER::m_clBoneJointsColor);
//			uic.ColorEditor(xorstr_(" Crosshair"), &CROSSHAIR::CrossHairColor);
//			uic.Slider(xorstr_(" Crosshair Size"), &CROSSHAIR::CrossHairSize, 0.0f, 40.0f, ImColor(255, 255, 255));
//			uic.Slider(xorstr_(" Box Thickness"), &ESP::PLAYER::m_flBoxUnfilledThickness, 0.0f, 3.0f, ImColor(255, 255, 255));
//			uic.Slider(xorstr_(" Box Radius"), &ESP::PLAYER::m_flBoxRounding, 0.0f, 6.0f, ImColor(255, 255, 255));
//			uic.Slider(xorstr_(" Line Thickness"), &ESP::PLAYER::m_flLinesThickness, 0.0f, 3.0f, ImColor(255, 255, 255));
//			uic.Slider(xorstr_(" Bone Thickness"), &ESP::PLAYER::m_flBonesThickness, 0.0f, 3.0f, ImColor(255, 255, 255));
//			uic.Slider(xorstr_(" Joint Radius"), &ESP::PLAYER::m_flJointRadius, 0.0f, 3.0f, ImColor(255, 255, 255));
//			uic.RadioButtonGroup(xorstr_(" Line Position"), &ESP::PLAYER::m_iCurrentLinePosIndex, ESP::PLAYER::m_AvailableSnapLinesPos, IM_ARRAYSIZE(ESP::PLAYER::m_AvailableSnapLinesPos));
//			uic.RadioButtonGroup(xorstr_(" Box Texture"), &ESP::PLAYER::m_iCurrentImageIndex, ESP::PLAYER::m_AvailableImages, IM_ARRAYSIZE(ESP::PLAYER::m_AvailableImages));
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//}
//
//void CreateAimUI() {
//	// AIMBOT FRAME
//	if (uic.BeginColumn(xorstr_("##left-column"), ImVec2((ImGui::GetContentRegionAvail().x / 2.0f), -20)))
//	{
//		if (uic.BeginFrame(1, ImVec2(0, (ImGui::GetContentRegionAvail().y)))) {
//			uic.CenterText(xorstr_("AIMBOT"), avg_pads, ImColor(255, 255, 255, 255).Value);
//			uic.LeaveLine();
//			uic.CenterText(xorstr_("It writes to memory so use it at your own risk!"), 0.0f, ImColor(255, 0, 0, 255).Value);
//			uic.Checkbox(xorstr_(" Enable"), &Aimbot::m_bEnableAimbot);
//			uic.Checkbox(xorstr_(" Visibility Check"), &Aimbot::m_bEnableVisibilityCheck);
//			uic.Checkbox(xorstr_(" Team Check"), &Aimbot::m_bEnableTeamCheck);
//			uic.Checkbox(xorstr_(" Fov Based"), &Aimbot::m_bFovBased);
//
//			if (Aimbot::m_bFovBased) {
//				uic.Slider<float>(xorstr_("Fov Range"), &Aimbot::m_flFOV, 1.0f, 1000.0f, ImColor(255, 255, 255, 255));
//				uic.Checkbox(xorstr_(" Show Circle"), &Aimbot::m_bShowFovCircle);
//
//				if (Aimbot::m_bShowFovCircle) {
//					uic.ColorEditor("Circle Color", &Aimbot::m_clFOVCircleColor);
//					uic.Slider<float>(xorstr_("Circle Thickness"), &Aimbot::m_flFOVCircleThickness, 0.0f, 10.0f, ImColor(255, 255, 255, 255));;
//				}
//			}
//
//			uic.ComboBox(xorstr_("Aim Position"), Aimbot::m_AimPositions[Aimbot::m_iCurrentAimPosIndex], &Aimbot::m_iCurrentAimPosIndex, Aimbot::m_AimPositions, IM_ARRAYSIZE(Aimbot::m_AimPositions));
//			uic.RadioButtonGroup(xorstr_(" Aimbot Mode"),
//				&Aimbot::m_iCurrentAimbotModeIndex,
//				Aimbot::m_AvailableAimbotModes,
//				IM_ARRAYSIZE(Aimbot::m_AvailableAimbotModes)
//			);
//			uic.LeaveLine();
//			uic.Hotkey(&Aimbot::m_iCurrentKEY);
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//
//	ImGui::SameLine();
//
//	// OTHER AIMS FEATURES
//	if (uic.BeginColumn(xorstr_("##right-column"), ImVec2((ImGui::GetContentRegionAvail().x), -20)))
//	{
//		// TRIGGERBOT
//		if (uic.BeginFrame(1, ImVec2(0, (ImGui::GetContentRegionAvail().y / 2.0f)))) {
//			uic.CenterText(xorstr_("TRIGGER BOT"), avg_pads, ImColor(255, 255, 255, 255).Value);
//			uic.Checkbox(xorstr_(" Enable"), &TRIGGER_BOT::m_bEnableTriggerBot);
//			uic.Checkbox(xorstr_(" Team Check"), &TRIGGER_BOT::m_bEnableTeamCheck);
//			uic.Slider(xorstr_(" Fire Delay (ms)"), &TRIGGER_BOT::m_flTriggerDelay, 0.0f, 120.0f, ImColor(255, 255, 255));
//			uic.Slider(xorstr_(" Fire Rate (ms)"), &TRIGGER_BOT::m_flTriggerFireRate, 0.0f, 120.0f, ImColor(255, 255, 255));
//			uic.RadioButtonGroup(xorstr_(" Fire Mode"),
//				&TRIGGER_BOT::m_iCurrentTriggerModeIndex,
//				TRIGGER_BOT::m_AvailableFireModes,
//				IM_ARRAYSIZE(TRIGGER_BOT::m_AvailableFireModes)
//			);
//			uic.LeaveLine();
//			uic.Hotkey(&TRIGGER_BOT::m_iCurrentTriggerKey);
//		}
//
//		uic.EndFrame();
//
//		// SRCS
//		if (uic.BeginFrame(2, ImVec2(0, 0))) {
//			uic.CenterText(xorstr_("STANDALONE RCS"), avg_pads, ImColor(255, 255, 255, 255).Value);
//			uic.Checkbox(xorstr_(" Enable"), &SRCS::m_bEnableSRCS);
//			uic.Slider(xorstr_(" PITCH"), &SRCS::m_flPITCH, 1.8f, 2.4f, ImColor(255, 255, 255));
//			uic.Slider(xorstr_(" YAW"), &SRCS::m_flYAW, 1.6f, 2.2f, ImColor(255, 255, 255));
//			uic.RadioButtonGroup(xorstr_(" Mode"),
//				&SRCS::m_iCurrentSRCSModeIndex,
//				SRCS::m_AvailableModes,
//				IM_ARRAYSIZE(SRCS::m_AvailableModes)
//			);
//			uic.LeaveLine();
//			uic.Hotkey(&SRCS::m_iCurrentSRCSKey);
//			ImGui::Text(xorstr_(" Note: This is not perfect - \n different weapons have different recoil patterns."));
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//}
//
//void CreateMiscUI() {
//	// top-left & bottom-left
//	if (uic.BeginColumn(xorstr_("##left-column"), ImVec2((ImGui::GetContentRegionAvail().x / 2.0f), -20)))
//	{
//		if (uic.BeginFrame(1, ImVec2(0, (ImGui::GetContentRegionAvail().y / 2.0f)))) {
//			uic.CenterText(xorstr_("WEAPON FEATURES"), avg_pads, ImColor(255, 255, 255, 255).Value);
//			uic.Checkbox(xorstr_(" Esp"), &ESP::PLAYER::m_bEnableEquippedWeaponEsp);
//			uic.Checkbox(xorstr_(" Hitsound"), &HITSERVICE::m_bEnableHitsound);
//			uic.ColorEditor(xorstr_(" Color"), &ESP::PLAYER::m_clEquippedWeaponIconColor);
//			uic.ColorEditor(xorstr_(" Stroke Color"), &ESP::PLAYER::m_clEquippedWeaponIconStrokeColor);
//			uic.LeaveLine();
//			HITSERVICE::ScanDirectoryForFile(xorstr_(".wav"));
//
//			if (!HITSERVICE::wav_files.empty()) {
//				static int m_iSelectedHitSoundIndex = 0;
//				std::vector<const char*> wav_files_cstr;
//
//				for (const auto& file : HITSERVICE::wav_files) {
//					wav_files_cstr.push_back(file.c_str());
//				}
//
//				// Show ComboBox
//				uic.ComboBox(xorstr_("Select Hitsound (Must be .wav file or audio file,\nthat is supported by WinAPI)"),
//					HITSERVICE::wav_files[m_iSelectedHitSoundIndex].c_str(),
//					&m_iSelectedHitSoundIndex,
//					wav_files_cstr.data(),
//					wav_files_cstr.size(),
//					0.0f
//				);
//				HITSERVICE::file_name = HITSERVICE::wav_files[m_iSelectedHitSoundIndex];
//			}
//		}
//
//		uic.EndFrame();
//
//		if (uic.BeginFrame(2, ImVec2(0, 0))) {
//			uic.CenterText(xorstr_("MEMORY FEATURES"), avg_pads, ImColor(255, 255, 255, 255).Value);
//			ImGui::TextColored(ImColor(255, 0, 0), xorstr_("Memory features are highly risky and can get you\na sure ban!"));
//			uic.LeaveLine();
//			uic.Checkbox(xorstr_(" Flash Override"), &MEMORY::m_bEnableFlashAlphaOverride);
//			uic.Slider(xorstr_(" Flash Alpha"), &MEMORY::m_flFlashAlpha, 0.0f, 255.0f, ImColor(255, 255, 255));
//			uic.Checkbox(xorstr_(" Fake Bhop"), &MEMORY::m_bEnableFakeBhop);
//			uic.Hotkey(&MEMORY::m_iBhopKEY);
//			uic.Checkbox(xorstr_(" Fov Override"), &MEMORY::m_bEnableCameraFovOverride);
//			uic.Slider<int>(xorstr_(" Fov Range"), &MEMORY::m_iDefaultFOV, 1, 150, ImColor(255, 255, 255));
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//
//	ImGui::SameLine();
//
//	// top-right & bottom-right
//	if (uic.BeginColumn(xorstr_("##right-column"), ImVec2(0, -20)))
//	{
//		if (uic.BeginFrame(3, ImVec2(0, (ImGui::GetContentRegionAvail().y / 2.0f)))) {
//			uic.CenterText("More Features Coming Soon!", 0.0f, ImColor(0, 255, 0));
//		}
//
//		uic.EndFrame();
//
//		if (uic.BeginFrame(4, ImVec2(0, 0))) {
//			uic.CenterText("More Features Coming Soon!", 0.0f, ImColor(0, 255, 0));
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//}
//
//void CreateServerUI() {
//	//top-left & bottom-left
//	if (uic.BeginColumn(xorstr_("##left-column"), ImVec2((ImGui::GetContentRegionAvail().x / 2.0f), -20)))
//	{
//		// top-left-box
//		if (uic.BeginFrame(1, ImVec2(0, (ImGui::GetContentRegionAvail().y / 2.0f)))) {
//			uic.Checkbox("Player List", &this->show_player_list);
//		}
//
//		uic.EndFrame();
//
//		// bottom-left-box
//		if (uic.BeginFrame(2, ImVec2(0, 0))) {
//			uic.CenterText("More Features Coming Soon!", 0.0f, ImColor(0, 255, 0));
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//
//	ImGui::SameLine();
//
//	//top-right & bottom-right
//	if (uic.BeginColumn(xorstr_("##right-column"), ImVec2(0, -20)))
//	{
//		// top-right-box
//		if (uic.BeginFrame(3, ImVec2(0, (ImGui::GetContentRegionAvail().y / 2.0f)))) {
//			uic.CenterText("More Features Coming Soon!", 0.0f, ImColor(0, 255, 0));
//		}
//
//		uic.EndFrame();
//
//		// bottom-right-box
//		if (uic.BeginFrame(4, ImVec2(0, 0))) {
//			uic.CenterText("More Features Coming Soon!", 0.0f, ImColor(0, 255, 0));
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//}
//
//void CreateSettingsUI() {
//	//top-left & bottom-left
//	if (uic.BeginColumn(xorstr_("##left-column"), ImVec2((ImGui::GetContentRegionAvail().x / 2.0f), -20)))
//	{
//		// top-left-box
//		if (uic.BeginFrame(1, ImVec2(0, (ImGui::GetContentRegionAvail().y / 2.0f)))) {
//			uic.CenterText(xorstr_(" OFFSETS UPDATE/DOWNLOAD"), avg_pads, ImColor(255, 255, 255));
//			uic.LeaveLine();
//
//			if (ImGui::Button(xorstr_("Download Latest Offsets"), ImVec2(250, 40))) {
//				Instance<Updater>::Get().DownloadOffsets();
//			}
//
//			uic.LeaveLine();
//
//			if (ImGui::Button(xorstr_("Reload"), ImVec2(250, 40))) {
//				Instance<Updater>::Get().UpdateOffsets();
//			}
//
//			ImGui::Text(xorstr_("If you're unable to download/update offsets using the\nbutton above,try downloading them manually-\nfrom the provided links and put them into-\nthe offsets folder!"));
//
//			ImGui::TextLinkOpenURL(xorstr_("Offsets.json"), "https://raw.githubusercontent.com/a2x/cs2-dumper/refs/heads/main/output/offsets.json");
//			ImGui::TextLinkOpenURL(xorstr_("ClientDll.json"), "https://raw.githubusercontent.com/a2x/cs2-dumper/refs/heads/main/output/client_dll.json");
//			ImGui::TextLinkOpenURL(xorstr_("Buttons.json"), "https://raw.githubusercontent.com/a2x/cs2-dumper/refs/heads/main/output/buttons.json");
//		}
//
//		uic.EndFrame();
//
//		// bottom-left-box
//		if (uic.BeginFrame(2, ImVec2(0, 0))) {
//			uic.CenterText(xorstr_(" CONFIG MANAGER"), avg_pads, ImColor(255, 255, 255));
//			uic.LeaveLine();
//
//			ConfigManager& configs = Instance<ConfigManager>::Get();
//
//			configs.ScanDirectoryForFile(CONFIG_FILE_EXTENSION);
//
//			static char buffer[MAX_BUFFER_SIZE * 2] = "Config Name";
//
//			ImGui::SetNextItemWidth(150.0f);
//			uic.InputBoxWithPlaceholder(xorstr_("##config_name"), "Config Name", buffer, sizeof(buffer));
//
//			if (ImGui::Button(xorstr_("Save Config"), ImVec2(150, 35))) {
//				configs.file_name = buffer;
//				configs.CreateConfig();
//			}
//
//			uic.LeaveLine();
//
//			if (ImGui::Button(xorstr_("Load Config"), ImVec2(150, 35))) {
//				configs.LoadConfig();
//			}
//
//			uic.LeaveLine();
//
//			if (!configs.ConfigFiles.empty()) {
//				static int SELECTED_CONFIG_INI_FILE_INDEX = 0;
//				std::vector<const char*> config_files_cstr;
//
//				for (unsigned int i = 0; i < configs.ConfigFiles.size(); ++i) {
//					config_files_cstr.push_back(configs.ConfigFiles[i].c_str());
//				}
//
//				std::string SELECTED_FILE_NAME = config_files_cstr[SELECTED_CONFIG_INI_FILE_INDEX];
//				uic.ComboBox(xorstr_(" Select Configuration"), SELECTED_FILE_NAME.c_str(), &SELECTED_CONFIG_INI_FILE_INDEX, config_files_cstr.data(), config_files_cstr.size(), 0.0f);
//				configs.file_name = config_files_cstr[SELECTED_CONFIG_INI_FILE_INDEX];
//			}
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//
//	ImGui::SameLine();
//
//	//top-right & bottom-right
//	if (uic.BeginColumn(xorstr_("##right-column"), ImVec2(0, -20)))
//	{
//		// top-right-box
//		if (uic.BeginFrame(3, ImVec2(0, (ImGui::GetContentRegionAvail().y / 2.0f)))) {
//			uic.CenterText(xorstr_(" SETTINGS"), avg_pads, ImColor(255, 255, 255));
//			uic.LeaveLine();
//
//			uic.Checkbox(xorstr_("Automatic Update"), &_FLAGS_::m_bAutomaticUpdate);
//			uic.Checkbox(xorstr_("Animate UI"), &_FLAGS_::m_bAnimateUI);
//			uic.Checkbox(xorstr_("Show Overlay Texts"), &_FLAGS_::m_bShowText);
//			uic.Slider<float>(xorstr_(" Animation Speed"), &_FLAGS_::m_flAnimationSpeed, 0.5, 10.0f, ImColor(255, 255, 255));
//
//			if (ImGui::Button(xorstr_("Save Settings"), ImVec2(150, 35)))
//			{
//				settings.SaveSettings();
//			}
//		}
//
//		uic.EndFrame();
//
//		// bottom-right-box
//		if (uic.BeginFrame(4, ImVec2(0, 0))) {
//			uic.CenterText(xorstr_(" HOTKEYS"), avg_pads, ImColor(255, 255, 255));
//			uic.LeaveLine();
//
//			uic.Hotkey(&_FLAGS_::m_iEndProgramKey);
//			ImGui::SameLine();
//			ImGui::Text("Panic Key (Exits)");
//
//			uic.Hotkey(&_FLAGS_::m_iVisibilityToggleKey);
//			ImGui::SameLine();
//			ImGui::Text("Visibility Toggle Key");
//
//			uic.Hotkey(&_FLAGS_::m_iLoadUnloadCheatsKey);
//			ImGui::SameLine();
//			ImGui::Text("Load/Unload Cheats Key");
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//}
//
//void CreatePlayerListUI(std::vector<CEntity>& list) {
//	uic.SetStyles();
//	ImGui::SetNextWindowSize(ImVec2(300, 500));
//	ImGui::Begin(xorstr_("Player List Window"), &this->show_player_list, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
//
//	ImGui::PushFont(RES_LOADER::FONTS::PANAROMA_UI_FONT);
//
//	if (uic.BeginColumn(xorstr_("##left-column"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y))) {
//		uic.CenterText(xorstr_("PLAYER/ENTITY LIST"), 0.0f, ImColor(255, 255, 255));
//
//		if (uic.BeginFrame(1, ImVec2(0, (ImGui::GetContentRegionAvail().y)))) {
//			for (auto& entity : list) {
//				ImGui::TextColored((entity.Team == T_TERRORIST ? T_COLOR : CT_COLOR), entity.Name);
//				ImGui::SameLine();
//				ImGui::TextColored((entity.Team == T_TERRORIST ? T_COLOR : CT_COLOR), std::to_string(entity.Health).c_str());
//			}
//		}
//
//		uic.EndFrame();
//	}
//
//	uic.EndColumn();
//
//	ImGui::PopFont();
//
//	ImGui::End();
//}