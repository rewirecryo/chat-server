#include "../include/Client.hpp"

Client::Client(int fd)
{
	__fd = fd;
}

void Client::kick()
{
	if(close(__fd) == -1)
	{
		throw NetworkError(strerror(errno));
	}
}

void Client::sendMessage(const Message &msg)
{
	int ret;

	nlohmann::json msg_json = msg.toJSON();
		
	if((ret = send(__fd, msg_json.dump().c_str(), std::min<size_t>(msg_json.dump().size(), 1023), 0)) == -1)
	{
		throw NetworkError(strerror(errno));
	}
}
