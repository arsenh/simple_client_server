#include "command_line_args_parser.hpp"
// Headers from this project

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <regex>
#include <cmath>
#include <iostream>

bool dolly::commandLineArgsParser::isCorrectAddress(const std::string& address) noexcept
{
    return std::regex_match(address, std::regex("(\\d{1,3}(\\.\\d{1,3}){3})"));
}

bool dolly::commandLineArgsParser::isCorrectPort(const std::string& port)
{
	const int minPort = 0;
	const int maxPort = std::pow(2, 16);
	int portInt{};
	try {
		portInt = std::stoi(port);
	}
	catch (const std::invalid_argument&) {
		return false;
	}
	return (minPort <= portInt) && (portInt < maxPort);
}

std::string dolly::commandLineArgsParser::getAddress(const std::string& address, const std::string& port) noexcept
{
	return address + ":" + port;
}

std::pair<bool, std::string> dolly::commandLineArgsParser::parse(int argc, char* argv[]) noexcept
{
	if (argc != argsCount) {
		std::cerr << "Incorrect count of command line arguments."
			<< " \nFor more information use --help option." << std::endl;
		return { true, {} };
	}
	if (strcmp(argv[1], address) || strcmp(argv[3], port)) {
		std::cerr << "Incorrect command line arguments." << std::endl;
		return { true, {} };
	}
	if (!isCorrectAddress(argv[2])) {
		std::cerr << "Please enter correct IP address." << std::endl;
		return { true, {} };
	}
	if (!isCorrectPort(argv[4])) {
		std::cerr << "Please enter correct port." << std::endl;
		return { true, {} };
	}
	std::string address = getAddress(argv[2], argv[4]);
	return { false, address };
}
