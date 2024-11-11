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

void Client::send(const void *buf, size_t size)
{
	if(::send(__fd, buf, size, 0) == -1)
	{
		throw NetworkError(strerror(errno));
	}
}

void Client::send(const nlohmann::json &j)
{
	send(j.dump().c_str(), j.dump().size() + 1);
}
