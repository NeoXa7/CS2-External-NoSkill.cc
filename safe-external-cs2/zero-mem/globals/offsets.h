#pragma once
namespace Offsets
{
	// Client.dll 
    inline auto dwEntityList = 0x1A1F670;
    inline auto dwLocalPlayerPawn = 0x1874040;
    inline auto dwViewMatrix = 0x1A89070;
    inline auto dwViewAngles = 0x1A93300;
    inline auto dwLocalPlayerController = 0x1A1F670;
    inline auto dwGameEntitySystem_highestEntityIndex = 0x20F0;
    inline auto dwSensitivity = 0x1A856A8;
    inline auto dwSensitivity_sensitivity = 0x40;

    inline auto m_iJump = 0x186CD50;
    inline auto m_hPlayerPawn = 0x814;
    inline auto m_iHealth = 0x344;
    inline auto m_iTeamNum = 0x3E3;
    inline auto m_ArmorValue = 0x241C;
    inline auto m_sSanitizedPlayerName = 0x770;
    inline auto m_vOldOrigin = 0x1324;
    inline auto m_vecAbsVelocity = 0x3F0;
    inline auto m_bIsScoped = 0x23E8;
    inline auto m_iShotsFired = 0x23FC;
    inline auto m_fFlags = 0x3EC;
    inline auto m_bDormant = 0xEF;
    inline auto m_groundNormal = 0x1F0;
    inline auto m_pGameSceneNode = 0x328;
    inline auto m_vecViewOffset = 0xCB0;
    inline auto m_angEyeAngles = 0x1438;
    inline auto m_pClippingWeapon = 0x13A0;
    inline auto m_pEntity = 0x10;
    inline auto m_designerName = 0x20;
    inline auto m_aimPunchCache = 0x15A8;
    inline auto m_iIDEntIndex = 0x1458;
    inline auto m_aimPunchAngle = 0x1584;
    inline auto m_iPing = 0x740;
    inline auto m_pBulletServices = 0x1518;
    inline auto m_totalHitsOnServer = 0x40;
    inline auto m_flFlashMaxAlpha = 0x1408;
    inline auto m_pCameraServices = 0x11E0;
    inline auto m_iFOV = 0x210;
    inline auto m_bSpotted = 0x8;
    inline auto m_bSpottedByMask = 0xC;
    inline auto m_entitySpottedState = 0x23D0;

    inline void DumpOffsets() {
        std::ofstream file(std::string(BASE_DIRECTORY) + "/dump.asm");
        file << "inline auto dwEntityList = " << "0x" << std::uppercase << std::hex << Offsets::dwEntityList << ";" << '\n';
        file << "inline auto dwLocalPlayerPawn = " << "0x" << std::uppercase << std::hex << Offsets::dwLocalPlayerPawn << ";" << '\n';
        file << "inline auto dwViewMatrix = " << "0x" << std::uppercase << std::hex << Offsets::dwViewMatrix << ";" << '\n';
        file << "inline auto dwViewAngles = " << "0x" << std::uppercase << std::hex << Offsets::dwViewAngles << ";" << '\n';
        file << "inline auto dwLocalPlayerController = " << "0x" << std::uppercase << std::hex << Offsets::dwEntityList << ";" << '\n';
        file << "inline auto dwGameEntitySystem_highestEntityIndex = " << "0x" << std::uppercase << std::hex << Offsets::dwGameEntitySystem_highestEntityIndex << ";" << '\n';
        file << "inline auto dwSensitivity = " << "0x" << std::uppercase << std::hex << Offsets::dwSensitivity << ";" << '\n';
        file << "inline auto dwSensitivity_sensitivity = " << "0x" << std::uppercase << std::hex << Offsets::dwSensitivity_sensitivity << ";" << '\n';
        file << '\n';
        file << "inline auto m_hPlayerPawn = " << "0x" << std::uppercase << std::hex << Offsets::m_hPlayerPawn << ";" << '\n';
        file << "inline auto m_iHealth = " << "0x" << std::uppercase << std::hex << Offsets::m_iHealth << ";" << '\n';
        file << "inline auto m_iTeamNum = " << "0x" << std::uppercase << std::hex << Offsets::m_iTeamNum << ";" << '\n';
        file << "inline auto m_ArmorValue = " << "0x" << std::uppercase << std::hex << Offsets::m_ArmorValue << ";" << '\n';
        file << "inline auto m_sSanitizedPlayerName = " << "0x" << std::uppercase << std::hex << Offsets::m_sSanitizedPlayerName << ";" << '\n';
        file << "inline auto m_vOldOrigin = " << "0x" << std::uppercase << std::hex << Offsets::m_vOldOrigin << ";" << '\n';
        file << "inline auto m_vecAbsVelocity = " << "0x" << std::uppercase << std::hex << Offsets::m_vecAbsVelocity << ";" << '\n';
        file << "inline auto m_bIsScoped = " << "0x" << std::uppercase << std::hex << Offsets::m_bIsScoped << ";" << '\n';
        file << "inline auto m_iShotsFired = " << "0x" << std::uppercase << std::hex << Offsets::m_iShotsFired << ";" << '\n';
        file << "inline auto m_fFlags = " << "0x" << std::uppercase << std::hex << Offsets::m_fFlags << ";" << '\n';
        file << "inline auto m_bDormant = " << "0x" << std::uppercase << std::hex << Offsets::m_bDormant << ";" << '\n';
        file << "inline auto m_groundNormal = " << "0x" << std::uppercase << std::hex << Offsets::m_groundNormal << ";" << '\n';
        file << "inline auto m_pGameSceneNode = " << "0x" << std::uppercase << std::hex << Offsets::m_pGameSceneNode << ";" << '\n';
        file << "inline auto m_vecViewOffset = " << "0x" << std::uppercase << std::hex << Offsets::m_vecViewOffset << ";" << '\n';
        file << "inline auto m_angEyeAngles = " << "0x" << std::uppercase << std::hex << Offsets::m_angEyeAngles << ";" << '\n';
        file << "inline auto m_pClippingWeapon = " << "0x" << std::uppercase << std::hex << Offsets::m_pClippingWeapon << ";" << '\n';
        file << "inline auto m_pEntity = " << "0x" << std::uppercase << std::hex << Offsets::m_pEntity << ";" << '\n';
        file << "inline auto m_designerName = " << "0x" << std::uppercase << std::hex << Offsets::m_designerName << ";" << '\n';
        file << "inline auto m_aimPunchCache = " << "0x" << std::uppercase << std::hex << Offsets::m_aimPunchCache << ";" << '\n';
        file << "inline auto m_iIDEntIndex = " << "0x" << std::uppercase << std::hex << Offsets::m_iIDEntIndex << ";" << '\n';
        file << "inline auto m_aimPunchAngle = " << "0x" << std::uppercase << std::hex << Offsets::m_aimPunchAngle << ";" << '\n';
        file << "inline auto m_iPing = " << "0x" << std::uppercase << std::hex << Offsets::m_iPing << ";";
        file.close();
    }
}