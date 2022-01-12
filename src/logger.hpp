#pragma once
#include <memory>
#include <mutex>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cstdarg>
#include "common.hpp"

namespace Wine
{
	class Logger
	{
	public:
		explicit Logger();
		~Logger() noexcept;

		Logger(Logger const &) = delete;
		Logger(Logger &&) = delete;
		Logger &operator=(Logger const &) = delete;
		Logger &operator=(Logger &&) = delete;

		/**
		 * \brief Logs an info message
		 * \param format The format of the logged text
		 * \param ... The arguments to format the string
		 */
		void Info(const char *format, ...);

		/**
		 * \brief Logs WineMenu logo
		 */
		void Logo();

		/**
		 * \brief Logs an error message
		 * \param format The format of the logged text
		 * \param ... The arguments to format the string
		 */
		void Error(const char *format, ...);

		/**
		 * \brief Sets the title of the console
		 * \param title The new title for the console
		 */
		void SetTitle(const char *title);

		/**
		 * \brief Whether a console using ImGUI is showing
		 * \return bool
		 */
		bool RenderConsole();

		/**
		 * \brief Whether to render a console using ImGUI
		 * \param render Whether to render the console
		 */
		void RenderConsole(bool render);

		/**
		 * \brief Whether a debug console is showing using AllocConsole
		 * \return bool
		 */
		bool ShowConsole();

		/**
		 * \brief Whether to show a debug console using AllocConsole
		 * \param show Whether to show the console
		 */
		void ShowConsole(bool show);

		/**
		 * \brief Render any logger related UI
		 */
		void Render();

		/**
		 * \brief Logs a message
		 * \param type The type of the logged text, visual only
		 * \param format The format of the logged text
		 * \param args The arguments to format the string
		 */
		void Log(const char *type, const char *format, std::va_list args);

		std::mutex &GetMutex();
		std::pair<std::unique_ptr<char[]> *, std::size_t> GetMessages();
		std::pair<std::unique_ptr<char[]> *, std::size_t> GetPrefixes();

	private:
		std::mutex m_Mutex;
		std::vector<std::unique_ptr<char[]>> m_Messages;
		std::vector<std::unique_ptr<char[]>> m_Prefixes;
		bool m_RenderConsole = false;
		bool m_ShowConsole = false;
		std::filesystem::path m_FilePath;
		std::ofstream m_File;
		std::ofstream m_Console;
	};

	inline std::unique_ptr<Logger> g_Logger;
}
