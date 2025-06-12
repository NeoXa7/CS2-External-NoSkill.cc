#pragma once
#include <globals/defs.h>
#include <globals/imports.h>
#include <utils/draw.h>

namespace MISC {
	
}

namespace CROSSHAIR {
	inline bool m_bEnableCrosshair = true;
	inline float m_flCrossHairSize = 10.0f;
	inline ImColor m_clCrossHairColor = ImColor(0, 255, 0);

	void DRAW() {
		if (m_bEnableCrosshair) {
			Vector2 SightPos = Vector2(static_cast<int>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)) / 2;
			Utils::Draw::Line({ SightPos.x - m_flCrossHairSize,SightPos.y }, { SightPos.x + m_flCrossHairSize,SightPos.y }, 1, m_clCrossHairColor);
			Utils::Draw::Line({ SightPos.x,SightPos.y - m_flCrossHairSize }, { SightPos.x ,SightPos.y + m_flCrossHairSize }, 1, m_clCrossHairColor);
			Utils::Draw::Line({ SightPos.x,SightPos.y - CROSSHAIR::m_flCrossHairSize }, { SightPos.x ,SightPos.y + CROSSHAIR::m_flCrossHairSize }, 1, CROSSHAIR::m_clCrossHairColor);
			Utils::Draw::Line({ SightPos.x,SightPos.y - CROSSHAIR::m_flCrossHairSize }, { SightPos.x ,SightPos.y + CROSSHAIR::m_flCrossHairSize }, 1, CROSSHAIR::m_clCrossHairColor);
		}
	}
}