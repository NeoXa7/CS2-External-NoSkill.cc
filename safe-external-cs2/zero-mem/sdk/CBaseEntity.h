#pragma once
#include <globals/imports.h>
#include <sdk/maths/vector.h>
#include <sdk/maths/maths.h>
#include <sdk/CBone.h>
#include <sdk/CGame.h>

class CBaseEntity
{
public:
	uintptr_t C_CSPlayerPawn = 0;
	uintptr_t C_CSPlayerController = 0;
	uintptr_t pDesignerName = 0;
	uintptr_t pNode = 0;
	uintptr_t pBoneMatrix = 0;
	uintptr_t pClippingWeapon = 0;
	uintptr_t pNameAddress = 0;
	uintptr_t pBulletService = 0;
	uintptr_t pCameraService = 0;
	Vector3 pViewAngles;

	uint32_t ShotsFired = 0;

	char Name[MAX_BUFFER_SIZE] = { 0 };
	int Index = 0;
	int ID = 0;
	int Health = 0;
	int Armor = 0;
	int Team = 0;
	int Flags = 0;
	int Ping = 0;
	int IDEntIndex = 0;
	int TotalHits = 0;

	bool IsScoped = false;
	bool IsDormant = false;
	bool IsVisible = false;

	Vector3 Position3D;
	Vector3 EyeAngles3D;
	Vector3 EyePosition3D;
	Vector3 HeadPosition3D;
	Vector3 Velocity;

	Vector2 Position2D;
	Vector2 EyeAngles2D;
	Vector2 HeadPosition2D;
	Vector2 EyePosition2D;

	C_UTL_VECTOR AimPunchCache;

	float AimPunchAngle;
	float MouseSensitivity;

public:
	Vector3 GetBone3D(BoneIndex type);
	Vector2 GetBone2D(BoneIndex type);
	bool IsDead();
	bool IsSameTeam(int& other_team);
	ImColor GetHealthColor();
	Vector3 GetCurrentViewAngles();
	void SetViewAngles(Vector3& angles);
};
