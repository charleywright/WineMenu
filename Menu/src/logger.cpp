#include "logger.hpp"
#include <windows.h>
#include "common.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

namespace Wine
{
	namespace
	{
		std::size_t s_LastLogCount = 0;
	}

	Logger::Logger()
	{
		m_FilePath = g_DataDir;
		m_FilePath.append("WineMenu.log");
		m_File.open(m_FilePath, std::ios_base::out | std::ios_base::app);
		Logo();
	}

	Logger::~Logger() noexcept
	{
		FreeConsole();
	}

	void Logger::Info(const char *format, ...)
	{
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);
		va_end(args);
	}

	void Logger::Error(const char *format, ...)
	{
		std::va_list args{};
		va_start(args, format);
		Log("Error", format, args);
		va_end(args);

		g_Running = false;
	}

	bool Logger::RenderConsole()
	{
		return m_RenderConsole;
	}

	void Logger::RenderConsole(bool render)
	{
		m_RenderConsole = render;
	}

	bool Logger::ShowConsole()
	{
		return m_ShowConsole;
	}

	void Logger::ShowConsole(bool show)
	{
		if (!show)
		{
			m_Console.clear();
			m_Console.close();
			FreeConsole();
		}
		else
		{
			if (!AttachConsole(GetCurrentProcessId()))
				AllocConsole();
			SetConsoleTitleA("WineMenu");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			SetConsoleCP(CP_UTF8);
			SetConsoleOutputCP(CP_UTF8);
			m_Console.open("CONOUT$");

			std::lock_guard lock(g_Logger->GetMutex());
			auto msgs = g_Logger->GetMessages();
			auto pfxs = g_Logger->GetPrefixes();

			g_Logger->Logo();
			for (std::size_t i = 0; i < msgs.second; ++i)
				m_Console << pfxs.first[i].get() << msgs.first[i].get() << "\n";
			m_Console.flush();
		}
		m_ShowConsole = show;
	}

	void Logger::Render()
	{
		if (m_RenderConsole)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin(" Log"))
			{
				std::lock_guard lock(g_Logger->GetMutex());
				auto msgs = g_Logger->GetMessages();

				for (std::size_t i = 0; i < msgs.second; ++i)
				{
					ImGui::TextUnformatted(msgs.first[i].get());
				}

				if (s_LastLogCount != msgs.second)
				{
					s_LastLogCount = msgs.second;
					ImGui::SetScrollHereY(1.f);
				}
			}
			ImGui::End();
		}
	}

	void Logger::SetTitle(const char *title)
	{
		SetConsoleTitleA(title);
	}

	void Logger::Log(const char *type, const char *format, std::va_list args)
	{
		std::lock_guard lock(m_Mutex);

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		auto prefix = std::make_unique<char[]>(64);
		std::snprintf(prefix.get(), 63, "[%02d:%02d:%02d] [%s] ", tm->tm_hour, tm->tm_min, tm->tm_sec, type);

		std::size_t messageLength = std::vsnprintf(nullptr, 0, format, args) + 1;
		auto messageBuffer = std::make_unique<char[]>(messageLength);

		std::uninitialized_fill_n(messageBuffer.get(), messageLength, '\0');
		std::vsnprintf(messageBuffer.get(), messageLength, format, args);

		m_File << prefix.get() << messageBuffer.get() << std::endl;
		m_Console << prefix.get() << messageBuffer.get() << std::endl;

		m_Prefixes.push_back(std::move(prefix));
		m_Messages.push_back(std::move(messageBuffer));
	}

	void Logger::Logo()
	{
		m_Console << "##   ##    ##                       ##   ##\n";
		m_Console << "##   ##                             ### ###\n";
		m_Console << "##   ##   ###     #####     ####    #######   ####    #####    ##  ##\n";
		m_Console << "## # ##    ##     ##  ##   ##  ##   #######  ##  ##   ##  ##   ##  ##\n";
		m_Console << "#######    ##     ##  ##   ######   ## # ##  ######   ##  ##   ##  ##\n";
		m_Console << "### ###    ##     ##  ##   ##       ##   ##  ##       ##  ##   ##  ##\n";
		m_Console << "##   ##   ####    ##  ##    #####   ##   ##   #####   ##  ##   ######\n\n";
		m_Console.flush();
	}

	std::mutex &Logger::GetMutex()
	{
		return m_Mutex;
	}

	std::pair<std::unique_ptr<char[]> *, std::size_t> Logger::GetMessages()
	{
		return std::make_pair(m_Messages.data(), m_Messages.size());
	}

	std::pair<std::unique_ptr<char[]> *, std::size_t> Logger::GetPrefixes()
	{
		return std::make_pair(m_Prefixes.data(), m_Prefixes.size());
	}
}
