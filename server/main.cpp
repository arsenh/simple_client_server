#include "socket.hpp"
#include "logger.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <string>
#include <thread>
#include <chrono>

using Socket = dolly::network::networklib::TcpSocket;
using connection = Socket::connection;

void to_upper(std::string& str)
{
	std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
}


void handle_client_connection(const Socket& server, const connection socket)
{
	while (true) {
		auto [length, data] = server.receiveData(socket);
		std::cout << "server received data from connectes host" << std::endl;
		if (length < 0) {
			//throw std::exception("Server Receive data Error");
			std::cout << "Client sended FIN: length < 0 = " << length << std::endl;
			break;
		} else if (length == 0) {
			std::cout << "Client sended FIN: length == 0 = " << length << std::endl;
			break;
		}
		to_upper(data);
		std::cout << "Server send UPPER data to host" << std::endl;
		server.sendData(socket, data);
	}
}

void server_run()
{
	std::string address = "0.0.0.0:8080";
	Socket server{ address };
	server.listenConnections();
	std::cout << "Server started on address: " << address << std::endl;
	while (true) {
		connection con = server.acceptConnection();
		std::cout << "\naccept connection" << std::endl;
		assert(con > 0);
		handle_client_connection(server, con);
	}
}

int main()
{
	try {
		server_run();
		std::cin.get();
	} catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
    return 0;
}