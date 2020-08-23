#include "socket.hpp"

#include <cassert>
#include <exception>
#include <iostream>
#include <string_view>

#ifdef __linux__
	#include <unistd.h>
	#include <arpa/inet.h>
#elif WIN32
	#include <WinSock2.h>
	#include <Windows.h>
	#pragma comment(lib,"WS2_32")
#endif


dolly::network::networklib::TcpSocket::
TcpSocket(std::string_view address)
	: mDescriptor{0}
	, mIpV4{}
	, mPort{}
{
#ifdef WIN32
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		throw std::runtime_error("WSAStartup Error");
	}
#endif
	mDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > mDescriptor) {
		throw std::runtime_error("Socket creation Error");
	}
	char optval = 1;
	if (setsockopt(mDescriptor, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0) {
		throw std::runtime_error("socketopt Error");
	}
	parseAddress(std::string(address));
}

void dolly::network::networklib::TcpSocket::
listenConnections() const
{
	assert(0 < mDescriptor);
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(std::atoi(mPort.data()));
	addr.sin_addr.s_addr = inet_addr(mIpV4.data());
	if (bind(mDescriptor, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
		throw std::runtime_error("Socket bind Error");
	}
	if (listen(mDescriptor, SOMAXCONN) != 0) {
		throw std::runtime_error("Socket listen Error");
	}
}

dolly::network::networklib::TcpSocket::connection
dolly::network::networklib::TcpSocket::
connectToHost() const
{
	assert(0 < mDescriptor);
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(std::atoi(mPort.data()));
	addr.sin_addr.s_addr = inet_addr(mIpV4.data());
	auto res = connect(mDescriptor, (struct sockaddr*)&addr, sizeof(addr));
	if (0 > res) {
		throw std::runtime_error("Server unavailable Error");
	}
	return mDescriptor;
}

dolly::network::networklib::TcpSocket::connection
dolly::network::networklib::TcpSocket::
acceptConnection() const
{
	assert(0 < mDescriptor);
	return accept(mDescriptor, NULL, NULL);
}

void dolly::network::networklib::TcpSocket::
sendData(connection con, std::string_view buffer) const
{
	assert(0 < mDescriptor);
	const int size = static_cast<int>(std::size(buffer)) + 1;
	send(con, buffer.data(), size, 0);
}

std::pair<int, std::string> dolly::network::networklib::TcpSocket::
receiveData(connection con) const
{
	char buffer[receive_data_size];
	int length = recv(con, buffer, receive_data_size, 0);
	return { length, std::string{buffer} };
}

void dolly::network::networklib::TcpSocket::
closeConnection(connection con) const
{
	assert(0 < mDescriptor);
	#ifdef __linux__
		close(con);
		shutdown(mDescriptor, SHUT_RDWR);
	#elif __WIN32
		closesocket(con);
		shutdown(mDescriptor, SD_BOTH);
	#endif
}

bool dolly::network::networklib::TcpSocket::
parseAddress(std::string address)
{
	const size_t it = address.find(":");
	if (it == std::string::npos) {
		return false;
	}
	// TODO: check validation of ipV4 and port.
	mIpV4 = address.substr(0, it);
	mPort = address.substr(it + 1, address.size());
	return true;
}

dolly::network::networklib::TcpSocket::
~TcpSocket()
{
	assert(0 < mDescriptor);
	closeConnection(mDescriptor);
}
