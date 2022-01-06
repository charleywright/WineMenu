#include <windows.h>
#include "game.hpp"
#include "memory.hpp"

namespace Wine {
  GameVariables::GameVariables():
    m_GameState(Signature("48 85 C9 74 4B 83 3D", "GameState").Scan().Add(7).Rip().As<decltype(m_GameState)>()),
    m_FrameCount(Signature("F3 0F 10 0D ? ? ? ? 44 89 6B 08", "FrameCount").Scan().Add(4).Rip().Sub(8).As<decltype(m_GameState)>()),
    m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
    m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8D 55 A0 48 8B 01", "D3D Swapchain").Scan().Add(3).Rip().As<decltype(m_Swapchain) &>()),
    m_NativeRegistrations(Signature("48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B7 15 ? ? ? ? 33 FF", "NativeRegistrations").Scan().Add(7).Rip().As<decltype(m_NativeRegistrations)>()),
    m_GlobalBase(Signature("4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0", "GlobalPtr").Scan().Add(7).Rip().As<decltype(m_GlobalBase)>()),
    m_WorldPtr(Signature("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07", "WorldPtr").Scan().Add(3).Rip().As<decltype(m_WorldPtr)>()),
    m_GameBuild(Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8", "GameBuild").Scan().Sub(17).Add(265 + 3).Rip().As<decltype(m_GameBuild)>())
	{

	}

  GameFunctions::GameFunctions() :
    m_IsDlcPresent(Signature("84 C0 74 0D 8D 53 0C", "IsDlcPresent").Scan().Sub(63).As<decltype(m_IsDlcPresent)>()),
    m_WndProc(Signature("48 8B 0D ? ? ? ? 48 8D 55 EF FF 15", "WndProc").Scan().Sub(0x385).As<decltype(m_WndProc)>()),
    m_GetEventData(Signature("48 85 C0 74 14 4C 8B 10", "GetEventData").Scan().Sub(28).As<decltype(m_GetEventData)>()),
    m_GetLabelText(Signature("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9", "GetLabelText").Scan().Sub(19).As<decltype(m_GetLabelText)>())
	{
	}
}
