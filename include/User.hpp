#ifndef INCLUDED_CHATSERVER_USER_HPP
#define INCLUDED_CHATSERVER_USER_HPP

#include <string>

class User
{
public:
	User(int id, const std::string &username);

	int getID()const;
	void setID(int id);
	
	const std::string &getUsername()const;
	void setUsername(const std::string &username);

private:
	int __id = -1;
	std::string __username = "";
};

#endif
