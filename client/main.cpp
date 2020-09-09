// Headers from this project
#include "client.hpp"

// Headers from other projects
#include "socket.hpp"

// Headers from third party libraries

// Headers from standard libraries
#include <iostream>
#include <string>

int main()
{
	const std::string address = "192.168.0.48:8080";
	client c{address};
	try {
		c.run();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}