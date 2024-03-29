#pragma once
#include <windows.h>
#include <cstdint>
#include <memory>
#include "VMTHook.hpp"
#include <dxgi.h>

namespace Wine
{
	struct Hooks
	{
		static bool IsDlcPresent(std::uint32_t hash);
		static const char *GetLabelText(void *unk, const char *label);
		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t *args, std::uint32_t argCount);
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static bool SetCursorPos(int x, int y);

		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain *dis, UINT syncInterval, UINT flags);

		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain *dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const &) = delete;
		Hooking(Hooking &&) = delete;
		Hooking &operator=(Hooking const &) = delete;
		Hooking &operator=(Hooking &&) = delete;

		/**
		 * @brief Activates all hooks
		 */
		void Hook();

		/**
		 * @brief Deactivates all hooks
		 */
		void Unhook();

		friend struct Hooks;

	private:
		void *m_OriginalIsDlcPresent{};
		void *m_OriginalGetLabelText{};
		void *m_OriginalGetEventData{};
		void *m_OriginalWndProc{};
		void *m_OriginalSetCursorPos{};
		VMTHook m_D3DHook;
	};

	inline std::unique_ptr<Hooking> g_Hooking;
}
