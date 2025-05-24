#pragma once
#include <globals/imports.h>
#include <globals/defs.h>
#include <utils/console.h>
#include <utils/memory.h>
#include <utils/resource_loader.h>
#include <sdk/sdk.h>
#include <renderer/directx/directX11.h>
#include <globals/utils.h>
#include <gui/menu.h>
#include <KDZero/kprocess.h>
#include <gui/settings_manager.h>
#include <key_auth_system.h>
#include <gui/form.h>
#include <sdk/defs.h>
#include <cheats/_import.h>


/*	
	MY C++ CODE IS EASIER TO UNDERSTAND IF YOU KNOW ENGLISH ~
	 - Developer

	 DO NOT CHANGE THE CODE BELOW OR YOU WILL ENCOUNTER AN POSSIBLE BLUE SCREEN OF DEATH 
*/


class MAIN {
public:
	MAIN() {}
	~MAIN() {}

	MAIN(const MAIN&) = delete;
	MAIN& operator=(const MAIN&) = delete;

private:
	Process& m_ProcessManager = Instance<Process>::Get();
	KDZERO_PROCESS_MANAGER& m_KernelProcessManager = Instance<KDZERO_PROCESS_MANAGER>::Get();
	Form& m_Form = Instance<Form>::Get();

	void SetupConsole() {
		Console::CreateConsoleWindow((PROTECT("NoSkill.cc - Compiled at :  ") + compilation_date + " " + compilation_time).c_str());
		Console::SetConsoleTextColor(RED);
		std::cout << R"(  _  _  ___    ___ _  _____ _    _      ___ ___ 
 | \| |/ _ \  / __| |/ /_ _| |  | |    / __/ __|
 | .` | (_) | \__ \ ' < | || |__| |__ | (_| (__ 
 |_|\_|\___/  |___/_|\_\___|____|____(_)___\___|
                                                )" << std::endl;

		std::cout << PROTECT(" [NoSkill.cc] Note: This cheat was developed for 'Windows 10' and may not work on other versions of 'Windows'.\n\n");

		Console::SetConsoleTextColor(YELLOW);

		std::cout << PROTECT(" [NoSkill.cc] Connecting...\n");
		std::cout << PROTECT(" [NoSkill.cc] Connected\n");
		std::cout << PROTECT("\n");
	}

	void MainLoop() {
		Renderer::DIRECTX11 DX11(PROTECT("NoSkill.cc"), SCREEN_WIDTH, SCREEN_HEIGHT);
		this->SetupConsole();

		// EntityList loop thread
		std::thread LoopThread(&CSourceEngine::IterateEntities, &Instance<CSourceEngine>::Get());
		LoopThread.detach();

		// TriggerBot thread
		std::thread TriggerThread(TRIGGER_BOT::RUN);
		TriggerThread.detach();
		
		std::thread GameThread(&MEMORY::RUN);
		GameThread.detach();

		DX11.Initialize();
		RES_LOADER::Device = DX11.GetDevice();
		RES_LOADER::LoadFonts();
		RES_LOADER::LoadImages();

		KAA.init();
		if (!KAA.response.success)
		{
			Console::SetConsoleTextColor(RED);
			std::cout << PROTECT(" [NoSkill.cc] Status: ") << KAA.response.message;
			std::cin.get();
		}

		// Login Loop
		bool loggedIn = false;

		m_Form.ReadData();

		while (DX11.IsRunning() && !loggedIn) {
			DX11.StartRender();

			if (GetAsyncKeyState(DEFAULT_PANIC_KEY_DESTROY_PROGRAM) & 1) {
				Console::DestroyConsoleWindow();
				EXIT;
			}

			loggedIn = m_Form.RunForm();

			DX11.EndRender();
		}

		settings.LoadSettings();

		std::thread run(checkAuthenticated, ownerid);
		std::thread check(sessionStatus);

		if (!m_Form.Exists())
			return;

		bool is_update_needed = false;

		if (_FLAGS_::m_bAutomaticUpdate) {
			if (Instance<Updater>::Get().NeedsUpdate()) {
				std::cout << PROTECT("[NoSkill.cc] Update required, updating cheat") << '\n';
				if (Instance<Updater>::Get().DownloadOffsets()) {
					Instance<Updater>::Get().UpdateOffsets();
				}
			}
			else { 
				Instance<Updater>::Get().UpdateOffsets();
			}
		}
		else {
			if (Instance<Updater>::Get().NeedsUpdate()) {
				is_update_needed = true;
			}
		}

		// Main thread
		while (DX11.IsRunning()) {
			DX11.StartRender();

			if (Instance<Menu>::Get().m_bVisible)
			{
				LONG_PTR exStyle = GetWindowLongPtrA(DX11.GetWindow(), GWL_EXSTYLE);
				exStyle &= ~WS_EX_TRANSPARENT; // remove WS_EX_TRANSPARENT
				exStyle &= ~WS_EX_LAYERED;     // remove WS_EX_LAYERED
				exStyle |= WS_EX_TOOLWINDOW;   // ensure WS_EX_TOOLWINDOW is set
				exStyle |= WS_EX_TOPMOST;   // ensure WS_EX_TOPMOST is set
				SetWindowLongPtrA(DX11.GetWindow(), GWL_EXSTYLE, exStyle);

				SetWindowPos(DX11.GetWindow(), HWND_TOPMOST, 0, 0, 0, 0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}
			else
			{
				LONG_PTR exStyle = GetWindowLongPtrA(DX11.GetWindow(), GWL_EXSTYLE);
				exStyle |= WS_EX_TRANSPARENT;  // add WS_EX_TRANSPARENT
				exStyle |= WS_EX_LAYERED;      // add WS_EX_LAYERED
				exStyle |= WS_EX_TOOLWINDOW;   // keep WS_EX_TOOLWINDOW
				exStyle |= WS_EX_TOPMOST;   // keep WS_EX_TOPMOST
				SetWindowLongPtrA(DX11.GetWindow(), GWL_EXSTYLE, exStyle);
			}

			if (is_update_needed && _FLAGS_::m_bShowText) {
				Utils::Draw::TextWithStroke("Update Required! update in settings tab!", Vector2(SCREEN_CENTER_X, SCREEN_CENTER_Y));
			}

			if (GetAsyncKeyState(_FLAGS_::m_iVisibilityToggleKey) & 1) {
				Instance<Menu>::Get().m_bVisible = !Instance<Menu>::Get().m_bVisible;
				if (Instance<Menu>::Get().m_bVisible && Renderer::m_bForeGroundCheck) {
					Renderer::m_bForeGroundCheck = false;
				}
				else {
					Renderer::m_bForeGroundCheck = true;
				}
			}

			if (GetAsyncKeyState(_FLAGS_::m_iEndProgramKey) & 1) {
				Console::DestroyConsoleWindow();
				EXIT;
			}

			if (GetAsyncKeyState(_FLAGS_::m_iLoadUnloadCheatsKey) & 1) {
				_FLAGS_::m_bEnableCheats = !_FLAGS_::m_bEnableCheats;
			}

			if (KAA.user_data.hwid.empty() || KAA.user_data.ip.empty() || KAA.user_data.username.empty()) {
				exit(0);
			}

			SourceEngine.UpdateEngine();

			std::lock_guard<std::mutex> lock(SourceEngine.GetEntityListMutex());
			auto& list = SourceEngine.GetEntityListRef();

			if (!m_Form.Exists())
				return;

			if (IsDebuggerPresent()) {
				exit(0);
			}

			for (auto& entities : list) {
				if (_FLAGS_::m_bEnableCheats) {
					ESP::RUN(entities);
				}
			}

			if (_FLAGS_::m_bEnableCheats) {
				SRCS::RUN();
				AIMBOT::RUN(list);
				HITSERVICE::HIT_SOUND();
				CROSSHAIR::DRAW();
			}

			//Instance<Menu>::Get().RenderList(list);

			if (Instance<Menu>::Get().m_bVisible) {
				Instance<Menu>::Get().Render();
			}

			DX11.EndRender();
		}
		DX11.Shutdown();
	}

public:
	void Start() {
		if (IsDebuggerPresent()) {
			exit(0);
		}

		/*SourceEngine.ProcessID = m_KernelProcessManager.GetProcessID("cs2.exe");

		if (!SourceEngine.ProcessID) {
			LI_FN(printf).get()(PROTECT(" [NoSkill.cc] Failed to get Process ID of Process (", m_SourceEngine.ProcessName, ") : ", m_SourceEngine.ProcessID, '\n'));
			std::cin.get();
		}
		else
		{
			SourceEngine.ClientDll = m_KernelProcessManager.GetModuleBaseAddress(PROTECT("client.dll"), SourceEngine.ProcessID);

			if (!SourceEngine.ClientDll) {
				LI_FN(printf).get()(PROTECT(" [NoSkill.cc] Failed to read from driver (KDZero.sys)\n"));
				LI_FN(printf).get()(PROTECT(" [NoSkill.cc] Make sure to map (KDZero.sys) using kd-mapper (provided) or any other tool first and then try again!\n"));
				std::cin.get();
			}
			else { 
				if (IsDebuggerPresent()) {
					exit(0);
				}

				this->MainLoop();
			}
		}

		*/

		this->MainLoop();

		std::cin.get();
	}
};
