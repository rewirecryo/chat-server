#include "../include/InstructionFactory.hpp"

Instruction *InstructionFactory::create(Client *client, InstructionType type)
{
	switch(type)
	{
	case InstructionType::SEND_MESSAGE:
		return new Message(client);
		break;
	default:
		throw std::runtime_error("InstructionFactory::create(): Tried to create instruction with invalid type.");
	}
}
