#pragma once
#include <globals/imports.h>
#include <globals/defs.h>

namespace Renderer
{
	inline bool m_bIsRunning = true;
	inline bool m_bForeGroundCheck = true;

	class DIRECTX11
	{
	private:
		const char* Title;
		int Width, Height;

		HWND window;
		WNDCLASSEX wc;

		ID3D11Device* device;
		ID3D11DeviceContext* device_context;
		IDXGISwapChain* swap_chain;
		ID3D11RenderTargetView* render_targetview;

		LARGE_INTEGER frequency;
		LARGE_INTEGER startTime;

		// creation of device, window, and ImGui.
		bool CreateDevice();
		void CreateOverlay();
		bool InitializeImGui();

		// destroying of device, window and ImGui.
		void DestroyDevice();
		void DestroyOverlay();
		void DestroyImGui();

	public:
		DIRECTX11(const char* window_title, int width, int height) : Title(window_title), Width(width), Height(height) {}



		// i'm using this for the menu specifically, but you could render ESP and shit like that in here if you wanted to.
		// as long as you're calling ImGui::GetBackgroundDrawList() between Start and End render you're fine to do what you want :)

		// small helper functions for the SetForeground function
		bool IsWindowInForeground(HWND window) { return GetForegroundWindow() == window; }
		bool BringToForeground(HWND window) { return SetForegroundWindow(window); }

		// sets the window to the foreground
		void SetForeground(HWND window);
		void StartTimer();

	public:
		void Initialize() {
			CreateOverlay();
			CreateDevice();
			InitializeImGui();
			StartTimer();
		}

		void Shutdown() {
			DestroyDevice();
			DestroyOverlay();
			DestroyImGui();
		}

		// for use inside of your main loop to render.
		void StartRender();
		void EndRender();
		float GetElapsedTime();

		ID3D11Device* GetDevice()& {
			return this->device;
		}

		HWND GetWindow()& {
			return this->window;
		}

		bool& IsRunning() {
			return Renderer::m_bIsRunning;
		}
	};
}