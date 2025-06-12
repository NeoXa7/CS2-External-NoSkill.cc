#include <pch.h>
#include "CBaseEntity.h"
#include "defs.h"

Vector3 CBaseEntity::GetBone3D(BoneIndex type) {
	Vector3 bone_3d = mem.Read<Vector3>(this->pBoneMatrix + (type * 0x20));
	return bone_3d;
}

Vector2 CBaseEntity::GetBone2D(BoneIndex type) {
	Vector3 bone_3d = this->GetBone3D(type);
	Vector3 bone_2d = bone_3d.WorldToScreen(Instance<CGame>::Get().ViewMatrix);
	return bone_2d.ToVector2();
}

bool CBaseEntity::IsDead() {
	if (this->Health <= 0)
		return true;

	return false;
}

bool CBaseEntity::IsSameTeam(int& other_team) {
	if (this->Team == other_team)
		return true;

	return false;
}

ImColor CBaseEntity::GetHealthColor() {
	int health = std::clamp(this->Health, 0, 100);
	float t = health / 100.0f;

	ImVec4 color;

	if (t > 0.5f) {
		// Green to Yellow (100–50 HP)
		float interp = (t - 0.5f) * 2.0f; // Range: 0 to 1
		color.x = (1.0f - interp); // Red goes from 0 → 1
		color.y = 1.0f;            // Green stays full
		color.z = 0.0f;
	}
	else {
		// Yellow to Red (50–0 HP)
		float interp = t * 2.0f; // Range: 0 to 1
		color.x = 1.0f;
		color.y = interp;       // Green fades from 1 → 0
		color.z = 0.0f;
	}

	color.w = 1.0f;
	return ImColor(color);
}

Vector3 CBaseEntity::GetCurrentViewAngles()
{
	return mem.Read<Vector3>(SourceEngine.ClientDll + Offsets::dwViewAngles);
}

void CBaseEntity::SetViewAngles(Vector3& angles)
{
	mem.Write<Vector3>(SourceEngine.ClientDll + Offsets::dwViewAngles, angles);
}
