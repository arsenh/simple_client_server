// Headers from this project
#include "server.hpp"

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <thread>

void server::to_upper(std::string& str) noexcept
{
	std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
}

void server::handle_client_connection(const connection con) const
{
	for (;;) {
		auto [err, data] = mServerSocket.receiveData(con);
		logger::get().debug("Server received data from client connetion");
		if (err) {
			std::cout << "Client closes the connection" << std::endl;
			logger::get().error("Client sended FIN. Server closes the connection");
			mServerSocket.closeConnection(con);
			break;
		}
		to_upper(data);
		mServerSocket.sendData(con, data);
		logger::get().information("Server send data to client connection");
	}
}

void server::run() const
{
	mServerSocket.listenConnections();
	std::cout << "Server started on address: " << mAddress << std::endl;
	logger::get().information(std::string("Server started on address: ") + std::string(mAddress));
	for (;;) {
		const auto& [con, host_info] = mServerSocket.acceptConnection();
		logger::get().debug("Server accepted the client connection.");
		const auto& [ipAddress, port] = host_info;
		logger::get().information("Connection client ip address: " + ipAddress + " port: " + port);
		std::cout << "\naccept connection => " << "IPv4: " << ipAddress << " Port: " << port << std::endl;
		assert(con > 0);
		std::thread t(&server::handle_client_connection, this, con);
		t.detach();
	}
}

server::server(std::string_view address)
	: mAddress { address }
	, mServerSocket{ mAddress }
{

}
