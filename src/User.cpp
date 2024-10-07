#include "../include/User.hpp"

User::User(int id, const std::string &username)
{
	__id = id;
	__username = username;
}

const std::string &User::getUsername()const
{
	return __username;
}

void User::setUsername(const std::string &username)
{
	__username = username;
}

int User::getID()const
{
	return __id;
}

void User::setID(int id)
{
	__id = id;
}
