#include "../include/Message.hpp"

nlohmann::json Message::toJSON()const
{
	nlohmann::json j;
	j["msg_text"] = text;
	return j;
}

void Message::fromJSON(const nlohmann::json &j)
{
	text = j["msg_text"];
}
