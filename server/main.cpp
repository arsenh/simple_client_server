// Headers from this project

// Headers from other projects
#include "logger.hpp"
#include "server.hpp"
#include "command_line_args_parser.hpp"

// Headers from third party libraries

// Headers from standard libraries
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	const auto [err, address] = dolly::CommandLineArgsParser::parse(argc, argv);
	if (err) {
		exit(1);
	}
	using logger = dolly::logger::logger;
	using loggerLevel = dolly::logger::logger::level;
	server s{ address };
	try {
		logger::get().setupLogger();
		logger::get().setLevel(loggerLevel::trace);
		s.run();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}