#pragma once
#include <globals/imports.h>
#include <bytes/obs_icon_font_bytes.h>
#include <bytes/font_awesome_bytes.h>
#include <bytes/font_awesome_icons.h>
#include <bytes/noskill.cc_logo_bytes.h>
#include <libs/xorstr.h>


namespace RES_LOADER
{
	inline ID3D11Device* Device = nullptr;

	namespace FONTS {
		inline ImFont* PANAROMA_WEAPONS_ICON_FONT = nullptr;
		inline ImFont* PANAROMA_UI_FONT = nullptr;
		inline ImFont* PANAROMA_UI_BIG_FONT = nullptr;
		inline ImFont* FONT_AWESOME = nullptr;
		inline ImFont* FONT_AWESOME_SIZE_5 = nullptr;
		inline ImFont* RIFIC_BOLD = nullptr;
		inline ImFont* ARIAL_BOLD = nullptr;
	}

	namespace IMAGES {
		inline ID3D11ShaderResourceView* LOGO = nullptr;
		inline ID3D11ShaderResourceView* NO_SKILL_CC_LOGO = nullptr;
		inline ID3D11ShaderResourceView* FISH_STICK = nullptr;
		inline ID3D11ShaderResourceView* ANIME_GIRL_1 = nullptr;
		inline ID3D11ShaderResourceView* ANIME_GIRL_2 = nullptr;
		inline ID3D11ShaderResourceView* ANIME_GIRL_3 = nullptr;
		inline ID3D11ShaderResourceView* TARGET_ICON = nullptr;
		inline ID3D11ShaderResourceView* MOUSE_ICON = nullptr;
		inline ID3D11ShaderResourceView* ARROW_ICON = nullptr;
		inline ID3D11ShaderResourceView* PERSON_ICON = nullptr;
		inline ID3D11ShaderResourceView* GUN_ICON = nullptr;
		inline ID3D11ShaderResourceView* WORLD_ICON = nullptr;
		inline ID3D11ShaderResourceView* EXPLOITS_ICON = nullptr;
		inline ID3D11ShaderResourceView* SCRIPTS_ICON = nullptr;
		inline ID3D11ShaderResourceView* SETTINGS_ICON = nullptr;
		inline ID3D11ShaderResourceView* T_ICON = nullptr;
	}

	inline bool LoadImageByFile(const char* file_path, ID3D11ShaderResourceView** result) {
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		ID3DX11ThreadPump* threadPump = nullptr;

		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
			Device,
			file_path,
			&loadInfo,
			threadPump,
			result,
			nullptr
		);

		return SUCCEEDED(hr);
	}

	inline bool LoadImageByMemory(unsigned char* image, size_t size_of_image, ID3D11ShaderResourceView** result) {
		D3DX11_IMAGE_LOAD_INFO info;
		ID3DX11ThreadPump* thread = nullptr;

		auto hres = D3DX11CreateShaderResourceViewFromMemory(Device, image, size_of_image, &info, thread, result, 0);
		return (hres == S_OK);
	}

	inline void LoadImages() {
		LoadImageByMemory(noskillcc_logo_bytes, sizeof(noskillcc_logo_bytes), &IMAGES::NO_SKILL_CC_LOGO);
		LoadImageByFile("bin/images/skins/Fish-Stick.jpg", &IMAGES::FISH_STICK);
		LoadImageByFile("bin/images/skins/anime-girl-1.jpg", &IMAGES::ANIME_GIRL_1);
		LoadImageByFile("bin/images/skins/anime-girl-2.jpg", &IMAGES::ANIME_GIRL_2);
		LoadImageByFile("bin/images/skins/anime-girl-3.jpg", &IMAGES::ANIME_GIRL_3);
		LoadImageByFile("bin/images/icons/target.png", &IMAGES::TARGET_ICON);
		LoadImageByFile("bin/images/icons/mouse.png", &IMAGES::MOUSE_ICON);
		LoadImageByFile("bin/images/icons/arrow.png", &IMAGES::ARROW_ICON);
		LoadImageByFile("bin/images/icons/person.png", &IMAGES::PERSON_ICON);
		LoadImageByFile("bin/images/icons/gun.png", &IMAGES::GUN_ICON);
		LoadImageByFile("bin/images/icons/world.png", &IMAGES::WORLD_ICON);
		LoadImageByFile("bin/images/icons/danger.png", &IMAGES::EXPLOITS_ICON);
		LoadImageByFile("bin/images/icons/terminal.png", &IMAGES::SCRIPTS_ICON);
		LoadImageByFile("bin/images/icons/settings.png", &IMAGES::SETTINGS_ICON);
		LoadImageByFile("bin/images/icons/T.png", &IMAGES::T_ICON);
	}

	inline void LoadFonts() {
		ImGuiIO& io = ImGui::GetIO();

		io.Fonts->AddFontDefault();

		ImFontConfig weapons_font_config;
		weapons_font_config.MergeMode = false;
		weapons_font_config.PixelSnapH = true;
		weapons_font_config.OversampleH = 3;
		weapons_font_config.OversampleV = 3;

		ImFontConfig font_awesome_config;
		font_awesome_config.MergeMode = true;
		font_awesome_config.PixelSnapH = true;
		font_awesome_config.OversampleH = 3;
		font_awesome_config.OversampleV = 3;

		static const ImWchar icon_ranges[] = { 0xE000, 0xF8FF, 0 };

		FONTS::PANAROMA_WEAPONS_ICON_FONT = io.Fonts->AddFontFromMemoryTTF(ICONS_FONT_BYTES, sizeof(ICONS_FONT_BYTES), 18.0f, &weapons_font_config, icon_ranges);
		FONTS::PANAROMA_UI_FONT = io.Fonts->AddFontFromFileTTF("bin/fonts/notosans-bold.ttf", 15.0f);
		FONTS::PANAROMA_UI_BIG_FONT = io.Fonts->AddFontFromFileTTF("bin/fonts/notosans-bold.ttf", 35.0f);
		FONTS::RIFIC_BOLD = io.Fonts->AddFontFromFileTTF("bin/fonts/RifficFree-Bold.ttf", 25.0f);
		FONTS::ARIAL_BOLD = io.Fonts->AddFontFromFileTTF("bin/fonts/arial_bold.ttf", 35.0f);
		FONTS::FONT_AWESOME = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 15.0f, &font_awesome_config, icon_ranges);
		FONTS::FONT_AWESOME_SIZE_5 = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 5.0f, &font_awesome_config, icon_ranges);
		
		ImGui_ImplDX11_InvalidateDeviceObjects();
		ImGui_ImplDX11_CreateDeviceObjects();
	}
	
	inline ID3D11ShaderResourceView* CreateTextureFromMemory(unsigned char* data, int width, int height) {
		ID3D11Texture2D* texture = nullptr;
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = data;
		initData.SysMemPitch = width * 4;

		HRESULT hr = Device->CreateTexture2D(&desc, &initData, &texture);

		ID3D11ShaderResourceView* textureView = nullptr;
		hr = Device->CreateShaderResourceView(texture, nullptr, &textureView);
		texture->Release();

		return textureView;
	}
};