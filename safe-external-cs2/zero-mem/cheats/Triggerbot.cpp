#include <pch.h>
#include "Triggerbot.h"

namespace TRIGGER_BOT {
	void RUN() {
		int loops = 0;
		while (true) {
			if (loops > 15) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				if (Instance<Process>::Get().InForeground("Counter-Strike 2") && TRIGGER_BOT::m_bEnableTriggerBot) {
					if (LocalPlayer.IDEntIndex > 0)
					{
						uintptr_t EntityID = mem.Read<uintptr_t>(Instance<CGame>::Get().EntityList + 0x8 * (LocalPlayer.IDEntIndex >> 9) + 0x10);
						uintptr_t Entity = mem.Read<uintptr_t>(EntityID + 120 * (LocalPlayer.IDEntIndex & 0x1FF));

						int EntityTeam = mem.Read<int>(Entity + Offsets::m_iTeamNum);
						int EntityHealth = mem.Read<int>(Entity + Offsets::m_iHealth);


						if (TRIGGER_BOT::m_iCurrentTriggerModeIndex == 0) {
							TRIGGER_BOT::m_imTriggerMode = AUTO;
						}
						else if (TRIGGER_BOT::m_iCurrentTriggerModeIndex == 1) {
							TRIGGER_BOT::m_imTriggerMode = HOLD;
						}

						if (TRIGGER_BOT::m_bEnableTeamCheck == true)
						{
							if (EntityTeam != LocalPlayer.Team && EntityHealth > 0)
							{
								if (TRIGGER_BOT::m_imTriggerMode == HOLD && (GetAsyncKeyState(TRIGGER_BOT::m_iCurrentTriggerKey) & 0x8000)) {
									FireMacro(TRIGGER_BOT::m_flTriggerDelay, TRIGGER_BOT::m_flTriggerFireRate);
								}
								else if (TRIGGER_BOT::m_imTriggerMode == AUTO) {
									FireMacro(TRIGGER_BOT::m_flTriggerDelay, TRIGGER_BOT::m_flTriggerFireRate);
								}
							}
						}
						else if (EntityHealth > 0)
						{
							if (TRIGGER_BOT::m_imTriggerMode == HOLD && (GetAsyncKeyState(TRIGGER_BOT::m_iCurrentTriggerKey) & 0x8000)) {
								FireMacro(TRIGGER_BOT::m_flTriggerDelay, TRIGGER_BOT::m_flTriggerFireRate);
							}
							else if (TRIGGER_BOT::m_imTriggerMode == AUTO) {
								FireMacro(TRIGGER_BOT::m_flTriggerDelay, TRIGGER_BOT::m_flTriggerFireRate);
							}
						}
					}
				}
			}

			loops++;
		}
	}
}