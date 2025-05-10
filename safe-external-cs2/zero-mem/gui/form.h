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

    std::string license_path = xorstr_("bin/License");

    char username_buffer[64] = { 0 };
    char password_buffer[64] = { 0 };
    char key_buffer[512] = { 0 };

    std::string logs = xorstr_("");

    bool Exists() {
        if (std::filesystem::exists(this->license_path)) {
            std::string uname = ReadFromJson(this->license_path, xorstr_("username"));
            std::string upass = ReadFromJson(this->license_path, xorstr_("password"));

            if (uname.empty() && upass.empty())
                return false;
        }

        return true;
    }

    void ReadData() {
        if (_FLAGS_::m_bRememberME) {
            if (fs::exists(this->license_path)) {
                std::string uname = ReadFromJson(this->license_path, xorstr_("username"));
                std::string upass = ReadFromJson(this->license_path, xorstr_("password"));

                strncpy_s(username_buffer, uname.c_str(), sizeof(username_buffer) - 1);
                strncpy_s(password_buffer, upass.c_str(), sizeof(password_buffer) - 1);
            }
        }
    }

    bool RunForm()
    {
        uic.SetStyles();
        ImGui::SetNextWindowSize(ImVec2(450, 420));
        if (ImGui::Begin(xorstr_("NoSkill.cc | Loader"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings)) {
            ImGui::PushFont(RES_LOADER::FONTS::PANAROMA_UI_FONT);
            uic.SetLogo((ImTextureID)RES_LOADER::IMAGES::NO_SKILL_CC_LOGO, ImVec2(200, 50), 30.0f);
            uic.DrawBorder(ImGui::GetWindowPos(), ImGui::GetWindowSize(), 2.0f, 2.0f, 255.0f);

            ImVec2 windowSize = ImGui::GetWindowSize();
            float contentWidth = 250.0f;
            float centerX = windowSize.x * 0.5f - contentWidth * 0.5f;

            ImVec2 buttonSize = ImVec2(125, 35);
            ImVec2 buttonSpacing = ImVec2(10, 0);
            float totalButtonsWidth = buttonSize.x * 2 + buttonSpacing.x;
            float startX = (windowSize.x - totalButtonsWidth) * 0.5f;

            ImGui::SetCursorPos(ImVec2(startX, 100));
            if (ImGui::Button(xorstr_("Login"), buttonSize)) {
                form_index = 0;
                logs.clear();
            }

            ImGui::SameLine();
            ImGui::SetCursorPosX(startX + buttonSize.x + buttonSpacing.x);
            if (ImGui::Button(xorstr_("Register"), buttonSize)) {
                form_index = 1;
                logs.clear();
            }

            ImGui::SetCursorPos(ImVec2(centerX, 160));
            ImGui::PushItemWidth(contentWidth);
            uic.InputBoxWithPlaceholder(xorstr_("##Username"), xorstr_("Username"), username_buffer, IM_ARRAYSIZE(username_buffer), (this->show_username ? 0 : ImGuiInputTextFlags_Password));
            ImGui::SameLine();
            ImGui::PushID(1);
            uic.Checkbox("##", &this->show_username);
            ImGui::PopID();

            ImGui::SetCursorPos(ImVec2(centerX, ImGui::GetCursorPosY() + 10));
            uic.InputBoxWithPlaceholder(xorstr_("##Password"), xorstr_("Password"), password_buffer, IM_ARRAYSIZE(password_buffer), (this->show_password ? 0 : ImGuiInputTextFlags_Password));
            ImGui::SameLine();
            uic.Checkbox("##", &this->show_password);

            if (form_index == 0) { // login form
                ImGui::SetCursorPos(ImVec2(centerX, ImGui::GetCursorPosY() + 15));
                uic.Checkbox("Remember me", &_FLAGS_::m_bRememberME);
                ImGui::SetCursorPos(ImVec2(centerX, ImGui::GetCursorPosY() + 20));
                if (ImGui::Button(xorstr_("Login!"), ImVec2(contentWidth, 35)))
                {
                    KAA.login(username_buffer, password_buffer);
                    if (!KAA.response.success)
                    {
                        //std::remove(this->key_file_path.c_str());
                        logs = KAA.response.message;
                        if (logs == xorstr_("Invalid username")) {
                            logs = xorstr_("Invalid username or password");
                        }
                        if (!logs.empty()) {
                            uic.CenterText(logs.c_str(), 50.0f, ImColor(255, 255, 255));
                        }
                        ImGui::PopFont();
                        ImGui::End();
                        return false;
                    }
                    else
                    {
                        WriteToJson(this->license_path, xorstr_("username"), username_buffer, true, xorstr_("password"), password_buffer);
                        logs = xorstr_("Logging-in!");
                        if (!logs.empty()) {
                            uic.CenterText(logs.c_str(), 50.0f, ImColor(255, 255, 255));
                        }
                        ImGui::PopFont();
                        ImGui::End();
                        return true;
                    }
                }
            }
            else if (form_index == 1) { // register form
                ImGui::SetCursorPos(ImVec2(centerX, ImGui::GetCursorPosY() + 10));
                uic.InputBoxWithPlaceholder(xorstr_("##Key"), xorstr_("Key"), key_buffer, IM_ARRAYSIZE(key_buffer), (this->show_key ? 0 : ImGuiInputTextFlags_Password));
                ImGui::SameLine();
                ImGui::PushID(2);
                uic.Checkbox("##", &this->show_key);
                ImGui::PopID();
                ImGui::SetCursorPos(ImVec2(centerX, ImGui::GetCursorPosY() + 15));
                if (ImGui::Button(xorstr_("Register!"), ImVec2(contentWidth, 35)))
                {
                    KAA.regstr(username_buffer, password_buffer, key_buffer);

                    if (!KAA.response.success)
                    {
                        std::remove(this->license_path.c_str());
                        logs = KAA.response.message;
                        ImGui::PopFont();
                        ImGui::End();
                        return false;
                    }
                    else
                    {
                        logs = xorstr_("Successfully Registered! Now Login!");
                        WriteToJson(this->license_path, xorstr_("username"), username_buffer, true, xorstr_("password"), password_buffer);
                    }
                }
            }

            if (!logs.empty()) {
                uic.CenterText(logs.c_str(), 50.0f, ImColor(255, 255, 255));
            }

            ImGui::PopFont();
            ImGui::End();
        }

        return false;
    }
};
