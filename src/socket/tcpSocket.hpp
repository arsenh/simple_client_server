#pragma once

// Headers from this project

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <string_view>
#include <string>

struct sockaddr_in;

namespace dolly::network
{
	class tcpSocket
	{
	public:

		using connection = int;
		using hostInfo = std::pair<std::string, std::string>;

	private:

		static constexpr int receive_data_size = 200;
		connection mDescriptor;
		std::string mIpV4;
		std::string mPort;
	
	private:
		/**
		 * @brief Retrieves from address string IP4 address and port.
		 * \param address - string which contains IP4 address and port.
		 * \return - true if address parsed successfully, otherwise false.
		 */
		bool parseAddress(std::string address);

		/**
		 * @brief Creates IP4 address family socket address.
		 * \return - Socket address object.
		 */
		sockaddr_in createSocketAddress() const;
	
	public:

		/// @brief Listen the network connections.
		void listenConnections() const;
		
		/// @brief Connect to host.
		connection connectToHost() const;
		
		/**
		 * @brief Accept client connection.
		 * \return - Client connection and client info {ip address and port}.
		 */
		std::pair<connection, hostInfo> acceptConnection() const;
		
		/**
		 * @brief Send data to client.
		 * \param con - client connection.
		 * \param buffer - data buffer.
		 * \return - Client connection and client info {ip address and port}.
		 */
		void sendData(connection con, std::string_view buffer) const;

		/**
		 * @brief Receive data from client.
		 * \return - length of data and received buffer.
		 */
		std::pair<bool, std::string> receiveData(connection con) const;
		
		/**
		 * @brief Close socket connetion.
		 * \param con - connetion descriptor.
		 */
		void closeConnection(connection con) const;

		connection getConnection() const noexcept {
			return mDescriptor;
		}

	public:
		/**
		 * @brief The only available constructor
		 * @param parent - parent widget of view
		 */
		explicit tcpSocket(std::string_view address);
		
		/// Destructor
		virtual ~tcpSocket();
		
		/// @name Deleted special member functions
		/// @brief This class is not copy-constructible
		tcpSocket(const tcpSocket&) = delete;

		/// This class is not copy assignable
		tcpSocket& operator=(const tcpSocket&) = delete;

		/// This class is not constructible by move constructor
		tcpSocket(tcpSocket&&) = delete;

		/// This class is not assignable by move assignment operator
		tcpSocket& operator=(tcpSocket&&) = delete;
	};
}
