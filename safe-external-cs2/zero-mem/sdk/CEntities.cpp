#include <pch.h>
#include "CEntities.h"

CEntity* CEntityCollection::FindEntityByName(CEntity& entity, std::string name) {
	if (name == entity.Name) {
		std::cout << "Entity found : " << entity.Name << '\n';
		return &entity;
	}
	return nullptr;
}

CEntity* CEntityCollection::FindEntityWithHealth(CEntity& entity, int health) {
	if (health == entity.Health) {
		std::cout << "Entity found : " << entity.Name << '\n';
		return &entity;
	}
	return nullptr;
}

CEntity* CEntityCollection::FindEntityWithHealthLessThan(CEntity& entity, int health) {
	if (entity.Health < health) {
		std::cout << "Entity found : " << entity.Name << '\n';
		return &entity;
	}
	return nullptr;
}

CEntity* CEntityCollection::FindEntityWithHealthGreaterThan(CEntity& entity, int health) {
	if (entity.Health > health) {
		std::cout << "Entity found : " << entity.Name << '\n';
		return &entity;
	}
	return nullptr;
}

CEntity* CEntityCollection::FindClosestEntity(CEntity& entity) {
	CEntity* closest_entity = nullptr;
	float min_distance = FLT_MAX;

	float distance = (entity.Position3D - Instance<CLocalPlayer>::Get().Position3D).Length();
	if (distance < min_distance) {
		min_distance = distance;
		closest_entity = &entity;
	}

	return closest_entity;
}