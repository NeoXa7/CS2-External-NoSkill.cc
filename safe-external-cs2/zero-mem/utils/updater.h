#pragma once
#include <globals/imports.h>
#include <globals/offsets.h>
#include <libs/json.hpp>
#include <libs/xorstr.h>

using json = nlohmann::json;
namespace fs = std::filesystem;

#ifdef _WIN32
inline std::time_t timegm(std::tm* tm) {
    return _mkgmtime(tm);
}
#endif

class Updater {
private:
    const std::string a2x_dumper_api = xorstr_("https://api.github.com/repos/a2x/cs2-dumper/commits");

    const std::vector<std::pair<std::string, std::string>> files_to_update = {
        {"https://github.com/a2x/cs2-dumper/raw/main/output/offsets.json", xorstr_("offsets.json")},
        {"https://github.com/a2x/cs2-dumper/raw/main/output/client_dll.json", xorstr_("client_dll.json")},
        {"https://github.com/a2x/cs2-dumper/raw/main/output/buttons.json", xorstr_("buttons.json")},
    };

    std::vector<std::string> Files = { xorstr_("offsets.json"), xorstr_("client_dll.json"), xorstr_("buttons.json") };

    bool FileExists(const std::string& path) const {
        return fs::exists(path) && fs::is_regular_file(path);
    }

    bool DownloadFile(const std::string& url, const std::string& local_path) {
        HINTERNET hInternet = InternetOpen(xorstr_("Updater"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
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
        HINTERNET hInternet = InternetOpenA(xorstr_("Updater"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
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

            std::string commit_date = data[0][xorstr_("commit")][xorstr_("author")][xorstr_("date")];
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
            std::cerr << xorstr_(" [NoSkill.cc] Failed to open ") << fileName << "." << std::endl;
            return false;
        }

        std::string fileContent((std::istreambuf_iterator<char>(inFile)),
            std::istreambuf_iterator<char>());
        inFile.close();

        try {
            outJson = json::parse(fileContent);
        }
        catch (const json::parse_error& e) {
            std::cerr << xorstr_(" [NoSkill.cc] JSON parse error in ") << fileName
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
            std::cout << xorstr_(" [NoSkill.cc] Failed to fetch latest commit info.\n");
            std::cout << xorstr_(" [NoSkill.cc] Try downloading manually.\n");
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
            std::cout << xorstr_(" [NoSkill.cc] Failed to fetch latest commit info.\n");
            std::cout << xorstr_(" [NoSkill.cc] Try downloading manually.\n");
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
                std::cout << xorstr_(" [NoSkill.cc] Updated : ") << filename << "\n";
            }
            else {
                std::cout << xorstr_(" [NoSkill.cc] Failed to update/download: ") << filename << "\n";
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
                std::cerr << xorstr_(" [NoSkill.cc] ") << filePath << xorstr_(" not found.") << std::endl;
                continue;
            }

            if (!ParseJsonFromFile(filePath, Data)) {
                std::cout << xorstr_("  [NoSkill.cc] Failed to reload Offsets! (Failed to parse Json File)\n") << '\n';
                return false;
            }

            const auto& Client = Data[xorstr_("client.dll")];
            const auto& Matchmaking = Data[xorstr_("matchmaking.dll")];
            const auto& Engine2 = Data[xorstr_("engine2.dll")];

            if (file == xorstr_("offsets.json"))
            {
                Offsets::dwEntityList = Client[xorstr_("dwEntityList")];
                Offsets::dwLocalPlayerPawn = Client[xorstr_("dwLocalPlayerPawn")];
                Offsets::dwLocalPlayerController = Client[xorstr_("dwLocalPlayerController")];
                Offsets::dwViewAngles = Client[xorstr_("dwViewAngles")];
                Offsets::dwViewMatrix = Client[xorstr_("dwViewMatrix")];
                Offsets::dwSensitivity = Client[xorstr_("dwSensitivity")];
                Offsets::dwSensitivity_sensitivity = Client[xorstr_("dwSensitivity_sensitivity")];
                /*Offsets::dwGameRules = Client["dwGameRules"];
                Offsets::dwPlantedC4 = Client["dwPlantedC4"];
                Offsets::dwGlobalVars = Client["dwGlobalVars"];
                Offsets::dwWeaponC4 = Client["dwWeaponC4"];
                Offsets::dwGameTypes = Matchmaking["dwGameTypes"];
                Offsets::dwGameTypes_mapName = Matchmaking["dwGameTypes_mapName"];
                Offsets::dwBuildNumber = Engine2["dwBuildNumber"];*/
            }
            else if (file == xorstr_("client_dll.json"))
            {
                json client = Data.contains(xorstr_("client.dll"));

                if (Data.contains(xorstr_("client.dll")) && Data[xorstr_("client.dll")].contains(xorstr_("classes"))) {
                    auto& classes = Data[xorstr_("client.dll")][xorstr_("classes")];

                    if (classes.contains("C_CSPlayerPawn")) {
                        auto& C_CSPlayerPawn = classes[xorstr_("C_CSPlayerPawn")][xorstr_("fields")];
                        Offsets::m_ArmorValue = C_CSPlayerPawn[xorstr_("m_ArmorValue")];
                        Offsets::m_iShotsFired = C_CSPlayerPawn[xorstr_("m_iShotsFired")];
                        Offsets::m_aimPunchAngle = C_CSPlayerPawn[xorstr_("m_aimPunchAngle")];
                        Offsets::m_bIsScoped = C_CSPlayerPawn[xorstr_("m_bIsScoped")];
                        Offsets::m_pBulletServices = C_CSPlayerPawn[xorstr_("m_pBulletServices")];
                        Offsets::m_aimPunchCache = C_CSPlayerPawn[xorstr_("m_aimPunchCache")];
                    }

                    if (classes.contains(xorstr_("C_BaseEntity"))) {
                        auto& C_BaseEntity = classes[xorstr_("C_BaseEntity")][xorstr_("fields")];
                        Offsets::m_iTeamNum = C_BaseEntity[xorstr_("m_iTeamNum")];
                        Offsets::m_iHealth = C_BaseEntity[xorstr_("m_iHealth")];
                        Offsets::m_pGameSceneNode = C_BaseEntity[xorstr_("m_pGameSceneNode")];
                        Offsets::m_fFlags = C_BaseEntity[xorstr_("m_fFlags")];
                        Offsets::m_vecAbsVelocity = C_BaseEntity[xorstr_("m_vecAbsVelocity")];
                    }

                    if (classes.contains(xorstr_("CCSPlayerController"))) {
                        auto& CCSPlayerController = classes[xorstr_("CCSPlayerController")][xorstr_("fields")];
                        Offsets::m_hPlayerPawn = CCSPlayerController[xorstr_("m_hPlayerPawn")];
                        Offsets::m_sSanitizedPlayerName = CCSPlayerController[xorstr_("m_sSanitizedPlayerName")];
                        Offsets::m_iPing = CCSPlayerController[xorstr_("m_iPing")];
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
                        auto& C_BasePlayerPawn = classes[xorstr_("C_BasePlayerPawn")][xorstr_("fields")];
                        Offsets::m_vOldOrigin = C_BasePlayerPawn[xorstr_("m_vOldOrigin")];
                        Offsets::m_pCameraServices = C_BasePlayerPawn[xorstr_("m_pCameraServices")];
                    }

                    if (classes.contains("C_BaseModelEntity")) {
                        auto& C_BaseModelEntity = classes[xorstr_("C_BaseModelEntity")][xorstr_("fields")];
                        Offsets::m_vecViewOffset = C_BaseModelEntity[xorstr_("m_vecViewOffset")];
                    }

                    if (classes.contains(xorstr_("C_CSGameRules"))) {
                        auto& C_CSGameRules = classes[xorstr_("C_CSGameRules")][xorstr_("fields")];
                        //Offsets::m_bBombPlanted = C_CSGameRules["m_bBombPlanted"];
                        //Offsets::m_bBombDropped = C_CSGameRules["m_bBombDropped"];
                        //Offsets::m_bWarmupPeriod = C_CSGameRules["m_bWarmupPeriod"];
                        //Offsets::m_bCTTimeOutActive = C_CSGameRules["m_bCTTimeOutActive"];
                        //Offsets::m_bTerroristTimeOutActive = C_CSGameRules["m_bTerroristTimeOutActive"];
                    }


                    if (classes.contains("C_PlantedC4")) {
                        auto& C_PlantedC4 = classes[xorstr_("C_PlantedC4")][xorstr_("fields")];
                        /*Offsets::m_nBombSite = C_PlantedC4["m_nBombSite"];
                        Offsets::m_bHasExploded = C_PlantedC4["m_bHasExploded"];
                        Offsets::m_bBeingDefused = C_PlantedC4["m_bBeingDefused"];
                        Offsets::m_flDefuseLength = C_PlantedC4["m_flDefuseLength"];*/
                    }

                    if (classes.contains("CGameSceneNode")) {
                        auto& CGameSceneNode = classes[xorstr_("CGameSceneNode")][xorstr_("fields")];
                        // Offsets::m_vecAbsOrigin = CGameSceneNode[xorstr_("m_vecAbsOrigin")];
                        Offsets::m_bDormant = CGameSceneNode[xorstr_("m_bDormant")];
                    }

                    if (classes.contains(xorstr_("CPlayer_MovementServices_Humanoid")))
                    {
                        auto& CPlayer_MovementServices_Humanoid = classes[xorstr_("CPlayer_MovementServices_Humanoid")][xorstr_("fields")];
                        Offsets::m_groundNormal = CPlayer_MovementServices_Humanoid[xorstr_("m_groundNormal")];
                    }

                    if (classes.contains(xorstr_("CCSPlayerBase_CameraServices")))
                    {
                        auto& CCSPlayerBase_CameraServices = classes[xorstr_("CCSPlayerBase_CameraServices")][xorstr_("fields")];
                        Offsets::m_iFOV = CCSPlayerBase_CameraServices[xorstr_("m_iFOV")];
                    }

                    if (classes.contains(xorstr_("CEntityIdentity ")))
                    {
                        auto& CCSPlayerBase_CameraServices = classes[xorstr_("CEntityIdentity ")][xorstr_("fields")];
                        Offsets::m_designerName = CCSPlayerBase_CameraServices[xorstr_("m_designerName")];
                    }
                    
                    if (classes.contains(xorstr_("CEntityInstance")))
                    {
                        auto& CCSPlayerBase_CameraServices = classes[xorstr_("CEntityInstance")][xorstr_("fields")];
                        Offsets::m_pEntity = CCSPlayerBase_CameraServices[xorstr_("m_pEntity")];
                    }
                }
            }
            else if (file == xorstr_("buttons.json"))
            {
                /* Offsets::attack = Client["attack"];
                 Offsets::attack2 = Client["attack2"];*/
                 Offsets::m_iJump = Client[xorstr_("jump")];
            }
        }

        std::cout << xorstr_(" [NoSkill.cc] Offsets successfully updated\n") << '\n';
        return true;
    }
};
