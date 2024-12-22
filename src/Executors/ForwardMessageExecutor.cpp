#include "../../include/Executors/ForwardMessageExecutor.hpp"

int ForwardMessageExecutor::execute(const nlohmann::json &recvd_instruction, Client *src_client, Context *context, InstructionFactory *factory)
{
	if(src_client->getUser() == nullptr)
	{
		return -1;
	}

	// Give every recipient the message
	for(auto id_client_pair : *context->clients)
	{
		std::shared_ptr<ReceiveMessage> ins_recvmsg = std::make_shared<ReceiveMessage>();
		ins_recvmsg->setSender(src_client->getUser());
		ins_recvmsg->setContent(recvd_instruction["msg_text"]);

		factory->add(ins_recvmsg);
		id_client_pair.second->send(ins_recvmsg->toJSON());
	}

	return -1;
}
