#include "socket.hpp"
#include <iostream>


int main()
{
    network::slib::socket server{"127.0.01:8080"};
    return 0;
}