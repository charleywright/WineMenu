#pragma once
#include "game.hpp"
#include <windows.h>
#include <shlwapi.h>
#include <filesystem>

namespace Wine
{
	inline bool FileExists(const std::string &fileName)
	{
		std::filesystem::path p(fileName);
		return std::filesystem::exists(p);
	}

	inline const std::string GetModulePath(HMODULE module)
	{
		std::string path;
		char buffer[MAX_PATH];
		GetModuleFileNameA(module, buffer, MAX_PATH);
		PathRemoveFileSpecA(buffer);
		path = buffer;
		return path;
	}

	/**
	 * \brief Checks if a key is pressed
	 * \param key A virtual key code
	 * \return bool
	 */
	inline bool IsKeyPressed(std::uint16_t key)
	{
		if (GetForegroundWindow() == g_GameVariables->m_GameWindow)
		{
			if (GetAsyncKeyState(key) & 0x8000)
			{
				return true;
			}
		}

		return false;
	}
}
