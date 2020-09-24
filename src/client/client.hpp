#pragma once

// Headers from this project

// Headers from other projects
#include "socket/tcpSocket.hpp"

// Headers from third party libraries
#include "logger/logger.hpp"

// Headers from standard libraries
#include <string_view>

class client
{
public:
	using tcpSocket = dolly::network::tcpSocket;
	using connection = tcpSocket::connection;
	using logger = dolly::logger::logger;

private:

	const std::string_view mAddress;
	tcpSocket mClientSocket;

public:
	/// @brief Runs the client socket.
	void run() const;
public:
	/**
	 * @brief The only available constructor
	 * @param parent - parent widget of view
	 */
	explicit client(std::string_view address);

	/// Destructor
	virtual ~client() = default;

	/// @name Deleted special member functions
	/// @brief This class is not copy-constructible
	client(const client&) = delete;

	/// This class is not copy assignable
	client& operator=(const client&) = delete;

	/// This class is not constructible by move constructor
	client(client&&) = delete;

	/// This class is not assignable by move assignment operator
	client& operator=(client&&) = delete;
};