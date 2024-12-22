#include "../../include/Executors/CreateUserExecutor.hpp"

int CreateUserExecutor::execute(const nlohmann::json &j_ins, Client *src_client, Context *context, InstructionFactory *factory)
{
	int new_user_id = context->users->size();
	std::shared_ptr<User> new_user = std::make_shared<User>(new_user_id, j_ins["username"]);
	(*context->users)[context->users->size()] = new_user;

	auto new_ins = factory->create(InstructionType::RESPOND_CREATE_USER);
	new_ins->setRespondee(j_ins["id"]);
	((CreateUserResponse*)new_ins.get())->setUserID(new_user->getID());
	src_client->setUser(new_user.get());
	src_client->send(new_ins->toJSON());
//	factory->send(src_client, new_ins_id, true);
	
	return -1;
}
