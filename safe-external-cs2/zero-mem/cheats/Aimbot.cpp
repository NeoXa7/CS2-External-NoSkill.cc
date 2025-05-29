#include <pch.h>
#include "Aimbot.h"
#include <utils/process.h>

namespace AIMBOT {
	Vector2 FindClosest(std::vector<CEntity>& list) {
		Vector2 ClosestEntity = { 0, 0 };
		Vector2 COS(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		float lowest_distance = 10000.0f;

		for (auto& entity : list) {
			if (entity.Team == LocalPlayer.Team && AIMBOT::m_bEnableTeamCheck)
				continue;

			if (entity.Health <= 0)
				continue;

			Instance<CWeapon>::Get().ClippingWeapon = LocalPlayer.pClippingWeapon;
			Instance<CWeapon>::Get().EntityID = LocalPlayer.ID;
			Instance<CWeapon>::Get().Update();

			if (Instance<CWeapon>::Get().GetEquippedWeapon() == "awp" || Instance<CWeapon>::Get().GetEquippedWeapon() == "ssg08") {
				if (AIMBOT::m_bEnableSniperScopeCheck && !LocalPlayer.IsScoped)
					continue;
			}

			if (Instance<CWeapon>::Get().GetEquippedWeapon() == "scar20" || 
				Instance<CWeapon>::Get().GetEquippedWeapon() == "g3sg1" || 
				Instance<CWeapon>::Get().GetEquippedWeapon() == "aug" ||
				Instance<CWeapon>::Get().GetEquippedWeapon() == "sg553") 
			{
				if (AIMBOT::m_bEnableSniperRifleScopeCheck && !LocalPlayer.IsScoped)
					continue;
			}

			Vector3 EntityLocation;

			switch (m_iCurrentAimPosIndex) {
			case 0: EntityLocation = entity.GetBone3D(HEAD); break;
			case 1: EntityLocation = entity.GetBone3D(COCK); break;
			case 2: EntityLocation = entity.GetBone3D(NECK); break;
			case 3: EntityLocation = entity.GetBone3D(CHEST); break;
			case 4: EntityLocation = entity.GetBone3D(STOMACH); break;
			case 5: EntityLocation = entity.GetBone3D(LSHOULDER); break;
			case 6: EntityLocation = entity.GetBone3D(LARM); break;
			case 7: EntityLocation = entity.GetBone3D(LHAND); break;
			case 8: EntityLocation = entity.GetBone3D(RSHOULDER); break;
			case 9: EntityLocation = entity.GetBone3D(RARM); break;
			case 10: EntityLocation = entity.GetBone3D(RHAND); break;
			case 11: EntityLocation = entity.GetBone3D(LTHIGH); break;
			case 12: EntityLocation = entity.GetBone3D(LCALF); break;
			case 13: EntityLocation = entity.GetBone3D(LFOOT); break;
			case 14: EntityLocation = entity.GetBone3D(RTHIGH); break;
			case 15: EntityLocation = entity.GetBone3D(RCALF); break;
			case 16: EntityLocation = entity.GetBone3D(RFOOT); break;
			default: EntityLocation = entity.GetBone3D(HEAD); break;
			}

			Vector2 AimPosition2D = EntityLocation.WorldToScreen(Game.ViewMatrix).ToVector2();
			float PixelDistance = entity.HeadPosition2D.Distance(Vector2(SCREEN_CENTER_X, SCREEN_CENTER_Y));
			float distance = sqrt(pow(AimPosition2D.x - COS.x, 2) + pow(AimPosition2D.y - COS.y, 2));

			if (AIMBOT::m_bFovBased) {
				if (PixelDistance < AIMBOT::m_flFOV) {
					if (!AimPosition2D.IsZero()) {
						if (distance < lowest_distance)
						{
							lowest_distance = distance;
							ClosestEntity = AimPosition2D;
						}
					}
				}
			}
			else {
				if (!AimPosition2D.IsZero()) {
					if (distance < lowest_distance)
					{
						lowest_distance = distance;
						ClosestEntity = AimPosition2D;
					}
				}
			}
		}

		return ClosestEntity;
	}

	void Move(Vector2 target) {
		if (target.x == 0.0f && target.y == 0.0f)
			return;

		Vector2 screenCenter((float)GetSystemMetrics(SM_CXSCREEN) / 2.0f,
			(float)GetSystemMetrics(SM_CYSCREEN) / 2.0f);

		Vector2 delta = (target - screenCenter) / AIMBOT::m_flSmoothness;

		INPUT input = { 0 };
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		input.mi.dx = static_cast<LONG>(delta.x);
		input.mi.dy = static_cast<LONG>(delta.y);

		SendInput(1, &input, sizeof(INPUT));
	}


	void RUN(std::vector<CEntity>& list) {
		if (!AIMBOT::m_bEnableAimbot)
			return;

		if (!Instance<Process>::Get().InForeground("Counter-Strike 2"))
			return;

		if (AIMBOT::m_bShowFovCircle && AIMBOT::m_bFovBased) {
			Utils::Draw::Circle(SCREEN_CENTER_X, SCREEN_CENTER_Y, AIMBOT::m_flFOV, m_flFOVCircleThickness, 0, AIMBOT::m_clFOVCircleColor);
		}

		AIMBOT::m_imAimbotMode = (AIMBOT::m_iCurrentAimbotModeIndex == 0) ? AUTO : HOLD;

		if (AIMBOT::m_imAimbotMode == HOLD) {
			if (GetAsyncKeyState(AIMBOT::m_iCurrentKEY)) {
				AIMBOT::Move(AIMBOT::FindClosest(list));
			}
		}
		else if (AIMBOT::m_imAimbotMode == AUTO) {
			AIMBOT::Move(AIMBOT::FindClosest(list));
		}
	}
}

// Below is an aimbot that writes to memory (view angles, not safe + laggy on official servers as it will write to memory 64 times per second)

//
//namespace Aimbot {
//	void RUN(CEntity& entity) {
//		if (Aimbot::m_bEnableAimbot) {
//			if (Aimbot::m_bShowFovCircle && Aimbot::m_bFovBased) {
//				Utils::Draw::Circle(SCREEN_CENTER_X, SCREEN_CENTER_Y, Aimbot::m_flFOV, m_flFOVCircleThickness, 0, Aimbot::m_clFOVCircleColor);
//			}
//
//			if (entity.Team == LocalPlayer.Team && m_bEnableTeamCheck)
//				return;
//
//			if (!entity.IsVisible && Aimbot::m_bEnableVisibilityCheck)
//				return;
//
//			if (Aimbot::m_iCurrentAimbotModeIndex == 0) {
//				Aimbot::m_imAimbotMode = AUTO;
//			}
//			else if (Aimbot::m_iCurrentAimbotModeIndex == 1) {
//				Aimbot::m_imAimbotMode = HOLD;
//			}
//
//			Vector3 EntityLocation;
//			Vector3 LocalLocation = LocalPlayer.GetBone3D(HEAD);
//
//			switch (m_iCurrentAimPosIndex) {
//			case 0: EntityLocation = entity.GetBone3D(HEAD); break;
//			case 1: EntityLocation = entity.GetBone3D(COCK); break;
//			case 2: EntityLocation = entity.GetBone3D(NECK); break;
//			case 3: EntityLocation = entity.GetBone3D(CHEST); break;
//			case 4: EntityLocation = entity.GetBone3D(STOMACH); break;
//			case 5: EntityLocation = entity.GetBone3D(LSHOULDER); break;
//			case 6: EntityLocation = entity.GetBone3D(LARM); break;
//			case 7: EntityLocation = entity.GetBone3D(LHAND); break;
//			case 8: EntityLocation = entity.GetBone3D(RSHOULDER); break;
//			case 9: EntityLocation = entity.GetBone3D(RARM); break;
//			case 10: EntityLocation = entity.GetBone3D(RHAND); break;
//			case 11: EntityLocation = entity.GetBone3D(LTHIGH); break;
//			case 12: EntityLocation = entity.GetBone3D(LCALF); break;
//			case 13: EntityLocation = entity.GetBone3D(LFOOT); break;
//			case 14: EntityLocation = entity.GetBone3D(RTHIGH); break;
//			case 15: EntityLocation = entity.GetBone3D(RCALF); break;
//			case 16: EntityLocation = entity.GetBone3D(RFOOT); break;
//			default: EntityLocation = entity.GetBone3D(HEAD); break;
//			}
//
//			float PixelDistance = entity.HeadPosition2D.Distance(Vector2(SCREEN_CENTER_X, SCREEN_CENTER_Y));
//			Vector2 Angles = Maths::CalculateAngles(LocalLocation, EntityLocation);
//			Vector3 CurrentAngles = LocalPlayer.GetCurrentViewAngles();
//			Vector3 SmoothAngles = Maths::SmoothAngle(CurrentAngles, Vector3(Angles.y, Angles.x, 0.0f), 1.f);
//
//
//			if (!SmoothAngles.IsZero()) {
//				if (Aimbot::m_bFovBased) {
//					if (PixelDistance < Aimbot::m_flFOV) {
//						if (Aimbot::m_imAimbotMode == HOLD && (GetAsyncKeyState(Aimbot::m_iCurrentKEY) & 0x8000)) {
//							LocalPlayer.SetViewAngles(SmoothAngles);
//						}
//						else if (Aimbot::m_imAimbotMode == AUTO) {
//							LocalPlayer.SetViewAngles(SmoothAngles);
//						}
//					}
//				}
//				else {
//					if (Aimbot::m_imAimbotMode == HOLD && (GetAsyncKeyState(Aimbot::m_iCurrentKEY) & 0x8000)) {
//						LocalPlayer.SetViewAngles(SmoothAngles);
//					}
//					else if (Aimbot::m_imAimbotMode == AUTO) {
//						LocalPlayer.SetViewAngles(SmoothAngles);
//					}
//				}
//			}	
//		}
//	}
//}