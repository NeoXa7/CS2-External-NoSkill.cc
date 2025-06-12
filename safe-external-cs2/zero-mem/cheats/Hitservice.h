#pragma once
#include <sdk/sdk.h>
#include <utils/functions.h>
#include <utils/draw.h>
#include <utils/resource_loader.h>
#include <globals/imports.h>
#include <globals/utils.h>
#include <globals/_flags.h>
#include "esp.h"

namespace HITSERVICE {
	inline std::string sounds_path = std::string(BASE_DIRECTORY) + "\\sounds\\";
	inline std::string file_name = xorstr_("pop.wav");
	inline std::vector<std::string> wav_files;

	inline bool m_bEnableHitsound = true;

	inline int previous_hits = 0;

	void HIT_SOUND() {
		if (previous_hits == 0) {
			previous_hits = LocalPlayer.TotalHits;
			return;
		}

		if (LocalPlayer.TotalHits != previous_hits) {
			if (LocalPlayer.TotalHits == 0 && previous_hits != 0) {

			}
			else {
				if (m_bEnableHitsound) {
					PlaySoundA((sounds_path + file_name).c_str(), NULL, SND_FILENAME | SND_ASYNC);
				}
			}
			previous_hits = LocalPlayer.TotalHits;
		}
	}

	void ScanDirectoryForFile(const char* extension) {
		wav_files.clear();
		if (!std::filesystem::exists(sounds_path)) {
			std::cerr << "Directory does not exist: " << sounds_path << std::endl;
			return;
		}
		try {
			for (const auto& entry : std::filesystem::directory_iterator(sounds_path)) {
				if (entry.is_regular_file() && entry.path().extension() == extension) {
					wav_files.push_back(entry.path().filename().string());
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error scanning directory: " << e.what() << std::endl;
		}
	}
}