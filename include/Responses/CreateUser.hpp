#ifndef INCLUDED_CHATSERVER_CREATEUSERRESPONSE_HPP
#define INCLUDED_CHATSERVER_CREATEUSERRESPONSE_HPP

#include "../Instruction.hpp"

class CreateUserResponse : public Instruction
{
public:
	CreateUserResponse();
	CreateUserResponse(int user_id);

	nlohmann::json toJSON()const;

	int getUserID()const;
	void setUserID(int new_user_id);
	
private:
	int __user_id = -1;
};

#endif
