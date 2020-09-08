#pragma once

// Headers from this project

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <string_view>
#include <string>


struct sockaddr_in;

namespace dolly::network::networklib
{
	class TcpSocket
	{
	public:
		using connection = int;
		using hostInfo = std::pair<std::string, std::string>;

	private:
		static constexpr int receive_data_size = 200;
		int mDescriptor;
		std::string mIpV4;
		std::string mPort;
	
	private:
		bool parseAddress(std::string address);
		sockaddr_in createSocketAddress() const;
	
	public:
		explicit TcpSocket(std::string_view address);
		void listenConnections() const;
		connection connectToHost() const;
		std::pair<connection, hostInfo> acceptConnection() const;
		void sendData(connection con, std::string_view buffer) const;
		std::pair<int, std::string> receiveData(connection con) const;
		void closeConnection(connection con) const;
		virtual ~TcpSocket();
	};
}
