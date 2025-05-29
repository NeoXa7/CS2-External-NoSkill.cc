#include <key_auth_system.h>
#include <gui/custom.h>
#include <utils/resource_loader.h>
#include <libs/xorstr.h>

class Form {  
private:  
    UIComponents& uic = Instance<UIComponents>::Get();

    bool show_username = false;
    bool show_password = false;
    bool show_key = false;
    int form_index = 0;

public:  
    Form() {}
    ~Form() {}

    Form(const Form&) = delete;
    Form& operator=(const Form&) = delete;

    std::string license_path = PROTECT("bin/License");

    char username_buffer[64] = { 0 };
    char password_buffer[64] = { 0 };
    char key_buffer[512] = { 0 };

    std::string logs = PROTECT("");

    bool Exists() {
        if (std::filesystem::exists(this->license_path)) {
            std::string uname = ReadFromJson(this->license_path, PROTECT("username"));
            std::string upass = ReadFromJson(this->license_path, PROTECT("password"));

            if (uname.empty() && upass.empty())
                return false;
        }

        return true;
    }

    void ReadData() {
        if (_FLAGS_::m_bRememberME) {
            if (fs::exists(this->license_path)) {
                std::string uname = ReadFromJson(this->license_path, PROTECT("username"));
                std::string upass = ReadFromJson(this->license_path, PROTECT("password"));

                strncpy_s(username_buffer, uname.c_str(), sizeof(username_buffer) - 1);
                strncpy_s(password_buffer, upass.c_str(), sizeof(password_buffer) - 1);
            }
        }
    }

    bool RunForm()
    {
        uic.SetStyles();
        ImGui::SetNextWindowSize(ImVec2(500, 300));
        if (ImGui::Begin(PROTECT("NoSkill.cc | Loader"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings)) {
            Instance<Particles>::Get().DrawIdleWigglingDots();

            ImGui::PushFont(RES_LOADER::FONTS::RIFIC_BOLD);
            ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + (500 / 2), ImGui::GetCursorPos().y + 100.0f));
            ImGui::Text("NOSKILL.CC");
            ImGui::PopFont();

  
        }

        ImGui::End();
        return false;
    }
};
