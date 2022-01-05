#include <windows.h>
#include "game.hpp"
#include "memory.hpp"

namespace Wine {
  GameVariables::GameVariables():
		m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
    m_GameBuild(Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17).Add(265 + 3).Rip().As<decltype(m_GameBuild)>())
	{
		// auto sig = Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17);
		// m_GameBuild = sig.Add(265 + 3).Rip().As<decltype(m_GameBuild)>();
	}
}
