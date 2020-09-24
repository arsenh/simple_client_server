// Headers from this project
#include "client.hpp"

// Headers from other projects

// Headers from third party libraries

// Headers from standard libraries
#include <string>
#include <iostream>

void client::run() const
{
	std::string send_data;
	const connection client_socket = mClientSocket.connectToHost();
	std::cout << "Client connected to address: " << mAddress << std::endl;
	logger::get().information(std::string("Client conneted to address: ") + std::string(mAddress));
	for (;;) {
		std::cout << "Please enter the word: ";
		std::getline(std::cin, send_data);
		logger::get().debug("User entered the folowing text: " + send_data);
		if (send_data == "exit") {
			mClientSocket.closeConnection(client_socket);
			logger::get().information("Client closes the server conncetion.");
			break;
		}
		mClientSocket.sendData(client_socket, send_data);
		logger::get().debug("Client sended to server following data: " + send_data);
		const auto [length, data] = mClientSocket.receiveData(client_socket);
		if (length < 0) {
			logger::get().error("Receive data error");
			throw std::runtime_error("Client Receive data Error");
		}
		std::cout << "To Upper: " << data << std::endl;
	}
}

client::client(std::string_view address)
	: mAddress{ address }
	, mClientSocket { mAddress }
{

}