#pragma once
#include <globals/defs.h>
#include <globals/imports.h>
#include <utils/draw.h>

namespace MISC {
	
}

namespace CROSSHAIR {
	inline bool m_bEnableCrosshair = true;
	inline float CrossHairSize = 10.0f;
	inline ImColor CrossHairColor = ImColor(0, 255, 0);

	void DRAW() {
		if (m_bEnableCrosshair) {
			Vector2 SightPos = Vector2(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
			Utils::Draw::Line({ SightPos.x - CrossHairSize,SightPos.y }, { SightPos.x + CrossHairSize,SightPos.y }, 1, CrossHairColor);
			Utils::Draw::Line({ SightPos.x,SightPos.y - CrossHairSize }, { SightPos.x ,SightPos.y + CrossHairSize }, 1, CrossHairColor);
			Utils::Draw::Line({ SightPos.x,SightPos.y - CROSSHAIR::CrossHairSize }, { SightPos.x ,SightPos.y + CROSSHAIR::CrossHairSize }, 1, CROSSHAIR::CrossHairColor);
			Utils::Draw::Line({ SightPos.x,SightPos.y - CROSSHAIR::CrossHairSize }, { SightPos.x ,SightPos.y + CROSSHAIR::CrossHairSize }, 1, CROSSHAIR::CrossHairColor);
		}
	}
}