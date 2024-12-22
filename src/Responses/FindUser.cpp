#include "../../include/Responses/FindUser.hpp"

RespondFindUser::RespondFindUser()
{
	__setType(InstructionType::RESPOND_FIND_USER);
}

void RespondFindUser::setUserID(int new_id)
{
	__user_id = new_id;
}

int RespondFindUser::getUserID()const
{
	return __user_id;
}

nlohmann::json RespondFindUser::toJSON()const
{
	nlohmann::json j_ins = __jsonTemplate();

	j_ins["user_id"] = __user_id;
	j_ins["username"] = __username;

	return j_ins;
}
