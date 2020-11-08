// Headers from this project
#include "client.hpp"

// Headers from other projects
#include "logger/logger.hpp"
#include "command_line_args_parser/command_line_args_parser.hpp"

// Headers from third party libraries

// Headers from standard libraries
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	const auto [err, address] = dolly::commandLineArgsParser::parse(argc, argv);
	if (err) {
		exit(1);
	}
	using logger = dolly::logger::logger;
	using loggerLevel = dolly::logger::logger::level;
	client c{address};
	try {
		logger::get().setupLogger();
		logger::get().setLevel(loggerLevel::trace);
		c.run();
	} catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}