#pragma once
#include "CBaseEntity.h"

class CLocalPlayer : public CBaseEntity {
public:
    CLocalPlayer() {}
    ~CLocalPlayer() {}

    CLocalPlayer(const CLocalPlayer&) = delete;
    CLocalPlayer& operator=(const CLocalPlayer&) = delete;
};