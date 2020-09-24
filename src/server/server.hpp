#pragma once

// Headers from this project

// Headers from other projects
#include "socket_lib/socket.hpp"

// Headers from third party libraries
#include "logger/logger.hpp"

// Headers from standard libraries
#include <string_view>

class server
{
public:
	using socket = dolly::network::networklib::TcpSocket;
	using connection = socket::connection;
	using logger = dolly::logger::logger;

private:
	const std::string_view mAddress;
	socket mServerSocket;

private:
	/**
	 * @brief To Upper string.
	 * \param str - string
	 */
	void to_upper(std::string& str) const noexcept;

	/**
	 * . Handle the client connection.
	 * 
	 * \param con - client connection descriptor.
	 */
	void handle_client_connection(const connection con) const;

public:

	/// @brief Runs the server socket.
	void run() const;
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
