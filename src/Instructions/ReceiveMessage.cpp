#include "../../include/Instructions/ReceiveMessage.hpp"

ReceiveMessage::ReceiveMessage()
{
	__setType(InstructionType::RECEIVE_MESSAGE);
}

ReceiveMessage::ReceiveMessage(const std::string &content,
							   User *sender)
{
	__sender = sender;
	__content = content;
	__setType(InstructionType::RECEIVE_MESSAGE);
}

nlohmann::json ReceiveMessage::toJSON()const
{
	nlohmann::json j_ins = __jsonTemplate();

	j_ins["content"] = __content;
	j_ins["sender"] = __sender->getID();

	return j_ins;
}

void ReceiveMessage::setContent(const std::string &content)
{
	__content = content;
}

const std::string &ReceiveMessage::getContent()const
{
	return __content;
}

User *ReceiveMessage::getSender()const
{
	return __sender;
}

void ReceiveMessage::setSender(User *new_sender)
{
	__sender = new_sender;
}
