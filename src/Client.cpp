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
	// Turn the JSON into a structure that the client will accept understandable by the client
	nlohmann::json j_proper;
	j_proper["status"] = 0;
	j_proper["instruction_list"] = nlohmann::json();
	j_proper["instruction_list"].push_back(j);

	// Send the properly-formatted JSON
	send(j_proper.dump().c_str(), j_proper.dump().size() + 1);
}

User *Client::getUser()const
{
	return __user;
}

void Client::setUser(User *user)
{
	__user = user;
}
