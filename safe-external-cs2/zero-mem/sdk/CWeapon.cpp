#include "CWeapon.h"

void CWeapon::Update() {
    char Buffer[120] = { 0 };

    uintptr_t WeaponHandle = mem.Read<uintptr_t>(this->ClippingWeapon + 0x10);
    uintptr_t WeaponAddress = mem.Read<uintptr_t>(WeaponHandle + 0x20);

    mem.ReadRaw(WeaponAddress, Buffer, sizeof(Buffer));
    std::string weapon_n = std::string(Buffer);

    if (weapon_n.compare(0, 7, "weapon_") == 0) {
        std::string currentWeapon = weapon_n.substr(7);
        EquippedWeapon[this->EntityID] = currentWeapon;
    }
}

std::string CWeapon::GetEquippedWeapon()
{
    auto it = EquippedWeapon.find(this->EntityID);
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