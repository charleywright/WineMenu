#include "d3dRenderer.hpp"
#include "logger.hpp"
#include "game.hpp"

namespace Wine
{
	D3DRenderer::D3DRenderer():
		m_Swapchain(g_GameVariables->m_Swapchain)
	{
		// if (FAILED(m_Swapchain->GetDevice(__uuidof(ID3D11Device), (void**)(&m_Device))))
			// g_Logger->Error("Failed to get D3D Device");
		// m_Device->GetImmediateContext(&m_Context);
	}

	D3DRenderer::~D3DRenderer() noexcept
	{

	}

	void D3DRenderer::BeginFrame()
	{

	}

	void D3DRenderer::EndFrame()
	{

	}

	void D3DRenderer::PreResize()
	{

	}

	void D3DRenderer::PostResize()
	{

	}

	void D3DRenderer::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{

	}
}
