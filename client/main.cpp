// Headers from this project
#include "client.hpp"

// Headers from other projects
#include "socket.hpp"
#include "logger.hpp"

// Headers from third party libraries

// Headers from standard libraries
#include <iostream>
#include <string>

int main()
{
	using logger = dolly::logger::logger;
	using loggerLevel = dolly::logger::logger::level;
	const std::string address = "192.168.0.48:8080";
	client c{address};
	try {
		logger::get().setupLogger();
		logger::get().setLevel(loggerLevel::trace);
		c.run();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}