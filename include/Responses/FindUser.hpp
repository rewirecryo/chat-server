#ifndef INCLUDED_CHATSERVER_RESPONDFINDUSER_HPP
#define INCLUDED_CHATSERVER_RESPONDFINDUSER_HPP

#include "../Instruction.hpp"

class RespondFindUser : public Instruction
{
public:
	RespondFindUser();

	void setUserID(int new_id);
	int getUserID()const;

	void setUsername(const std::string &new_username)
	{
		__username = new_username;
	}
	
	nlohmann::json toJSON()const;
	
private:
	int __user_id = -1;
	std::string __username = "";
};

#endif
