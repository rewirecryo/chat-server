#ifndef INCLUDED_CHATSERVER_CONTEXT_HPP
#define INCLUDED_CHATSERVER_CONTEXT_HPP

#include <map>

#include "Client.hpp"

class Context
{
	std::map<int, Client> *client_list = nullptr;
};

#endif
