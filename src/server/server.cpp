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

void server::toUpper(std::string& str) noexcept
{
	std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
}

void server::acceptClientConnection()
{
	const auto& [con, host_info] = mServerSocket.acceptConnection();
	mClientSockets.push_back(con);
	std::cout << "Connected client: " << host_info.first << std::endl;
	logger::get().debug("Server accepted the client connection.");
}

void server::handleClientConnection(const connection con)
{
	auto [err, data] = mServerSocket.receiveData(con);
	logger::get().debug("Server received data from client connetion");
	if (err) {
		std::cout << "Client closes the connection" << std::endl;
		logger::get().error("Client sended FIN. Server closes the connection");
		mServerSocket.closeConnection(con);
		mClientSockets.erase(std::find(std::cbegin(mClientSockets), std::cend(mClientSockets), con));
		return;
	}
	toUpper(data);
	mServerSocket.sendData(con, data);
	logger::get().information("Server send data to client connection");
}

std::pair<fd_set, int> server::initSocketSet(const connection master) const
{
	fd_set reads;
	FD_ZERO(&reads);
	FD_SET(master, &reads);
	for (const auto con : mClientSockets) {
		FD_SET(con, &reads);
	}
	int max{};
	if (mClientSockets.empty()) {
		max = master;
	} else {
		int max = (std::max)(master,
			*std::max_element(std::cbegin(mClientSockets),
								std::cend(mClientSockets)));
	}
	return {reads, max};
}

void server::run()
{
	mServerSocket.listenConnections();
	std::cout << "Server started on address: " << mAddress << std::endl;
	logger::get().information(std::string("Server started on address: ") + std::string(mAddress));
	for (;;) {
		connection master = mServerSocket.getConnection();
		auto [reads, max]= initSocketSet(master);
		if (select(max + 1, &reads, nullptr, nullptr, nullptr) <= 0) {
			throw std::runtime_error("Select system call error");
		}
		if (FD_ISSET(master, &reads)) {
			acceptClientConnection();
		}
		for (const auto con : mClientSockets) {
			if (FD_ISSET(con, &reads)) {
				handleClientConnection(con);
			}
		}
	}
}

server::server(std::string_view address)
	: mAddress { address }
	, mServerSocket{ mAddress }
	, mClientSockets{}
{

}
