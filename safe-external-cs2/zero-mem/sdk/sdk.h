#pragma once
#include "CBaseEntity.h"
#include "CEntities.h"
#include "CLocalPlayer.h"
#include "CBone.h"
#include "CGame.h"
#include "CWeapon.h"
#include "maths/maths.h"
#include "maths/matrix.h"
#include "maths/vector.h"
#include <utils/mouse.h>

#define S_INAIR 65664
#define S_STANDING 65665
#define S_CROUCHING 65667
#define T_SPECTATOR 1
#define T_TERRORIST 2
#define T_COUNTER_TERRORIST 3
#define T_COLOR ImColor(234, 209, 139)
#define CT_COLOR ImColor(182, 212, 238, 255)
#define POST_PROCESSING_VOLUME "post_processing_volume"
#define C_ENV_SKY "env_sky"
#define SMOKE_GRENADE_PROJECTILE "smokegrenade_projectile"

enum INPUT_MODE : INT {
	AUTO = 0,
	HOLD = 1,
};

inline void FireMacro(float delay, float fire_rate) {
	Sleep(delay);
	MOUSE::LeftClick();
	Sleep(fire_rate);
}

class CSourceEngine
{
public:
	CSourceEngine() {}
	~CSourceEngine() {}

	CSourceEngine(const CSourceEngine&) = delete;
	CSourceEngine& operator=(const CSourceEngine&) = delete;

	const char* ProcessName = "cs2.exe";
	uint32_t  ProcessID = NULL;
	uintptr_t ClientDll = NULL;
	uintptr_t Engine2Dll = NULL;


private:
	std::vector<CEntity> CEntityList;
	std::mutex CEntityListMutex;

	// main function to get the base entity
	void GetCBaseEntity(CBaseEntity& entity);

	// Updates Entities (64) based on the Pawn and Controller inherits from CBaseEntity class (skips localplayer)
	void UpdatePlayerEntities();

	// Updates Localplayer based on the Pawn and Controller inherits from CBaseEntity class
	void UpdateLocalPlayer();

	// Updates required game variables
	void UpdateGame();

public:
	// basically main function of this class
	void IterateEntities(); // skips localplayer

	void UpdateEngine();

	// Use this to lock the entity list from outside when using GetEntityListRef()
	// Example:
	// std::lock_guard<std::mutex> lock(engine.GetEntityListMutex());
	std::mutex& GetEntityListMutex() {
		return this->CEntityListMutex;
	}

	// Use this when you want fast, direct access to the entity list
	// - Caller MUST lock the mutex before using
	// - High performance, no copy made
	// - Complex to Use
	// Example:
	// std::lock_guard<std::mutex> lock(engine.GetEntityListMutex());
	// auto& entities = engine.GetEntityListRef();
	// for (const auto& entity : entities) { your logic }
	std::vector<CEntity>& GetEntityListRef() {
		return this->CEntityList;
	}
};