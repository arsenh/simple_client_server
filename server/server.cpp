// Headers from this project
#include "server.hpp"

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

void server::to_upper(std::string& str) const noexcept
{
	std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
}

void server::handle_client_connection(const connection con) const
{
	for (;;) {
		auto [err, data] = mServerSocket.receiveData(con);
		std::cout << "server received data from connectes host" << std::endl;
		if (err) {
			std::cout << "Client sended FIN " << std::endl;
			mServerSocket.closeConnection(con);
			break;
		}
		to_upper(data);
		std::cout << "Server send UPPER data to host" << std::endl;
		mServerSocket.sendData(con, data);
	}
}

void server::run() const
{
	mServerSocket.listenConnections();
	std::cout << "Server started on address: " << mAddress << std::endl;
	for (;;) {
		const auto& [con, host_info] = mServerSocket.acceptConnection();
		const auto& [ipAddress, port] = host_info;
		std::cout << "\naccept connection => " << "IPv4: " << ipAddress << " Port: " << port << std::endl;
		assert(con > 0);
		handle_client_connection(con);
	}
}

server::server(std::string_view address)
	: mAddress { address }
	, mServerSocket{ mAddress }
{

}
