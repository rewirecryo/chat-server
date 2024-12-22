#ifndef INCLUDED_CHATSERVER_RECEIVEMESSAGE_HPP
#define INCLUDED_CHATSERVER_RECEIVEMESSAGE_HPP

#include "../Instruction.hpp"
#include "../User.hpp"

class ReceiveMessage : public Instruction
{
public:
	ReceiveMessage();
	ReceiveMessage(const std::string &content, User *sender);

	void setContent(const std::string &content);
	const std::string &getContent()const;
	
	virtual nlohmann::json toJSON()const;

	User *getSender()const;
	void setSender(User *new_sender);
	
private:
	std::string __content = "";
	User *__sender = nullptr;
};

#endif
