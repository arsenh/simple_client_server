#pragma once

// Headers from this project

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
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
		static constexpr std::array<const char*, 9> levels{"NONE", "FATAL", "CRITICAL",
														   "ERROR", "WARNING", "NOTICE",
			                                               "INFORMATION", "DEBUG", "TRACE"};
	public:

		/// @brief Returns logger singleton object.
		static logger& get() noexcept;

		/**
		 * Setup the loggger.
		 * 
		 * \param path - Logger file directory.
		 * \param l - logger level.
		 * \return true if setup finished successfully, otherwise false.
		 */
		bool setupLogger(const std::string path = std::filesystem::current_path().string(),
															const level l = level::none);

		/**
		 * Sets the logger level.
		 * 
		 * \param l - logger level.
		 */
		void setLevel(level l) noexcept;
		
		/**
		 * Writes fatal message in logger file.
		 * 
		 * \param mess - logger message
		 */
		void fatal(const std::string mess) noexcept;
		
		/**
		 * Writes critical message in logger file.
		 *
		 * \param mess - logger message
		 */
		void critical(const std::string mess) noexcept;
		
		/**
		 * Writes error message in logger file.
		 *
		 * \param mess - logger message
		 */
		void error(const std::string mess) noexcept;
		
		/**
		 * Writes warning message in logger file.
		 *
		 * \param mess - logger message
		 */
		void warning(const std::string mess) noexcept;
		
		/**
		 * Writes notice message in logger file.
		 *
		 * \param mess - logger message
		 */
		void notice(const std::string mess) noexcept;
		
		/**
		 * Writes information message in logger file.
		 *
		 * \param mess - logger message
		 */
		void information(const std::string mess) noexcept;
		
		/**
		 * Writes debug message in logger file.
		 *
		 * \param mess - logger message
		 */
		void debug(const std::string mess) noexcept;
		
		/**
		 * Writes trace message in logger file.
		 *
		 * \param mess - logger message
		 */
		void trace(const std::string mess) noexcept;
	private:
		
		/**
		 * Generates the logger file name.
		 * 
		 * \return - generated file name.
		 */
		std::string generateFileName() const noexcept;
	
	private:
		
		/// @name Special member functions
		/// Constructor
		logger();
		
		/// Destructor
		virtual ~logger();

	public:
		
		/// @name Deleted special member functions
		/// @brief This class is not copy-constructible
		logger(const logger&) = delete;

		/// This class is not copy assignable
		logger& operator=(const logger&) = delete;

		/// This class is not constructible by move constructor
		logger(logger&&) = delete;

		/// This class is not assignable by move assignment operator
		logger& operator=(logger&&) = delete;
	};
}
