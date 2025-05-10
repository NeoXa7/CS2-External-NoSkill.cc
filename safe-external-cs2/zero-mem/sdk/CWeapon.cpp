#include "CWeapon.h"

void CWeapon::Update(CEntity& entities) {
    char Buffer[120] = { 0 };

    uintptr_t WeaponHandle = mem.Read<uintptr_t>(entities.pClippingWeapon + 0x10);
    uintptr_t WeaponAddress = mem.Read<uintptr_t>(WeaponHandle + 0x20);

    mem.ReadRaw(WeaponAddress, Buffer, sizeof(Buffer));
    std::string weapon_n = std::string(Buffer);

    if (weapon_n.compare(0, 7, "weapon_") == 0) {
        std::string currentWeapon = weapon_n.substr(7);
        EquippedWeapon[entities.ID] = currentWeapon;
    }
}

std::string CWeapon::GetEquippedWeapon(uintptr_t entity)
{
    auto it = EquippedWeapon.find(entity);
    if (it != EquippedWeapon.end()) {
        return it->second;
    }
    return xorstr_("Invalid Weapon ID");
}

const char* CWeapon::GetWeaponIcon(std::string& weapon)
{
    auto it = weapon_icon_table.find(weapon);
    if (it != weapon_icon_table.end()) {
        return it->second.c_str();
    }
    return "";
}