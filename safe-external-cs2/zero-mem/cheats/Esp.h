#pragma once
#include <sdk/sdk.h>
#include <sdk/defs.h>
#include <utils/functions.h>
#include <utils/draw.h>
#include <utils/resource_loader.h>
#include <globals/imports.h>
#include <globals/utils.h>
#include <globals/_flags.h>

namespace ESP
{
	namespace PLAYER
	{
		inline bool m_bEnablePlayerEsp = true;

		inline bool m_bEnableBox = true;
		inline bool m_bEnableBoxFilled = true;
		inline bool m_bEnableBoxImage= false;
		inline bool m_bEnableSnapLines = false;
		inline bool m_bEnableHealthBar = true;
		inline bool m_bEnableHealthText = true;
		inline bool m_bEnableArmorBar = true;
		inline bool m_bEnableBones = true;
		inline bool m_bEnableBonesJoints = true;
		inline bool m_bEnableHead = false;
		inline bool m_bEnableHeadFilled = false;
		inline bool m_bEnableEyeRays = false;
		inline bool m_bEnableNames = true;
		inline bool m_bEnableDistanceEsp = false;
		inline bool m_bEnableEquippedWeaponEsp = true;

		inline bool m_bTeamCheck = true;
		inline bool m_bDormantCheck = true;

		inline float m_flBoxRounding = 0.0f;
		inline float m_flBoxUnfilledThickness = 2.0f;
		inline float m_flLinesThickness = 2.0f;
		inline float m_flBonesThickness = 2.0f;
		inline float m_flJointRadius = 2.0f;
		inline float m_flNameTextStrokeThickness = 1.0f;
		inline float m_flHealthTextStrokeThickness = 1.0f;
		inline float m_flDistanceTextStrokeThickness = 1.0f;
		inline float m_flWeaponIconStrokeThickness = 1.0f;

		inline ImColor m_clBoxFilledColor = ImColor(0, 0, 0, 58);
		inline ImColor m_clBoxUnfilledColor = ImColor(255, 255, 255);
		inline ImColor m_clLineColor = ImColor(255, 255, 255);
		inline ImColor m_clLinePointColor = ImColor(0, 0, 0);
		inline ImColor m_clNameColor = ImColor(255, 255, 255);
		inline ImColor m_clNameStrokeColor = ImColor(0, 0, 0);
		inline ImColor m_clArmorBarColor = ImColor(182, 212, 238);
		inline ImColor m_clDistanceTextColor = ImColor(250, 250, 250);
		inline ImColor m_clDistanceTextStrokeColor = ImColor(0, 0, 0);
		inline ImColor m_clHealthBarColor = ImColor(0, 255, 0);
		inline ImColor m_clHealthTextColor = ImColor(250, 250, 250);
		inline ImColor m_clHealthTextStrokeColor = ImColor(0, 0, 0);
		inline ImColor m_clBoneColor = ImColor(0, 210, 0);
		inline ImColor m_clBoneHeadColor = ImColor(255, 0, 0, 17);
		inline ImColor m_clBoneJointsColor = ImColor(255, 255, 247);
		inline ImColor m_clEquippedWeaponIconColor = ImColor(250, 250, 250);
		inline ImColor m_clEquippedWeaponIconStrokeColor = ImColor(0, 0, 0);

		inline int m_iCurrentLinePosIndex = 2;
		inline const char* m_AvailableSnapLinesPos[] = { "Top", "Center", "Bottom" };
		inline Vector2 m_vecCurrentlinePos;

		inline int m_iCurrentImageIndex = 1;
		inline const char* m_AvailableImages[] = { "Fish-Stick", "Anime-1", "Anime-2"};

		void RUN(CEntity& entities);
	}
}