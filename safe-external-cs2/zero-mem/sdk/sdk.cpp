#include <pch.h>
#include "sdk.h"
#include <utils/process.h>
#include <globals/defs.h>
#include <globals/offsets.h>
#include <cheats/Memory.h>

// main function to get the base entity class
void CSourceEngine::GetCBaseEntity(CBaseEntity& cBaseEntity) {
	cBaseEntity.pNode = mem.Read<uintptr_t>(cBaseEntity.C_CSPlayerPawn + Offsets::m_pGameSceneNode);
	cBaseEntity.pBoneMatrix = mem.Read<uintptr_t>(cBaseEntity.pNode + Offsets::m_groundNormal);
	cBaseEntity.pClippingWeapon = mem.Read<uintptr_t>(cBaseEntity.C_CSPlayerPawn + Offsets::m_pClippingWeapon);
	cBaseEntity.pNameAddress = mem.Read<uintptr_t>(cBaseEntity.C_CSPlayerController + Offsets::m_sSanitizedPlayerName);
	cBaseEntity.pBulletService = mem.Read<uintptr_t>(cBaseEntity.C_CSPlayerPawn + Offsets::m_pBulletServices);
	cBaseEntity.pCameraService = mem.Read<uintptr_t>(cBaseEntity.C_CSPlayerPawn + Offsets::m_pCameraServices);
	cBaseEntity.pViewAngles = mem.Read<Vector3>(cBaseEntity.C_CSPlayerPawn + Offsets::dwViewAngles);

	cBaseEntity.ShotsFired = mem.Read<uint32_t>(cBaseEntity.C_CSPlayerPawn + Offsets::m_iShotsFired);

	mem.ReadRaw(cBaseEntity.pNameAddress, cBaseEntity.Name, sizeof(cBaseEntity.Name));

	cBaseEntity.ID = mem.Read<int>(cBaseEntity.C_CSPlayerController + Offsets::m_pEntity);
	cBaseEntity.Health = mem.Read<int>(cBaseEntity.C_CSPlayerPawn + Offsets::m_iHealth);
	cBaseEntity.Armor = mem.Read<int>(cBaseEntity.C_CSPlayerPawn + Offsets::m_ArmorValue);
	cBaseEntity.Team = mem.Read<int>(cBaseEntity.C_CSPlayerPawn + Offsets::m_iTeamNum);
	cBaseEntity.Flags = mem.Read<int>(cBaseEntity.C_CSPlayerPawn + Offsets::m_fFlags);
	cBaseEntity.Ping = mem.Read<int>(cBaseEntity.C_CSPlayerController + Offsets::m_iPing);
	cBaseEntity.IDEntIndex = mem.Read<int>(cBaseEntity.C_CSPlayerPawn + Offsets::m_iIDEntIndex);
	cBaseEntity.TotalHits = mem.Read<int>(cBaseEntity.pBulletService + Offsets::m_totalHitsOnServer);

	cBaseEntity.IsScoped = mem.Read<bool>(cBaseEntity.C_CSPlayerPawn + Offsets::m_bIsScoped);
	cBaseEntity.IsDormant = mem.Read<bool>(cBaseEntity.C_CSPlayerPawn + Offsets::m_bDormant);
	cBaseEntity.IsVisible = mem.Read<bool>(cBaseEntity.C_CSPlayerPawn + Offsets::m_entitySpottedState + Offsets::m_bSpotted);

	cBaseEntity.Position3D = mem.Read<Vector3>(cBaseEntity.C_CSPlayerPawn + Offsets::m_vOldOrigin);
	cBaseEntity.EyeAngles3D = mem.Read<Vector3>(cBaseEntity.C_CSPlayerPawn + Offsets::m_angEyeAngles);
	cBaseEntity.EyePosition3D = mem.Read<Vector3>(cBaseEntity.C_CSPlayerPawn + Offsets::m_angEyeAngles);
	cBaseEntity.EyePosition3D = mem.Read<Vector3>(cBaseEntity.C_CSPlayerPawn + Offsets::m_vOldOrigin) + mem.Read<Vector3>(cBaseEntity.C_CSPlayerPawn + Offsets::m_vOldOrigin);
	cBaseEntity.HeadPosition3D = mem.Read<Vector3>(cBaseEntity.pBoneMatrix + (BoneIndex::HEAD * 0x20));
	cBaseEntity.Velocity = mem.Read<Vector3>(cBaseEntity.C_CSPlayerPawn + Offsets::m_vecAbsVelocity);

	cBaseEntity.Position2D = cBaseEntity.Position3D.WorldToScreen(Instance<CGame>::Get().ViewMatrix).ToVector2();
	cBaseEntity.EyeAngles2D = cBaseEntity.EyeAngles3D.WorldToScreen(Instance<CGame>::Get().ViewMatrix).ToVector2();
	cBaseEntity.HeadPosition2D = cBaseEntity.HeadPosition3D.WorldToScreen(Instance<CGame>::Get().ViewMatrix).ToVector2();
	cBaseEntity.EyePosition2D = cBaseEntity.EyePosition3D.WorldToScreen(Instance<CGame>::Get().ViewMatrix).ToVector2();

	cBaseEntity.AimPunchCache = mem.Read<C_UTL_VECTOR>(cBaseEntity.C_CSPlayerPawn + Offsets::m_aimPunchCache);

	cBaseEntity.AimPunchAngle = mem.Read<float>(cBaseEntity.C_CSPlayerPawn + Offsets::m_aimPunchAngle);
	cBaseEntity.MouseSensitivity = mem.Read<float>(mem.Read<uintptr_t>(ClientDll + Offsets::dwSensitivity) + Offsets::dwSensitivity_sensitivity);
}

// updating entities based on the entities pawn and controller inherits from CBaseEntity class (skips localplayer)
void CSourceEngine::UpdatePlayerEntities()
{
	CEntity cEntity;
	std::lock_guard<std::mutex> lock(this->CEntityListMutex);
	this->CEntityList.clear();

	uintptr_t pEntityList = mem.Read<uintptr_t>(ClientDll + Offsets::dwEntityList);

	for (int i = 0; i < 64; i++)
	{
		uintptr_t pListEntry = mem.Read<uintptr_t>(pEntityList + (8 * (i & 0x7FFF) >> 9) + 16);
		if (!pListEntry)
			continue;

		uintptr_t C_CSPlayerController = mem.Read<uintptr_t>(pListEntry + 120 * (i & 0x1FF));
		if (!C_CSPlayerController)
			continue;

		uint32_t pPawnHandle = mem.Read<uint32_t>(C_CSPlayerController + Offsets::m_hPlayerPawn);
		if (!pPawnHandle)
			continue;

		uintptr_t pListEntry2 = mem.Read<uintptr_t>(pEntityList + 0x8 * ((pPawnHandle & 0x7FFF) >> 9) + 16);
		if (!pListEntry2)
			continue;

		uintptr_t C_CSPlayerPawn = mem.Read<uintptr_t>(pListEntry2 + 120 * (pPawnHandle & 0x1FF));
		if (!C_CSPlayerPawn)
			continue;

		uintptr_t pEntityID = mem.Read<uintptr_t>(C_CSPlayerController + Offsets::m_pEntity);
		if (!pEntityID)
			continue;

		uintptr_t pDesignerName = mem.Read<uintptr_t>(pEntityID + Offsets::m_designerName);
		if (!pDesignerName)
			continue;

		cEntity.pDesignerName = pDesignerName;
		cEntity.Index = i;

		int health = mem.Read<int>(C_CSPlayerPawn + Offsets::m_iHealth);
		if (health <= 0) continue;

		if (C_CSPlayerPawn == Instance<CLocalPlayer>::Get().C_CSPlayerPawn)
			continue;

		cEntity.C_CSPlayerPawn = C_CSPlayerPawn;
		cEntity.C_CSPlayerController = C_CSPlayerController;

		this->GetCBaseEntity(cEntity);
		CEntityList.push_back(cEntity);
	}
}

// Updates Localplayer based on the Pawn and Controller inherits from CBaseEntity class
void CSourceEngine::UpdateLocalPlayer()
{
	uintptr_t C_CSPlayerPawn = mem.Read<uintptr_t>(ClientDll + Offsets::dwLocalPlayerPawn);
	uintptr_t C_CSPlayerController = mem.Read<uintptr_t>(ClientDll + Offsets::dwLocalPlayerController);

	Instance<CLocalPlayer>::Get().C_CSPlayerPawn = C_CSPlayerPawn;
	Instance<CLocalPlayer>::Get().C_CSPlayerController = C_CSPlayerController;

	this->GetCBaseEntity(Instance<CLocalPlayer>::Get());
}

void CSourceEngine::UpdateGame()
{
	Instance<CGame>::Get().EntityList = mem.Read<uintptr_t>(ClientDll + Offsets::dwEntityList);
	Instance<CGame>::Get().MaxEntities = mem.Read<uintptr_t>(ClientDll + Offsets::dwGameEntitySystem_highestEntityIndex);
	Instance<CGame>::Get().ViewMatrix = mem.Read<Matrix4x4>(ClientDll + Offsets::dwViewMatrix);
}

void CSourceEngine::IterateEntities()
{
	int loops = 0;

	while (true)
	{
		if (loops > 15) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			UpdatePlayerEntities();
			loops = 0;
		}

		++loops;	
	}
}

void CSourceEngine::UpdateEngine()
{
	this->UpdateLocalPlayer();
	this->UpdateGame();
}
