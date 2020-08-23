#pragma once

#include <string_view>

namespace dolly::network::networklib
{
	class TcpSocket
	{
	
	public:
		using connection = int;
	
	private:
		static constexpr int receive_data_size = 200;
		int mDescriptor;
		std::string mIpV4;
		std::string mPort;
	
	private:
		bool parseAddress(std::string address);
	
	public:
		explicit TcpSocket(std::string_view address);
		void listenConnections();
		connection connectToHost();
		connection acceptConnection();
		void sendData(connection con, std::string_view buffer);
		std::pair<int, std::string> receiveData(connection con);
		void closeConnection(connection con);
		virtual ~TcpSocket();
	};
}