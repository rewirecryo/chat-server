#ifndef INCLUDED_CHATSERVER_CONTEXT_HPP
#define INCLUDED_CHATSERVER_CONTEXT_HPP

#include <map>

#include "Client.hpp"
#include "User.hpp"

class Context
{
	std::map<int, Client> *client_list = nullptr;
	std::vector<User> *user_list = nullptr;
};

#endif
