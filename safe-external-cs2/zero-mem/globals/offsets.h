#pragma once

namespace C_SmokeGrenadeProjectile {
    inline std::ptrdiff_t m_nSmokeEffectTickBegin = 0x1210; // int32
    inline std::ptrdiff_t m_bDidSmokeEffect = 0x1214; // bool
    inline std::ptrdiff_t m_nRandomSeed = 0x1218; // int32
    inline std::ptrdiff_t m_vSmokeColor = 0x121C; // Vector
    inline std::ptrdiff_t m_vSmokeDetonationPos = 0x1228; // Vector
    inline std::ptrdiff_t m_VoxelFrameData = 0x1238; // C_NetworkUtlVectorBase<uint8>
    inline std::ptrdiff_t m_nVoxelFrameDataSize = 0x1250; // int32
    inline std::ptrdiff_t m_nVoxelUpdate = 0x1254; // int32
    inline std::ptrdiff_t m_bSmokeVolumeDataReceived = 0x1258; // bool
    inline std::ptrdiff_t m_bSmokeEffectSpawned = 0x1259; // bool
}

namespace C_PostProcessingVolume {
    inline std::ptrdiff_t m_hPostSettings = 0xD40; // CStrongHandle<InfoForResourceTypeCPostProcessingResource>
    inline std::ptrdiff_t m_flFadeDuration = 0xD48; // float32
    inline std::ptrdiff_t m_flMinLogExposure = 0xD4C; // float32
    inline std::ptrdiff_t m_flMaxLogExposure = 0xD50; // float32
    inline std::ptrdiff_t m_flMinExposure = 0xD54; // float32
    inline std::ptrdiff_t m_flMaxExposure = 0xD58; // float32
    inline std::ptrdiff_t m_flExposureCompensation = 0xD5C; // float32
    inline std::ptrdiff_t m_flExposureFadeSpeedUp = 0xD60; // float32
    inline std::ptrdiff_t m_flExposureFadeSpeedDown = 0xD64; // float32
    inline std::ptrdiff_t m_flTonemapEVSmoothingRange = 0xD68; // float32
    inline std::ptrdiff_t m_bMaster = 0xD6C; // bool
    inline std::ptrdiff_t m_bExposureControl = 0xD6D; // bool
    inline std::ptrdiff_t m_flRate = 0xD70; // float32
    inline std::ptrdiff_t m_flTonemapPercentTarget = 0xD74; // float32
    inline std::ptrdiff_t m_flTonemapPercentBrightPixels = 0xD78; // float32
    inline std::ptrdiff_t m_flTonemapMinAvgLum = 0xD7C; // float32
}

namespace C_EnvSky {
    inline std::ptrdiff_t m_hSkyMaterial = 0xD28; // CStrongHandle<InfoForResourceTypeIMaterial2>
    inline std::ptrdiff_t m_hSkyMaterialLightingOnly = 0xD30; // CStrongHandle<InfoForResourceTypeIMaterial2>
    inline std::ptrdiff_t m_bStartDisabled = 0xD38; // bool
    inline std::ptrdiff_t m_vTintColor = 0xD39; // Color
    inline std::ptrdiff_t m_vTintColorLightingOnly = 0xD3D; // Color
    inline std::ptrdiff_t m_flBrightnessScale = 0xD44; // float32
    inline std::ptrdiff_t m_nFogType = 0xD48; // int32
    inline std::ptrdiff_t m_flFogMinStart = 0xD4C; // float32
    inline std::ptrdiff_t m_flFogMinEnd = 0xD50; // float32
    inline std::ptrdiff_t m_flFogMaxStart = 0xD54; // float32
    inline std::ptrdiff_t m_flFogMaxEnd = 0xD58; // float32
    inline std::ptrdiff_t m_bEnabled = 0xD5C; // bool
}

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