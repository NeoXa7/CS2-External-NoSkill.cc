#pragma once
#include "CBaseEntity.h"
#include "CLocalPlayer.h"

class CEntity : public CBaseEntity { public: };

class CEntityCollection
{
public:
	CEntityCollection() {}
	~CEntityCollection() {}

	CEntityCollection(const CEntityCollection&) = delete;
	CEntityCollection& operator=(const CEntityCollection&) = delete;

	CEntity* FindEntityByName(CEntity& entity, std::string name);
	CEntity* FindEntityWithHealth(CEntity& entity, int health);
	CEntity* FindEntityWithHealthLessThan(CEntity& entity, int health);
	CEntity* FindEntityWithHealthGreaterThan(CEntity& entity, int health);
	CEntity* FindClosestEntity(CEntity& entity);
};