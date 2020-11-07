#pragma once

// Headers from this project

// Headers from other projects
#include "socket/tcpSocket.hpp"
#include "logger/logger.hpp"

// Headers from third party libraries
#include <ws2tcpip.h>

// Headers from standard libraries
#include <string_view>
#include <vector>

class server
{
public:
	using tcpSocket = dolly::network::tcpSocket;
	using connection = tcpSocket::connection;
	using logger = dolly::logger::logger;

private:
	const std::string_view mAddress;
	tcpSocket mServerSocket;
	std::vector<connection> mClientSockets;

private:
	/**
	 * @brief To Upper string.
	 * \param str - string
	 */
	static void toUpper(std::string& str) noexcept;

	void acceptClientConnection();

	/**
	 * . Handle the client connection.
	 * 
	 * \param con - client connection descriptor.
	 */
	void handleClientConnection(const connection con) const;

	std::pair<fd_set, int> initSocketSet(const connection master) const;

public:

	/// @brief Runs the server socket.
	void run();
public:
	/**
	 * @brief The only available constructor
	 * @param parent - parent widget of view
	 */
	explicit server(std::string_view address);

	/// Destructor
	virtual ~server() = default;

	/// @name Deleted special member functions
	/// @brief This class is not copy-constructible
	server(const server&) = delete;

	/// This class is not copy assignable
	server& operator=(const server&) = delete;

	/// This class is not constructible by move constructor
	server(server&&) = delete;

	/// This class is not assignable by move assignment operator
	server& operator=(server&&) = delete;
};
