#include "socket.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void client_run()
{
	using Socket = dolly::network::networklib::TcpSocket;
	using connection = Socket::connection;
	const std::string address = "127.0.0.1:8080";
	std::string send_data;
	Socket client{ "127.0.0.1:8080" };
	const connection con = client.connectToHost();
	std::cout << "Client connected to address: " << address << std::endl;

	while (true)
	{
		std::cout << "Please enter the word: ";
		std::cin >> send_data;
		if (send_data == "exit") {
			client.closeConnection(con);
			break;
		}
		client.sendData(con, send_data);
		const auto [length, data] = client.receiveData(con);
		if (length < 0) {
			throw std::exception("Client Receive data Error");
		}
		std::cout << "Server sended following data: " << data << std::endl;
	}
}

int main()
{
	try {
		client_run();
	} catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
    return 0;
}