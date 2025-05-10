#pragma once
#include <globals/imports.h>

namespace fs = std::filesystem;

/*
    CLASS IS CALLED "SIMPLE_INI", CAUSE IT STORES DATA IN A INI STRUCTURE
    MUST READ THE COMMENTS BELOW TO UNDERSTAND HOW TO LOAD/SAVE DATA
*/

class SIMPLE_INI {
private:
    // Map structure : SECTION_NAME, KEY_NAME, KEY_VALUE
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _data_map; // all the data is stored in this unordered nested map as a string for reading and writing.
public:
    // Example : S_INI_CreateDirectory("bin/settings/configs/++++++++); 
    void _CreateDirectories(const std::string& path) {
        if (!fs::exists(path)) {
            fs::create_directories(path);
        }
    }

    // Example : S_INI_CreateFile("bin/configs/cheats.YOUR_EXTENSION_NAME")
    void _CreateFile(const std::string& path) {
        if (!fs::exists(path)) {
            std::ofstream file(path);
        }
    }

    // Example : S_INI_WriteDataToFile("bin/configs/cheats.YOUR_EXTENSION_NAME")
    bool _WriteDataToFile(const std::string& path) {
        if (!fs::exists(path)) {
            std::cout << " [SIMPLE_INI] : File does not exists: " << path << '\n';
            return false;
        }

        std::ofstream file(path);
        if (!file.is_open()) {
            std::cout << " [SIMPLE_INI] : Failed to open file [" << path << "] for Writing!" << '\n';
            return false;
        }

        for (auto& sections : _data_map) {
            file << "[" << sections.first << "]" << '\n';
            for (auto& key_value : sections.second) {
                file << "  " << key_value.first << " = " << key_value.second << '\n';
            }
            file << '\n';
        }

        file.close();
        return true;
    }

    // Example : S_INI_WriteDataToFile("bin/configs/cheats.YOUR_EXTENSION_NAME")
    bool _ReadDataFromFile(const std::string& path) {
        if (!fs::exists(path)) {
            std::cout << " [SIMPLE_INI] : File does not exists: " << path << '\n';
            return false;
        }

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cout << " [SIMPLE_INI] : Failed to open file [" << path << "] for Reading!" << '\n';
            return false;
        }

        std::string line;
        std::string section;

        while(std::getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

            if (line.empty() || line[0] == ';' || line[0] == '#')
                continue;

            if (line.front() == '[' && line.back() == ']') {
                section = line.substr(1, line.size() - 2);
            }
            else {
                size_t delimiter_pos = line.find('=');
                if (delimiter_pos != std::string::npos) {
                    std::string key = line.substr(0, delimiter_pos);
                    std::string value = line.substr(delimiter_pos + 1);

                    key.erase(0, key.find_first_not_of(" \t"));
                    key.erase(key.find_last_not_of(" \t") + 1);
                    value.erase(0, value.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);

                    _data_map[section][key] = value;
                }
            }
        }

        return true;
    }

    template <typename T>
    // Example : ini.Store<bool>("VISUALS", "m_bEnablePlayerEsp", ESP::PLAYER::m_bEnablePlayerEsp);
    void Store(const std::string& section, const std::string& key, T& value) {
        std::string value_type = " #";
        if (typeid(value) == typeid(bool)) {
            value_type = " #bool";
        }
        else if (typeid(value) == typeid(float)) {
            value_type = " #float";
        }
        else if (typeid(value) == typeid(int)) {
            value_type = " #int";
        }

        _data_map[section][key] = std::to_string(value) + value_type;
    }

#define COLOR ImColor // change this to your color struct type

    // Example : ini.StoreColor("VISUALS", "m_clBoxFilledColor", ESP::PLAYER::m_clBoxFilledColor);
    void StoreColor(const std::string& section, const std::string& key, COLOR& value) { // edit this func for your color type struct
        char buf[64];
        snprintf(buf, sizeof(buf), "%.3f, %.3f, %.3f, %.3f", value.Value.x, value.Value.y, value.Value.z, value.Value.w);
        std::string comment = " #Vector4 Values";
        _data_map[section][key] = buf + comment;
    }

    // Example : ESP::PLAYER::m_bEnablePlayerEsp = ini.GetBool("VISUALS", "m_bEnablePlayerEsp");
    bool GetBool(const std::string& section, const std::string& key) {
        std::string value = _data_map[section][key];
        size_t comment_pos = value.find('#');
        if (comment_pos != std::string::npos) {
            value = value.substr(0, comment_pos); // keep only the part before #
        }

        // trim spaces
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        return (value == "1");
    }

    // EXAMPLE : ESP::PLAYER::m_clBoxFilledColor = ini.LoadColor("VISUALS", "m_clBoxFilledColor");
    COLOR GetColor(const std::string& section, const std::string& key, COLOR default_color = COLOR(1.0f, 1.0f, 1.0f, 1.0f)) {  // edit this func for your color type struct
        if (_data_map.find(section) == _data_map.end() || _data_map[section].find(key) == _data_map[section].end())
            return default_color;

        std::string value = _data_map[section][key];
        float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;

        if (sscanf_s(value.c_str(), "%f,%f,%f,%f", &r, &g, &b, &a) == 4) {
            return COLOR(r, g, b, a);
        }
        else {
            return default_color;
        }
    }

    // Example: float myValue = ini.GetFloat("AIM", "fSmoothness", 1.0f);
    float GetFloat(const std::string& section, const std::string& key, float default_value = 0.0f) {
        if (_data_map.find(section) == _data_map.end() || _data_map[section].find(key) == _data_map[section].end())
            return default_value;

        std::string value = _data_map[section][key];
        size_t comment_pos = value.find('#');
        if (comment_pos != std::string::npos) {
            value = value.substr(0, comment_pos);
        }

        // trim spaces
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        try {
            return std::stof(value);
        }
        catch (...) {
            return default_value;
        }
    }

    // Example: int myValue = ini.GetFloat("AIM", "iIndex", 1f);
    int GetInt(const std::string& section, const std::string& key, int default_value = 0) {
        if (_data_map.find(section) == _data_map.end() || _data_map[section].find(key) == _data_map[section].end())
            return default_value;

        std::string value = _data_map[section][key];
        size_t comment_pos = value.find('#');
        if (comment_pos != std::string::npos) {
            value = value.substr(0, comment_pos);
        }

        // trim spaces
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        try {
            return std::stof(value);
        }
        catch (...) {
            return default_value;
        }
    }

    // Example : N/A;
    std::string Get(const std::string& section, const std::string& key) {
        return _data_map[section][key];
    }
};