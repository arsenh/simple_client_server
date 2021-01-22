// Headers from this project
#include "tcpSocket.hpp"

// Headers from other projects

// Headers from third party libraries
#ifdef __linux__
	#include <unistd.h>
	#include <arpa/inet.h>
#elif WIN32
	#include <WinSock2.h>
	#include <Windows.h>
#pragma comment(lib,"WS2_32")
#endif

// Headers from standard libraries
#include <cassert>
#include <stdexcept>
#include <string_view>
#include <cstring>

dolly::network::tcpSocket::
tcpSocket(std::string_view address)
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

void dolly::network::tcpSocket::
listenConnections() const
{
	assert(0 < mDescriptor);
	sockaddr_in addr = createSocketAddress();
	if (bind(mDescriptor, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
		throw std::runtime_error("Socket bind Error");
	}
	if (listen(mDescriptor, SOMAXCONN) != 0) {
		throw std::runtime_error("Socket listen Error");
	}
}

dolly::network::tcpSocket::connection
dolly::network::tcpSocket::
connectToHost() const
{
	assert(0 < mDescriptor);
	sockaddr_in addr = createSocketAddress();
	auto res = connect(mDescriptor, (struct sockaddr*)&addr, sizeof(addr));
	if (0 > res) {
		throw std::runtime_error("Server unavailable Error");
	}
	return mDescriptor;
}

std::pair<dolly::network::tcpSocket::connection,
dolly::network::tcpSocket::hostInfo>
dolly::network::tcpSocket::
acceptConnection() const
{
	assert(0 < mDescriptor);
	sockaddr_in claddr;
	memset(&claddr, 0, sizeof(claddr));
#ifdef WIN32
	using socklen_t = int;
#endif // WIN32

    socklen_t i = sizeof(claddr);
	connection con = accept(mDescriptor, (sockaddr*)&claddr, &i);
	if (0 > con) {
		throw std::runtime_error("Server accept Error");
	}
	hostInfo info;
	info.first = inet_ntoa(claddr.sin_addr);
	info.second = std::to_string(ntohs(claddr.sin_port));
	return { con, info };
}

void dolly::network::tcpSocket::
sendData(connection con, std::string_view buffer) const
{
	assert(0 < mDescriptor);
	const int size = static_cast<int>(std::size(buffer)) + 1;
	send(con, buffer.data(), size, 0);
}

std::pair<bool, std::string> dolly::network::tcpSocket::
receiveData(connection con) const
{
	char buffer[receive_data_size];
	int length = recv(con, buffer, receive_data_size, 0);
	bool err = (length <= 0);
	return { err, std::string{buffer} };
}

void dolly::network::tcpSocket::
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

bool dolly::network::tcpSocket::
parseAddress(std::string address)
{
	const size_t it = address.find(":");
	if (it == std::string::npos) {
		return false;
	}
	mIpV4 = address.substr(0, it);
	mPort = address.substr(it + 1, address.size());
	return true;
}

sockaddr_in dolly::network::tcpSocket::
createSocketAddress() const
{
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(std::atoi(mPort.data()));
	addr.sin_addr.s_addr = inet_addr(mIpV4.data());
	return addr;
}

dolly::network::tcpSocket::
~tcpSocket()
{
	assert(0 < mDescriptor);
	closeConnection(mDescriptor);
}
