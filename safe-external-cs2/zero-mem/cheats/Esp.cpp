#include "esp.h"

void ESP::PLAYER::RUN(CEntity& entities) {
	if (entities.IsDormant && PLAYER::m_bDormantCheck)
		return;

	if (entities.Team == LocalPlayer.Team && PLAYER::m_bTeamCheck)
		return;

	float box_height = std::fabs(entities.HeadPosition2D.y - entities.Position2D.y);
	float box_width = box_height * 0.6f;

	Vector2 BoxPos(entities.Position2D.x - box_width / 2, entities.HeadPosition2D.y);
	Vector2 BoxSize(std::fabs(entities.HeadPosition2D.y - entities.Position2D.y) * 0.6f, entities.Position2D.y - entities.HeadPosition2D.y);

	// Predefined Distance Text Positions
	Vector2 BoxTopRight(BoxPos.x + BoxSize.x + 5.0f, BoxPos.y);
	Vector2 BoxTopLeft(BoxPos.x - 40.0f, BoxPos.y);
	Vector2 BoxBottomRight(BoxPos.x + BoxSize.x + 5.0f, BoxPos.y + BoxSize.y);
	Vector2 BoxBottomLeft(BoxPos.x - 40.0f, BoxPos.y + BoxSize.y);
	Vector2 AboveBox(BoxPos.x + BoxSize.x / 2 - 20.0f, BoxPos.y - 20.0f);
	Vector2 InsideBoxCenter(BoxPos.x + BoxSize.x / 2 - 20.0f, BoxPos.y + BoxSize.y / 2 - 5.0f);
	Vector2 BelowBox(BoxPos.x + BoxSize.x / 2 - 20.0f, BoxPos.y + BoxSize.y + 10.0f);

	// Player Esp
	if (!entities.Position2D.IsZero() && !entities.HeadPosition2D.IsZero() && PLAYER::m_bEnablePlayerEsp) {
		// Box Esp
		if (PLAYER::m_bEnableBox) {
			if (entities.Position2D.x > 0 && entities.Position2D.y > 0) { // Ensure it's visible
				if (!PLAYER::m_bEnableBoxFilled) {
					Utils::Draw::Rectangle(BoxPos, BoxSize, PLAYER::m_flBoxUnfilledThickness, PLAYER::m_flBoxRounding, PLAYER::m_clBoxUnfilledColor);
					//mem.DrawBox(BoxPos.x, BoxPos.y, (int)box_width, (int)box_height, 2.0f, 0, 0, 0);
				}
				else {
					Utils::Draw::FilledRectangle(BoxPos, BoxSize, PLAYER::m_flBoxUnfilledThickness, PLAYER::m_flBoxRounding, PLAYER::m_clBoxFilledColor, PLAYER::m_clBoxUnfilledColor);
				}
			}
		}

		if (PLAYER::m_bEnableBoxImage) {
			ImTextureID texture = 0;
			if (PLAYER::m_iCurrentImageIndex == 0) {
				texture = (ImTextureID)RES_LOADER::IMAGES::FISH_STICK;
			}
			else if (PLAYER::m_iCurrentImageIndex == 1) {
				texture = (ImTextureID)RES_LOADER::IMAGES::ANIME_GIRL_1;
			}
			else if (PLAYER::m_iCurrentImageIndex == 2) {
				texture = (ImTextureID)RES_LOADER::IMAGES::ANIME_GIRL_2;
			}
			else if (PLAYER::m_iCurrentImageIndex == 3) {
				texture = (ImTextureID)RES_LOADER::IMAGES::ANIME_GIRL_3;
			}

			Utils::Draw::ImageRectangle(texture, BoxPos, BoxSize);
		}

		// Line Esp
		if (PLAYER::m_bEnableSnapLines) {

			switch (PLAYER::m_iCurrentLinePosIndex) {
			case 0: PLAYER::m_vecCurrentlinePos = { SCREEN_TOP_X , SCREEN_TOP_Y }; break;
			case 1: PLAYER::m_vecCurrentlinePos = { SCREEN_CENTER_X , SCREEN_CENTER_Y }; break;
			case 2: PLAYER::m_vecCurrentlinePos = { SCREEN_BOTTOM_X , SCREEN_BOTTOM_Y }; break;
			default: PLAYER::m_vecCurrentlinePos = { SCREEN_BOTTOM_X , SCREEN_BOTTOM_Y }; break;
			}

			Utils::Draw::LineWithPoint(PLAYER::m_vecCurrentlinePos, entities.Position2D, PLAYER::m_flLinesThickness, 3.0f, PLAYER::m_clLineColor, PLAYER::m_clLinePointColor);

		}

		// Bone Esp
		if (PLAYER::m_bEnableBones) {
			Utils::Draw::CSGO::Bones(
				entities,
				PLAYER::m_flBonesThickness,
				PLAYER::m_bEnableHead,
				PLAYER::m_bEnableHeadFilled,
				PLAYER::m_bEnableBonesJoints,
				PLAYER::m_flJointRadius,
				PLAYER::m_clBoneColor,
				PLAYER::m_clBoneHeadColor,
				PLAYER::m_clBoneJointsColor
			);
		}

		// Eye Rays Esp
		if (PLAYER::m_bEnableEyeRays) {
			Utils::Draw::CSGO::EyeRay(entities, 20);
		}

		// Health Bar
		if (PLAYER::m_bEnableHealthBar) {
			PLAYER::m_clHealthBarColor = entities.GetHealthColor();
			Utils::Draw::VerticalBar(BoxPos, BoxPos + BoxSize, entities.Health, 4.0f, 2.0f, PLAYER::m_clHealthBarColor);
		}

		// Health Text
		if (PLAYER::m_bEnableHealthText) {
			char Buffer[MAX_BUFFER_SIZE];
			snprintf(Buffer, sizeof(Buffer), "[%d]", entities.Health);

			ImGui::PushFont(RES_LOADER::FONTS::PANAROMA_UI_FONT);
			Utils::Draw::TextWithStroke(Buffer, BoxTopLeft, PLAYER::m_flHealthTextStrokeThickness, PLAYER::m_clHealthTextColor, PLAYER::m_clHealthTextStrokeColor);
			ImGui::PopFont();
		}

		// Armor Bar
		if (PLAYER::m_bEnableArmorBar) {
			Utils::Draw::HorizontalBar(BoxPos, BoxPos + BoxSize, false, entities.Armor, 4.0f, 2.0f, PLAYER::m_clArmorBarColor);
		}

		// Name Esp
		if (PLAYER::m_bEnableNames) {
			ImGui::PushFont(RES_LOADER::FONTS::PANAROMA_UI_FONT);
			Utils::Draw::TextWithStroke(entities.Name, AboveBox, PLAYER::m_flNameTextStrokeThickness, PLAYER::m_clNameColor, PLAYER::m_clNameStrokeColor);
			ImGui::PopFont();
		}

		// Distance Esp 
		if (PLAYER::m_bEnableDistanceEsp) {
			char Buffer[MAX_BUFFER_SIZE];
			float EntitiesDistanceInMeters = ((entities.Position3D - LocalPlayer.Position3D).Length()) / GAME_METRIC_UNITS - 0.3;

			snprintf(Buffer, sizeof(Buffer), "[%.1f m]", EntitiesDistanceInMeters);

			ImGui::PushFont(RES_LOADER::FONTS::PANAROMA_UI_FONT);
			Utils::Draw::TextWithStroke(Buffer, BoxTopRight, PLAYER::m_flDistanceTextStrokeThickness, PLAYER::m_clDistanceTextColor);
			ImGui::PopFont();
		}

		// Weapon Esp (Equipped)
		if (PLAYER::m_bEnableEquippedWeaponEsp) {
			ImGui::PushFont(RES_LOADER::FONTS::PANAROMA_WEAPONS_ICON_FONT);
			Instance<CWeapon>::Get().Update(entities);
			std::string player_current_weapon = Instance<CWeapon>::Get().GetEquippedWeapon(entities.ID);
			Utils::Draw::TextWithStroke(Instance<CWeapon>::Get().GetWeaponIcon(player_current_weapon), BelowBox, PLAYER::m_flWeaponIconStrokeThickness, PLAYER::m_clEquippedWeaponIconColor, PLAYER::m_clEquippedWeaponIconStrokeColor);
			ImGui::PopFont();
		}
	}
}