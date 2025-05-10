#pragma once
#include <globals/imports.h>
#include <bytes/obs_icon_font_bytes.h>
#include <bytes/font_awesome_bytes.h>
#include <bytes/font_awesome_icons.h>
#include <bytes/noskill.cc_logo_bytes.h>
#include <libs/xorstr.h>

namespace RES_LOADER
{
	namespace FONTS {
		inline ImFont* PANAROMA_WEAPONS_ICON_FONT = nullptr;
		inline ImFont* PANAROMA_UI_FONT = nullptr;
		inline ImFont* FONT_AWESOME = nullptr;
		inline ImFont* FONT_AWESOME_SIZE_5 = nullptr;
	}

	namespace IMAGES {
		inline ID3D11ShaderResourceView* LOGO = nullptr;
		inline ID3D11ShaderResourceView* NO_SKILL_CC_LOGO = nullptr;
		inline ID3D11ShaderResourceView* FISH_STICK = nullptr;
		inline ID3D11ShaderResourceView* ANIME_GIRL_1 = nullptr;
		inline ID3D11ShaderResourceView* ANIME_GIRL_2 = nullptr;
		inline ID3D11ShaderResourceView* ANIME_GIRL_3 = nullptr;
	}

	inline bool LoadImageByFile(ID3D11Device* device, const char* file_path, ID3D11ShaderResourceView** result) {
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		ID3DX11ThreadPump* threadPump = nullptr;

		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
			device,
			file_path,
			&loadInfo,
			threadPump,
			result,
			nullptr
		);

		return SUCCEEDED(hr);
	}

	inline bool LoadImageByMemory(ID3D11Device* device, unsigned char* image, size_t size_of_image, ID3D11ShaderResourceView** result) {
		D3DX11_IMAGE_LOAD_INFO info;
		ID3DX11ThreadPump* thread = nullptr;

		auto hres = D3DX11CreateShaderResourceViewFromMemory(device, image, size_of_image, &info, thread, result, 0);
		return (hres == S_OK);
	}

	inline void LoadImages(ID3D11Device* device) {
		LoadImageByMemory(device, noskillcc_logo_bytes, sizeof(noskillcc_logo_bytes), &IMAGES::NO_SKILL_CC_LOGO);
		LoadImageByFile(device, "bin/images/skins/Fish-Stick.jpg", &IMAGES::FISH_STICK);
		LoadImageByFile(device, "bin/images/skins/anime-girl-1.jpg", &IMAGES::ANIME_GIRL_1);
		LoadImageByFile(device, "bin/images/skins/anime-girl-2.jpg", &IMAGES::ANIME_GIRL_2);
		LoadImageByFile(device, "bin/images/skins/anime-girl-3.jpg", &IMAGES::ANIME_GIRL_3);
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
		FONTS::FONT_AWESOME = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 15.0f, &font_awesome_config, icon_ranges);
		FONTS::FONT_AWESOME_SIZE_5 = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 5.0f, &font_awesome_config, icon_ranges);
		
		ImGui_ImplDX11_InvalidateDeviceObjects();
		ImGui_ImplDX11_CreateDeviceObjects();
	}
};