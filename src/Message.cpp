#include "../include/Message.hpp"

nlohmann::json Message::toJSON()const
{
	nlohmann::json j;
	j["instruction_type"] = InstructionType::SEND_MESSAGE;
	j["msg_text"] = text;
	return j;
}

void Message::fromJSON(const nlohmann::json &j)
{
	text = j["msg_text"];
}

void Message::execute()
{
	nlohmann::json j = {toJSON()};
	for(auto clients : *broadcast_clients)
	{
		clients.second.send(j);
	}
}
