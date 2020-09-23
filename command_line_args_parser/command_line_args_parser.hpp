#pragma once

// Headers from this project

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <string>

namespace dolly
{
	class CommandLineArgsParser
	{
	private:
		
		static constexpr int argsCount = 5;
		static constexpr char* address = "--address";
		static constexpr char* port = "--port";

	private:

		static bool isCorrectAddress(const std::string& address) noexcept;

		static bool isCorrectPort(const std::string& port);

		static std::string getAddress(const std::string& address,
									  const std::string& port) noexcept;
	public:

		static std::pair<bool, std::string> parse(int argc, char* argv[]) noexcept;

	public:
		~CommandLineArgsParser() = default;

		/// @name Deleted special member functions
		/// @name This class is not default constructible.
		CommandLineArgsParser() = delete;

		/// @brief This class is not copy-constructible
		CommandLineArgsParser(const CommandLineArgsParser&) = delete;

		/// This class is not copy assignable
		CommandLineArgsParser& operator=(const CommandLineArgsParser&) = delete;

		/// This class is not constructible by move constructor
		CommandLineArgsParser(CommandLineArgsParser&&) = delete;

		/// This class is not assignable by move assignment operator
		CommandLineArgsParser& operator=(CommandLineArgsParser&&) = delete;
	};
}
