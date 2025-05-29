#include <pch.h>
#include "directX11.h"
#include <utils/functions.h>
#include <globals/defs.h>

// declaration of the ImGui_ImplWin32_WndProcHandler function
// basically integrates ImGui with the Windows message loop so ImGui can process input and events
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Renderer
{
	LRESULT CALLBACK window_procedure(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// set up ImGui window procedure handler
		if (ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam))
			return true;

		// switch that disables alt application and checks for if the user tries to close the window.
		switch (msg)
		{
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu (imgui uses it in their example :shrug:)
				return 0;
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_CLOSE:
			return 0;
		}

		// define the window procedure
		return DefWindowProc(window, msg, wParam, lParam);
	}

	bool DIRECTX11::CreateDevice()
	{
		// First we setup our swap chain, this basically just holds a bunch of descriptors for the swap chain.
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));

		// set number of back buffers (this is double buffering)
		sd.BufferCount = 2;

		// width + height of buffer, (0 is automatic sizing)
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;

		// set the pixel format
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// get the fps from GetRefreshRate(). If anything fails it just returns 60 anyways.
		sd.BufferDesc.RefreshRate.Numerator = Utils::Functions::GetRefreshRate();
		sd.BufferDesc.RefreshRate.Denominator = 1;

		// allow mode switch (changing display modes)
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// set how the bbuffer will be used
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		sd.OutputWindow = window;

		// setup the multi-sampling
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;

		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// specify what Direct3D feature levels to use
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

		// create device and swap chain
		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0U,
			featureLevelArray,
			2,
			D3D11_SDK_VERSION,
			&sd,
			&swap_chain,
			&device,
			&featureLevel,
			&device_context);

		// if the hardware isn't supported create with WARP (basically just a different renderer)
		if (result == DXGI_ERROR_UNSUPPORTED) {
			result = D3D11CreateDeviceAndSwapChain(
				nullptr,
				D3D_DRIVER_TYPE_WARP,
				nullptr,
				0U,
				featureLevelArray,
				2, D3D11_SDK_VERSION,
				&sd,
				&swap_chain,
				&device,
				&featureLevel,
				&device_context);

			/*printf("[>>] DXGI_ERROR | Created with D3D_DRIVER_TYPE_WARP\n");*/
		}

		// can't do much more, if the hardware still isn't supported just return false.
		if (result != S_OK) {
			printf("[>>] Device Not Okay\n");
			return false;
		}

		// retrieve back_buffer, im defining it here since it isn't being used at any other point in time.
		ID3D11Texture2D* back_buffer{ nullptr };
		swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

		// if back buffer is obtained then we can create render target view and release the back buffer again
		if (back_buffer)
		{
			device->CreateRenderTargetView(back_buffer, nullptr, &render_targetview);
			back_buffer->Release();

			//printf("[>>] Created Device\n");
			return true;
		}

		// if we reach this point then it failed to create the back buffer
		printf("[>>] Failed to create Device\n");
		return false;
	}

	void DIRECTX11::DestroyDevice()
	{
		// release everything that has to do with the device.
		if (device)
		{
			device->Release();
			device_context->Release();
			swap_chain->Release();
			render_targetview->Release();

			printf("[>>] Released Device\n");
		}
		else
			printf("[>>] Device Not Found when Exiting.\n");
	}

	void DIRECTX11::CreateOverlay()
	{
		// holds descriptors for the window, called a WindowClass
		// set up window class
		wc.cbSize = sizeof(wc);
		wc.style = CS_CLASSDC;
		wc.lpfnWndProc = window_procedure;
		wc.hInstance = GetModuleHandleA(0);
		wc.lpszClassName = "ZERO_MEM";

		// register our class
		RegisterClassEx(&wc);

		// create window (the actual one that shows up in your taskbar)
		// WS_EX_TOOLWINDOW hides the new window that shows up in your taskbar and attaches it to any already existing windows instead.
		// (in this case the console)
		window = CreateWindowEx(
			WS_EX_LAYERED,
			wc.lpszClassName,
			this->Title,
			WS_POPUP,
			0,
			0,
			this->Width, // Width
			this->Height, // Height
			NULL,
			NULL,
			wc.hInstance,
			NULL
		);

		if (window == NULL)
			printf("[>>] Failed to create Overlay\n");

		// set overlay window attributes to make the overlay transparent
		SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_COLORKEY);

		// set up the DWM frame extension for client area
		{
			// first we define our RECT structures that hold our client and window area
			RECT client_area{};
			RECT window_area{};

			// get the client and window area
			GetClientRect(window, &client_area);
			GetWindowRect(window, &window_area);

			// calculate the difference between the screen and window coordinates
			POINT diff{};
			ClientToScreen(window, &diff);

			// calculate the margins for DWM frame extension
			const MARGINS margins{
				window_area.left + (diff.x - window_area.left),
				window_area.top + (diff.y - window_area.top),
				client_area.right,
				client_area.bottom
			};

			// then we extend the frame into the client area
			DwmExtendFrameIntoClientArea(window, &margins);
		}

		// show + update overlay
		ShowWindow(window, SW_SHOW);
		UpdateWindow(window);
	}

	void DIRECTX11::DestroyOverlay()
	{
		DestroyWindow(window);
		UnregisterClass(wc.lpszClassName, wc.hInstance);
	}

	bool DIRECTX11::InitializeImGui()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		// Initalize ImGui for the Win32 library
		if (!ImGui_ImplWin32_Init(window)) {
			printf("[>>] Failed ImGui_ImplWin32_Init\n");
			return false;
		}

		// Initalize ImGui for DirectX 11.
		if (!ImGui_ImplDX11_Init(device, device_context)) {
			printf("[>>] Failed ImGui_ImplDX11_Init\n");
			return false;
		}

		return true;
	}

	void DIRECTX11::DestroyImGui()
	{
		// Cleanup ImGui by shutting down DirectX11, the Win32 Platform and Destroying the ImGui context.
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void DIRECTX11::StartRender()
	{
		// handle windows messages
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// begin a new frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void DIRECTX11::EndRender()
	{
		// Render ImGui
		ImGui::Render();

		// Make a color that's clear / transparent
		float color[4]{ 0, 0, 0, 0 };

		// Set the render target and then clear it
		device_context->OMSetRenderTargets(1, &render_targetview, nullptr);
		device_context->ClearRenderTargetView(render_targetview, color);

		// Render ImGui draw data.
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Present rendered frame with V-Sync
		swap_chain->Present(0U, 0U);

		// Present rendered frame without V-Sync
		//swap_chain->Present(0U, 0U);
	}

	void DIRECTX11::SetForeground(HWND window)
	{
		if (!IsWindowInForeground(window))
			BringToForeground(window);
	}

	void DIRECTX11::StartTimer()
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&startTime);
	}

	float DIRECTX11::GetElapsedTime()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		return static_cast<float>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
	}
}