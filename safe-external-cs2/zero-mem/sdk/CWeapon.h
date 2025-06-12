#pragma once
#include <sdk/sdk.h>

static std::unordered_map<std::string, std::string> weapon_icon_table = {
    {xorstr_("deagle"), "\xEE\x80\x81"},
    {xorstr_("elite"), "\xEE\x80\x82"},
    {xorstr_("fiveseven"), "\xEE\x80\x83"},
    {xorstr_("glock"), "\xEE\x80\x84"},
    {xorstr_("ak47"), "\xEE\x80\x87"},
    {xorstr_("aug"), "\xEE\x80\x88"},
    {xorstr_("awp"), "\xEE\x80\x89"},
    {xorstr_("famas"), "\xEE\x80\x8A"},
    {xorstr_("g3sg1"), "\xEE\x80\x8B"},
    {xorstr_("galilar"), "\xEE\x80\x8D"},
    {xorstr_("m249"), "\xEE\x80\xBC"},
    {xorstr_("m4a1"), "\xEE\x80\x8E"},
    {xorstr_("mac10"), "\xEE\x80\x91"},
    {xorstr_("p90"), "\xEE\x80\xA4"},
    {xorstr_("mp5sd"), "\xEE\x80\x98"},
    {xorstr_("ump45"), "\xEE\x80\x98"},
    {xorstr_("xm1014"), "\xEE\x80\x99"},
    {xorstr_("bizon"), "\xEE\x80\x9A"},
    {xorstr_("mag7"), "\xEE\x80\x9B"},
    {xorstr_("negev"), "\xEE\x80\x9C"},
    {xorstr_("sawedoff"), "\xEE\x80\x9D"},
    {xorstr_("tec9"), "\xEE\x80\x9E"},
    {xorstr_("taser"), "\xEE\x80\x9F"},
    {xorstr_("hkp2000"), "\xEE\x80\x93"},
    {xorstr_("mp7"), "\xEE\x80\xA1"},
    {xorstr_("mp9"), "\xEE\x80\xA2"},
    {xorstr_("nova"), "\xEE\x80\xA3"},
    {xorstr_("p250"), "\xEE\x80\xA0"},
    {xorstr_("shield"), "shield"},
    {xorstr_("scar20"), "\xEE\x80\xA6"},
    {xorstr_("sg553"), "\xEE\x80\xA7"},
    {xorstr_("ssg08"), "\xEE\x80\xA8"},
    {xorstr_("knife_gg"), "knife_gg"},
    {xorstr_("knife"), "\xEE\x80\xAA"},
    {xorstr_("flashbang"), "\xEE\x80\xAB"},
    {xorstr_("hegrenade"), "\xEE\x80\xAC"},
    {xorstr_("smokegrenade"), "\xEE\x80\xAD"},
    {xorstr_("molotov"), "\xEE\x80\xAE"},
    {xorstr_("decoy"), "\xEE\x80\xAF"},
    {xorstr_("incgrenade"), "\xEE\x80\xB0"},
    {xorstr_("c4"), "\xEE\x80\xB1"},
    {xorstr_("knife_t"), "\xEE\x80\xBB"},
    {xorstr_("m4a1_silencer"), "\xEE\x80\x90"},
    {xorstr_("usp_silencer"), "\xEE\x80\xBD"},
    {xorstr_("cz75a"), "\xEE\x80\xBF"},
    {xorstr_("revolver"), "\xEE\x81\x80"},
    {xorstr_("knife_bayonet"), "\xEE\x87\xB4"},
    {xorstr_("knife_css"), "\xEE\x80\xAA"},
    {xorstr_("knife_flip"), "\xEE\x87\xB9"},
    {xorstr_("knife_gut"), "\xEE\x87\xBA"},
    {xorstr_("knife_karambit"), "\xEE\x87\xBB"},
    {xorstr_("knife_m9_bayonet"), "\xEE\x87\xBC"},
    {xorstr_("knife_tactical"), "\xEE\x87\xBD"},
    {xorstr_("knife_falchion"), "\xEE\x88\x80"},
    {xorstr_("knife_survival_bowie"), "\xEE\x88\x82"},
    {xorstr_("knife_butterfly"), "\xEE\x88\x83"},
    {xorstr_("knife_push"), "\xEE\x88\x84"},
    {xorstr_("knife_cord"), "\xEE\x80\xAA"},
    {xorstr_("knife_canis"), "\xEE\x80\xAA"},
    {xorstr_("knife_ursus"), "\xEE\x80\xAA"},
    {xorstr_("knife_gypsy_jackknife"), "\xEE\x80\xAA"},
    {xorstr_("knife_outdoor"), "\xEE\x80\xAA"},
    {xorstr_("knife_stiletto"), "\xEE\x80\xAA"},
    {xorstr_("knife_widowmaker"), "\xEE\x80\xAA"},
    {xorstr_("knife_skeleton"), "\xEE\x80\xAA"}
};

class CWeapon {
private:
    std::unordered_map<uintptr_t, std::string> EquippedWeapon;

public:
    CWeapon() {}
    ~CWeapon() {}

    CWeapon(const CWeapon&) = delete;
    CWeapon& operator=(const CWeapon&) = delete;

    uintptr_t ClippingWeapon = 0;
    uintptr_t EntityID = 0;

    void Update();

    std::string GetEquippedWeapon();

    const char* GetWeaponIcon(std::string& weapon);
};