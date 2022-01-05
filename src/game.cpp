#include <windows.h>
#include "game.hpp"
#include "memory.hpp"

namespace Wine {
  GameVariables::GameVariables():
    m_GameState(Signature("48 85 C9 74 4B 83 3D").Scan().Add(7).Rip().As<decltype(m_GameState)>()),
    m_FrameCount(Signature("F3 0F 10 0D ? ? ? ? 44 89 6B 08").Scan().Add(4).Rip().Sub(8).As<decltype(m_GameState)>()),
    m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
    // m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8D 55 A0 48 8B 01").Scan().Add(3).Rip().As<decltype(m_Swapchain) &>()),
    m_NativeRegistrations(Signature("48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B7 15 ? ? ? ? 33 FF").Scan().Add(7).Rip().As<decltype(m_NativeRegistrations)>()),
    m_GlobalBase(Signature("4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0").Scan().Add(7).Rip().As<decltype(m_GlobalBase)>()),
    m_WorldPtr(Signature("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07").Scan().Add(3).Rip().As<decltype(m_WorldPtr)>()),
    m_GameBuild(Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17).Add(265 + 3).Rip().As<decltype(m_GameBuild)>())
	{

	}
}
