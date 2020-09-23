#pragma once

// Headers from this project

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <string>

namespace dolly
{
	class commandLineArgsParser
	{
	private:
		
		static constexpr int argsCount = 5;
		static constexpr char* address = "--address";
		static constexpr char* port = "--port";

	private:
		/**
		 * Checks correctness of ip address.
		 * 
		 * \param address - ip address.
		 * \return true if address is correct, otherwise false.
		 */
		static bool isCorrectAddress(const std::string& address) noexcept;

		/**
		 * Checks correctness of port.
		 * 
		 * \param port - tcp connection port
		 * \return true if port is correct, otherwise false.
		 */
		static bool isCorrectPort(const std::string& port);

		/**
		 * Returns full connection address {ip adress + port}.
		 * 
		 * \param address - ip address
		 * \param port - port
		 * \return full connection address. 
		 */
		static std::string getAddress(const std::string& address,
									  const std::string& port) noexcept;
	public:

		/**
		 * Parses from command line arguments ip address and port.
		 * 
		 * \param argc - count of command line arguments.
		 * \param argv - arguments
		 * \return error flag and connetion address.
		 */
		static std::pair<bool, std::string> parse(int argc, char* argv[]) noexcept;

	public:
		~commandLineArgsParser() = default;

		/// @name Deleted special member functions
		/// @name This class is not default constructible.
		commandLineArgsParser() = delete;

		/// @brief This class is not copy-constructible
		commandLineArgsParser(const commandLineArgsParser&) = delete;

		/// This class is not copy assignable
		commandLineArgsParser& operator=(const commandLineArgsParser&) = delete;

		/// This class is not constructible by move constructor
		commandLineArgsParser(commandLineArgsParser&&) = delete;

		/// This class is not assignable by move assignment operator
		commandLineArgsParser& operator=(commandLineArgsParser&&) = delete;
	};
}
