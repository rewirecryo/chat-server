#include "../../include/Responses/CreateUser.hpp"

CreateUserResponse::CreateUserResponse()
{
	__setType(InstructionType::RESPOND_CREATE_USER);
}

CreateUserResponse::CreateUserResponse(int user_id)
{
	__setType(InstructionType::RESPOND_CREATE_USER);
	__user_id = user_id;
}

nlohmann::json CreateUserResponse::toJSON()const
{
	nlohmann::json j_ins = __jsonTemplate();

	j_ins["user_id"] = __user_id;

	return j_ins;
}

void CreateUserResponse::setUserID(int new_user_id)
{
	__user_id = new_user_id;
}

int CreateUserResponse::getUserID()const
{
	return __user_id;
}
