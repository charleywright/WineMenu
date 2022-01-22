#pragma once
#include <memory>
#include <dxgi.h>

namespace rage
{
	struct scrNativeRegistration;
}

namespace Wine
{
	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const &) = delete;
		GameVariables(GameVariables &&) = delete;
		GameVariables &operator=(GameVariables const &) = delete;
		GameVariables &operator=(GameVariables &&) = delete;

		HWND m_GameWindow;
		char *m_GameBuild;
		std::uint32_t *m_GameState;
		std::uint32_t *m_FrameCount;
		std::uint32_t *m_WorldPtr;
		IDXGISwapChain *m_Swapchain;
		rage::scrNativeRegistration **m_NativeRegistrations;
		std::uint64_t **m_GlobalBase;
	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const &) = delete;
		GameFunctions(GameFunctions &&) = delete;
		GameFunctions &operator=(GameFunctions const &) = delete;
		GameFunctions &operator=(GameFunctions &&) = delete;

		using IsDlcPresent = bool(std::uint32_t hash);
		IsDlcPresent *m_IsDlcPresent;

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc *m_WndProc;

		using GetEventData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t *args, std::uint32_t argCount);
		GetEventData *m_GetEventData;

		using GetLabelText = const char *(void *unk, const char *label);
		GetLabelText *m_GetLabelText;

		using SetCursorPos = bool(int x, int y);
		SetCursorPos *m_SetCursorPos;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}
