#include "../include/Message.hpp"

nlohmann::json Message::toJSON()const
{
	nlohmann::json j;
	j["msg_text"] = text;
	return j;
}
