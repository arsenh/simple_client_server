#pragma once

#include <string_view>

namespace network::slib {
	class socket {
	private:
		int mDescriptor;
		std::string_view mAddress;
		std::string_view mPort;
	public:
		socket(std::string_view address);
		void listen();
		void accept();
		void send(std::string_view buffer);
		std::string_view receive();
		virtual ~socket();
	};
}