#include <memory>

#pragma once

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
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
}
