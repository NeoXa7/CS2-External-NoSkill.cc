#pragma once
#include <globals/imports.h>
#include <globals/offsets.h>
#include <libs/json.hpp>
#include <libs/xorstr.h>

// slow but gets the job done

using json = nlohmann::json;
namespace fs = std::filesystem;

#ifdef _WIN32
inline std::time_t timegm(std::tm* tm) {
    return _mkgmtime(tm);
}
#endif

class Updater {
private:
    const std::string a2x_dumper_api = PROTECT("https://api.github.com/repos/a2x/cs2-dumper/commits");

    const std::vector<std::pair<std::string, std::string>> files_to_update = {
        {"https://github.com/a2x/cs2-dumper/raw/main/output/offsets.json", PROTECT("offsets.json")},
        {"https://github.com/a2x/cs2-dumper/raw/main/output/client_dll.json", PROTECT("client_dll.json")},
        {"https://github.com/a2x/cs2-dumper/raw/main/output/buttons.json", PROTECT("buttons.json")},
    };

    std::vector<std::string> Files = { PROTECT("offsets.json"), PROTECT("client_dll.json"), PROTECT("buttons.json") };

    bool FileExists(const std::string& path) const {
        return fs::exists(path) && fs::is_regular_file(path);
    }

    bool DownloadFile(const std::string& url, const std::string& local_path) {
        HINTERNET hInternet = InternetOpen(PROTECT("Updater"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) return false;

        HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (!hConnect) {
            InternetCloseHandle(hInternet);
            return false;
        }

        std::ofstream file(local_path, std::ios::binary);
        if (!file) {
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternet);
            return false;
        }

        char buffer[4096];
        DWORD bytes_read;
        while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytes_read) && bytes_read > 0) {
            file.write(buffer, bytes_read);
        }

        file.close();
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return true;
    }

    bool GetLatestCommitDate(std::time_t& out_time) {
        HINTERNET hInternet = InternetOpenA(PROTECT("Updater"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (!hInternet) return false;

        HINTERNET hConnect = InternetOpenUrlA(hInternet, a2x_dumper_api.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (!hConnect) {
            InternetCloseHandle(hInternet);
            return false;
        }

        std::string response;
        char buffer[4096];
        DWORD bytesRead;
        while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
            response.append(buffer, bytesRead);
        }

        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);

        try {
            auto data = json::parse(response);
            if (data.empty() || !data.is_array()) return false;

            std::string commit_date = data[0][PROTECT("commit")][PROTECT("author")][PROTECT("date")];
            std::tm tm = {};
            std::istringstream ss(commit_date);
            ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
            out_time = timegm(&tm);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    bool IsFileOutdated(const std::string& path, std::time_t commit_time) const {
        if (!FileExists(path)) return true;

        auto file_time = fs::last_write_time(path);
        auto file_sys_time = std::chrono::system_clock::now() + (file_time - fs::file_time_type::clock::now());
        return std::chrono::system_clock::to_time_t(file_sys_time) < commit_time;
    }

    bool ParseJsonFromFile(const std::string& fileName, json& outJson) {
        std::ifstream inFile(fileName, std::ios::binary);
        if (!inFile) {
            std::cerr << PROTECT(" [NoSkill.cc] Failed to open ") << fileName << "." << std::endl;
            return false;
        }

        std::string fileContent((std::istreambuf_iterator<char>(inFile)),
            std::istreambuf_iterator<char>());
        inFile.close();

        try {
            outJson = json::parse(fileContent);
        }
        catch (const json::parse_error& e) {
            std::cerr << PROTECT(" [NoSkill.cc] JSON parse error in ") << fileName
                << " at byte " << e.byte << ": " << e.what() << std::endl;
            return false;
        }

        return true;
    }

public:
    std::string offsets_directory = std::string(BASE_DIRECTORY) + "/offsets/";

    bool NeedsUpdate() {
        std::time_t commit_time;
        if (!GetLatestCommitDate(commit_time)) {
            std::cout << PROTECT(" [NoSkill.cc] Failed to fetch latest commit info.\n");
            std::cout << PROTECT(" [NoSkill.cc] Try downloading manually.\n");
            return false;
        }

        for (const auto& [url, filename] : files_to_update) {
            std::string local_path = offsets_directory + "/" + filename;
            if (IsFileOutdated(local_path, commit_time)) {
                return true;
            }
        }

        return false;
    }

    bool DownloadOffsets() {
        std::time_t commit_time;
        if (!GetLatestCommitDate(commit_time)) {
            std::cout << PROTECT(" [NoSkill.cc] Failed to fetch latest commit info.\n");
            std::cout << PROTECT(" [NoSkill.cc] Try downloading manually.\n");
            return false;
        }

        if (!fs::exists(offsets_directory)) {
            fs::create_directories(offsets_directory);
        }

        for (const auto& [url, filename] : files_to_update) {
            std::string path = offsets_directory + filename;

            std::ofstream file(path);

            if (!file.is_open())
                return false;

            if (DownloadFile(url, path)) {
                std::cout << PROTECT(" [NoSkill.cc] Updated : ") << filename << "\n";
            }
            else {
                std::cout << PROTECT(" [NoSkill.cc] Failed to update/download: ") << filename << "\n";
            }

            file.close();
        }

        return true;
    }

    bool UpdateOffsets() {
        for (const auto& file : Files) {
            std::string filePath = offsets_directory + file;
            json Data;
            if (!FileExists(filePath)) {
                std::cerr << PROTECT(" [NoSkill.cc] ") << filePath << PROTECT(" not found.") << std::endl;
                continue;
            }

            if (!ParseJsonFromFile(filePath, Data)) {
                std::cout << PROTECT("  [NoSkill.cc] Failed to reload Offsets! (Failed to parse Json File)\n") << '\n';
                return false;
            }

            const auto& Client = Data[PROTECT("client.dll")];
            const auto& Matchmaking = Data[PROTECT("matchmaking.dll")];
            const auto& Engine2 = Data[PROTECT("engine2.dll")];

            if (file == PROTECT("offsets.json"))
            {
                Offsets::dwEntityList = Client[PROTECT("dwEntityList")];
                Offsets::dwLocalPlayerPawn = Client[PROTECT("dwLocalPlayerPawn")];
                Offsets::dwLocalPlayerController = Client[PROTECT("dwLocalPlayerController")];
                Offsets::dwViewAngles = Client[PROTECT("dwViewAngles")];
                Offsets::dwViewMatrix = Client[PROTECT("dwViewMatrix")];
                Offsets::dwSensitivity = Client[PROTECT("dwSensitivity")];
                Offsets::dwSensitivity_sensitivity = Client[PROTECT("dwSensitivity_sensitivity")];
                /*Offsets::dwGameRules = Client["dwGameRules"];
                Offsets::dwPlantedC4 = Client["dwPlantedC4"];
                Offsets::dwGlobalVars = Client["dwGlobalVars"];
                Offsets::dwWeaponC4 = Client["dwWeaponC4"];
                Offsets::dwGameTypes = Matchmaking["dwGameTypes"];
                Offsets::dwGameTypes_mapName = Matchmaking["dwGameTypes_mapName"];
                Offsets::dwBuildNumber = Engine2["dwBuildNumber"];*/
            }
            else if (file == PROTECT("client_dll.json"))
            {
                json client = Data.contains(PROTECT("client.dll"));

                if (Data.contains(PROTECT("client.dll")) && Data[PROTECT("client.dll")].contains(PROTECT("classes"))) {
                    auto& classes = Data[PROTECT("client.dll")][PROTECT("classes")];

                    if (classes.contains("C_CSPlayerPawn")) {
                        auto& C_CSPlayerPawn = classes[PROTECT("C_CSPlayerPawn")][PROTECT("fields")];
                        Offsets::m_ArmorValue = C_CSPlayerPawn[PROTECT("m_ArmorValue")];
                        Offsets::m_iShotsFired = C_CSPlayerPawn[PROTECT("m_iShotsFired")];
                        Offsets::m_aimPunchAngle = C_CSPlayerPawn[PROTECT("m_aimPunchAngle")];
                        Offsets::m_bIsScoped = C_CSPlayerPawn[PROTECT("m_bIsScoped")];
                        Offsets::m_pBulletServices = C_CSPlayerPawn[PROTECT("m_pBulletServices")];
                        Offsets::m_aimPunchCache = C_CSPlayerPawn[PROTECT("m_aimPunchCache")];
                    }

                    if (classes.contains(PROTECT("C_BaseEntity"))) {
                        auto& C_BaseEntity = classes[PROTECT("C_BaseEntity")][PROTECT("fields")];
                        Offsets::m_iTeamNum = C_BaseEntity[PROTECT("m_iTeamNum")];
                        Offsets::m_iHealth = C_BaseEntity[PROTECT("m_iHealth")];
                        Offsets::m_pGameSceneNode = C_BaseEntity[PROTECT("m_pGameSceneNode")];
                        Offsets::m_fFlags = C_BaseEntity[PROTECT("m_fFlags")];
                        Offsets::m_vecAbsVelocity = C_BaseEntity[PROTECT("m_vecAbsVelocity")];
                    }

                    if (classes.contains(PROTECT("CCSPlayerController"))) {
                        auto& CCSPlayerController = classes[PROTECT("CCSPlayerController")][PROTECT("fields")];
                        Offsets::m_hPlayerPawn = CCSPlayerController[PROTECT("m_hPlayerPawn")];
                        Offsets::m_sSanitizedPlayerName = CCSPlayerController[PROTECT("m_sSanitizedPlayerName")];
                        Offsets::m_iPing = CCSPlayerController[PROTECT("m_iPing")];
                    }

                    if (classes.contains("C_CSPlayerPawnBase")) {
                        auto& C_CSPlayerPawnBase = classes["C_CSPlayerPawnBase"]["fields"];
                        Offsets::m_iIDEntIndex = C_CSPlayerPawnBase["m_iIDEntIndex"];
                        Offsets::m_flFlashMaxAlpha = C_CSPlayerPawnBase["m_flFlashMaxAlpha"];
                        Offsets::m_pClippingWeapon = C_CSPlayerPawnBase["m_pClippingWeapon"];
                        Offsets::m_angEyeAngles = C_CSPlayerPawnBase["m_angEyeAngles"];
                    }

                    if (classes.contains("CCSPlayer_BulletServices ")) {
                        auto& CCSPlayer_BulletServices = classes["CCSPlayer_BulletServices "]["fields"];
                        Offsets::m_totalHitsOnServer = CCSPlayer_BulletServices["m_totalHitsOnServer"];
                    }

                    if (classes.contains("C_BasePlayerPawn")) {
                        auto& C_BasePlayerPawn = classes[PROTECT("C_BasePlayerPawn")][PROTECT("fields")];
                        Offsets::m_vOldOrigin = C_BasePlayerPawn[PROTECT("m_vOldOrigin")];
                        Offsets::m_pCameraServices = C_BasePlayerPawn[PROTECT("m_pCameraServices")];
                    }

                    if (classes.contains("C_BaseModelEntity")) {
                        auto& C_BaseModelEntity = classes[PROTECT("C_BaseModelEntity")][PROTECT("fields")];
                        Offsets::m_vecViewOffset = C_BaseModelEntity[PROTECT("m_vecViewOffset")];
                    }

                    if (classes.contains(PROTECT("C_CSGameRules"))) {
                        auto& C_CSGameRules = classes[PROTECT("C_CSGameRules")][PROTECT("fields")];
                        //Offsets::m_bBombPlanted = C_CSGameRules["m_bBombPlanted"];
                        //Offsets::m_bBombDropped = C_CSGameRules["m_bBombDropped"];
                        //Offsets::m_bWarmupPeriod = C_CSGameRules["m_bWarmupPeriod"];
                        //Offsets::m_bCTTimeOutActive = C_CSGameRules["m_bCTTimeOutActive"];
                        //Offsets::m_bTerroristTimeOutActive = C_CSGameRules["m_bTerroristTimeOutActive"];
                    }


                    if (classes.contains("C_PlantedC4")) {
                        auto& C_PlantedC4 = classes[PROTECT("C_PlantedC4")][PROTECT("fields")];
                        /*Offsets::m_nBombSite = C_PlantedC4["m_nBombSite"];
                        Offsets::m_bHasExploded = C_PlantedC4["m_bHasExploded"];
                        Offsets::m_bBeingDefused = C_PlantedC4["m_bBeingDefused"];
                        Offsets::m_flDefuseLength = C_PlantedC4["m_flDefuseLength"];*/
                    }

                    if (classes.contains("CGameSceneNode")) {
                        auto& CGameSceneNode = classes[PROTECT("CGameSceneNode")][PROTECT("fields")];
                        //Offsets::m_vecAbsOrigin = CGameSceneNode[PROTECT("m_vecAbsOrigin")];
                        Offsets::m_bDormant = CGameSceneNode[PROTECT("m_bDormant")];
                    }

                    if (classes.contains(PROTECT("CPlayer_MovementServices_Humanoid")))
                    {
                        auto& CPlayer_MovementServices_Humanoid = classes[PROTECT("CPlayer_MovementServices_Humanoid")][PROTECT("fields")];
                        Offsets::m_groundNormal = CPlayer_MovementServices_Humanoid[PROTECT("m_groundNormal")];
                    }

                    if (classes.contains(PROTECT("CCSPlayerBase_CameraServices")))
                    {
                        auto& CCSPlayerBase_CameraServices = classes[PROTECT("CCSPlayerBase_CameraServices")][PROTECT("fields")];
                        Offsets::m_iFOV = CCSPlayerBase_CameraServices[PROTECT("m_iFOV")];
                    }

                    if (classes.contains(PROTECT("CEntityIdentity")))
                    {
                        auto& CCSPlayerBase_CameraServices = classes[PROTECT("CEntityIdentity")][PROTECT("fields")];
                        Offsets::m_designerName = CCSPlayerBase_CameraServices[PROTECT("m_designerName")];
                    }
                    
                    if (classes.contains(PROTECT("CEntityInstance")))
                    {
                        auto& CCSPlayerBase_CameraServices = classes[PROTECT("CEntityInstance")][PROTECT("fields")];
                        Offsets::m_pEntity = CCSPlayerBase_CameraServices[PROTECT("m_pEntity")];
                    }

                    if (classes.contains(PROTECT("C_SmokeGrenadeProjectile")))
                    {
                        auto& C_SmokeGrenadeProjectile = classes[PROTECT("C_SmokeGrenadeProjectile")][PROTECT("fields")];
                        C_SmokeGrenadeProjectile::m_nSmokeEffectTickBegin = C_SmokeGrenadeProjectile[PROTECT("m_nSmokeEffectTickBegin")];
                        C_SmokeGrenadeProjectile::m_bDidSmokeEffect = C_SmokeGrenadeProjectile[PROTECT("m_bDidSmokeEffect")];
                        C_SmokeGrenadeProjectile::m_nRandomSeed = C_SmokeGrenadeProjectile[PROTECT("m_nRandomSeed")];
                        C_SmokeGrenadeProjectile::m_vSmokeColor = C_SmokeGrenadeProjectile[PROTECT("m_vSmokeColor")];
                        C_SmokeGrenadeProjectile::m_vSmokeDetonationPos = C_SmokeGrenadeProjectile[PROTECT("m_vSmokeDetonationPos")];
                        C_SmokeGrenadeProjectile::m_VoxelFrameData = C_SmokeGrenadeProjectile[PROTECT("m_VoxelFrameData")];
                        C_SmokeGrenadeProjectile::m_nVoxelFrameDataSize = C_SmokeGrenadeProjectile[PROTECT("m_nVoxelFrameDataSize")];
                        C_SmokeGrenadeProjectile::m_nVoxelUpdate = C_SmokeGrenadeProjectile[PROTECT("m_nVoxelUpdate")];
                        C_SmokeGrenadeProjectile::m_bSmokeVolumeDataReceived = C_SmokeGrenadeProjectile[PROTECT("m_bSmokeVolumeDataReceived")];
                        C_SmokeGrenadeProjectile::m_bSmokeEffectSpawned = C_SmokeGrenadeProjectile[PROTECT("m_bSmokeEffectSpawned")];
                    } 
                    
                    if (classes.contains(PROTECT("C_EnvSky")))
                    {
                        auto& C_EnvSky = classes[PROTECT("C_EnvSky")][PROTECT("fields")];
                        C_EnvSky::m_hSkyMaterial = C_EnvSky[PROTECT("m_hSkyMaterial")];
                        C_EnvSky::m_hSkyMaterialLightingOnly = C_EnvSky[PROTECT("m_hSkyMaterialLightingOnly")];
                        C_EnvSky::m_bStartDisabled = C_EnvSky[PROTECT("m_bStartDisabled")];
                        C_EnvSky::m_vTintColor = C_EnvSky[PROTECT("m_vTintColor")];
                        C_EnvSky::m_vTintColorLightingOnly = C_EnvSky[PROTECT("m_vTintColorLightingOnly")];
                        C_EnvSky::m_flBrightnessScale = C_EnvSky[PROTECT("m_flBrightnessScale")];
                        C_EnvSky::m_nFogType = C_EnvSky[PROTECT("m_nFogType")];
                        C_EnvSky::m_flFogMinStart = C_EnvSky[PROTECT("m_flFogMinStart")];
                        C_EnvSky::m_flFogMinEnd = C_EnvSky[PROTECT("m_flFogMinEnd")];
                        C_EnvSky::m_flFogMaxStart = C_EnvSky[PROTECT("m_flFogMaxStart")];
                        C_EnvSky::m_flFogMaxEnd = C_EnvSky[PROTECT("m_flFogMaxEnd")];
                        C_EnvSky::m_bEnabled = C_EnvSky[PROTECT("m_bEnabled")];
                    }
                    
                    if (classes.contains(PROTECT("C_PostProcessingVolume")))
                    {
                        auto& C_PostProcessingVolume = classes[PROTECT("C_PostProcessingVolume")][PROTECT("fields")];
                        C_PostProcessingVolume::m_hPostSettings = C_PostProcessingVolume[PROTECT("m_hPostSettings")];
                        C_PostProcessingVolume::m_flFadeDuration = C_PostProcessingVolume[PROTECT("m_flFadeDuration")];
                        C_PostProcessingVolume::m_flMinLogExposure = C_PostProcessingVolume[PROTECT("m_flMinLogExposure")];
                        C_PostProcessingVolume::m_flMaxLogExposure = C_PostProcessingVolume[PROTECT("m_flMaxLogExposure")];
                        C_PostProcessingVolume::m_flMinExposure = C_PostProcessingVolume[PROTECT("m_flMinExposure")];
                        C_PostProcessingVolume::m_flMaxExposure = C_PostProcessingVolume[PROTECT("m_flMaxExposure")];
                        C_PostProcessingVolume::m_flExposureCompensation = C_PostProcessingVolume[PROTECT("m_flExposureCompensation")];
                        C_PostProcessingVolume::m_flExposureFadeSpeedUp = C_PostProcessingVolume[PROTECT("m_flExposureFadeSpeedUp")];
                        C_PostProcessingVolume::m_flExposureFadeSpeedDown = C_PostProcessingVolume[PROTECT("m_flExposureFadeSpeedDown")];
                        C_PostProcessingVolume::m_flTonemapEVSmoothingRange = C_PostProcessingVolume[PROTECT("m_flTonemapEVSmoothingRange")];
                        C_PostProcessingVolume::m_bMaster = C_PostProcessingVolume[PROTECT("m_bMaster")];
                        C_PostProcessingVolume::m_bExposureControl = C_PostProcessingVolume[PROTECT("m_bExposureControl")];
                        C_PostProcessingVolume::m_flRate = C_PostProcessingVolume[PROTECT("m_flRate")];
                        C_PostProcessingVolume::m_flTonemapPercentTarget = C_PostProcessingVolume[PROTECT("m_flTonemapPercentTarget")];
                        C_PostProcessingVolume::m_flTonemapPercentBrightPixels = C_PostProcessingVolume[PROTECT("m_flTonemapPercentBrightPixels")];
                        C_PostProcessingVolume::m_flTonemapMinAvgLum = C_PostProcessingVolume[PROTECT("m_flTonemapMinAvgLum")];
                    }
                }
            }
            else if (file == PROTECT("buttons.json"))
            {
                /* Offsets::attack = Client["attack"];
                 Offsets::attack2 = Client["attack2"];*/
                 Offsets::m_iJump = Client[PROTECT("jump")];
            }
        }

        std::cout << PROTECT(" [NoSkill.cc] Offsets successfully updated\n") << '\n';
        return true;
    }
};
