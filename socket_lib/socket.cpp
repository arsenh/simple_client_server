#include "socket.hpp"
#include <iostream>

network::slib::socket::
socket(std::string_view address)
	: mDescriptor{0}
	, mAddress{}
	, mPort{}
{
	std::cout << address << std::endl;
}

void network::slib::socket::
listen()
{

}

void network::slib::socket::
accept()
{
}

void network::slib::socket::
send(std::string_view buffer)
{
	(void)buffer;
}

std::string_view network::slib::socket::
receive()
{
	return std::string_view();
}

network::slib::socket::
~socket()
{
	// TODO: close socket
}
