#pragma once
#include <Windows.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

struct Screen
{
	int width, height;
	int left, top, right, bottom;
};

class Overlay {
public:
	static UINT g_ResizeWidth;
	static UINT g_ResizeHeight;

	bool Initialize(HINSTANCE hInstance);
	void Render();
	void Shutdown();
	bool IsRunning();

	Screen FindWindowLocation(LPCSTR windowName);

private:
	ID3D11Device* g_pd3dDevice;
	ID3D11DeviceContext* g_pd3dDeviceContext;
	IDXGISwapChain* g_pSwapChain;
	bool g_SwapChainOccluded;
	ID3D11RenderTargetView* g_mainRenderTargetView;

	WNDCLASSEX wc{};
	HWND hWnd;

	bool show_menu = true;

	bool running = true;

	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
};

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);