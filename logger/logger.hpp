#pragma once

#include <string>
#include <array>
#include <fstream>
#include <filesystem>

namespace dolly::logger {
	class logger
	{
	public:
		enum class level : int { none, fatal, critical,
						   error, warning, notice,
			               information, debug, trace};
	private:
		level mLevel;
		std::ofstream mFileStream;
		static constexpr std::array<char*, 9> levels{"NONE", "FATAL", "CRITICAL",
			                                         "ERROR", "WARNING", "NOTICE",
			                                         "INFORMATION", "DEBUG", "TRACE"};
	public:
		static logger& get() noexcept;

		bool setupLogger(const std::string path = std::filesystem::current_path().string(),
															const level l = level::none);
		void setLevel(level l) noexcept;
		
		void fatal(const std::string mess) noexcept;
		void critical(const std::string mess) noexcept;
		void error(const std::string mess) noexcept;
		void warning(const std::string mess) noexcept;
		void notice(const std::string mess) noexcept;
		void information(const std::string mess) noexcept;
		void debug(const std::string mess) noexcept;
		void trace(const std::string mess) noexcept;
	private:
		logger();
		std::string generateFileName() const noexcept;
	public:
		
		logger(const logger&) = delete;
		
		logger(logger&&) = delete;
		
		logger& operator=(const logger&) = delete;
		
		logger& operator=(logger&&) = delete;
		virtual ~logger();
	};
}