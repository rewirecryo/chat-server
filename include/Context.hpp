#ifndef INCLUDED_CHATSERVER_CONTEXT_HPP
#define INCLUDED_CHATSERVER_CONTEXT_HPP

#include <map>

#include "Client.hpp"
#include "User.hpp"

class Context
{
public:
	std::map<int, std::shared_ptr<Client>> *clients = nullptr;
	std::map<unsigned int, std::shared_ptr<User>> *users = nullptr;
};

#endif
