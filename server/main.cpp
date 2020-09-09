// Headers from this project

// Headers from other projects
#include "logger.hpp"
#include "server.hpp"

// Headers from third party libraries

// Headers from standard libraries
#include <iostream>
#include <string>

int main()
{
	std::string address = "192.168.0.48:8080";
	server s{ address };
	try {
		s.run();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}