#include "../../include/Executors/FindUserExecutor.hpp"

int FindUserExecutor::execute(const nlohmann::json &recvd_instruction, Client *client, Context *context, InstructionFactory *factory)
{
	int wanted_id = recvd_instruction["user_id"];

	auto found_user_iter = context->users->find(recvd_instruction["user_id"]);

	// Fill out our Response
	std::shared_ptr<RespondFindUser> query_response = std::make_shared<RespondFindUser>();
	query_response->setRespondee(recvd_instruction["id"]);
	if(found_user_iter != context->users->end())
	{
		std::shared_ptr<User> found_user = ((*found_user_iter).second);
		query_response->setUserID(found_user->getID());
		query_response->setUsername(found_user->getUsername());
	}
	else
	{
		query_response->setUserID(-1);
		query_response->setUsername("");
	}

	// Send out our Response
	factory->add(query_response);
	factory->send(client, query_response->getInstructionID());
	
	return -1;
}
