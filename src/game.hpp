#include <memory>

#pragma once

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
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		HWND m_GameWindow;
		char* m_GameBuild;
		std::uint32_t* m_GameState;
		std::uint32_t* m_FrameCount;
		std::uint32_t* m_WorldPtr;
		// IDXGISwapChain* m_Swapchain;
		rage::scrNativeRegistration** m_NativeRegistrations;
		std::uint64_t** m_GlobalBase;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
}
