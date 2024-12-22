#include "../include/InstructionFactory.hpp"

std::shared_ptr<Instruction> InstructionFactory::create(InstructionType type)
{
	std::shared_ptr<Instruction> new_instruction;
	
	switch(type)
	{
	case InstructionType::RECEIVE_MESSAGE:
		new_instruction = std::make_shared<ReceiveMessage>();
		break;
	case InstructionType::RESPOND_CREATE_USER:
		new_instruction = std::make_shared<CreateUserResponse>();
		break;
	case InstructionType::RESPOND_FIND_USER:
		new_instruction = std::make_shared<RespondFindUser>();
		break;
	default:
		throw std::runtime_error("InstructionFactory::create(): Tried to create instruction with invalid type.");
	}

	return add(new_instruction);
}

std::shared_ptr<Instruction> InstructionFactory::add(std::shared_ptr<Instruction> new_instruction)
{
	new_instruction->setInstructionID(__next_id);
	__instructions[__next_id] = new_instruction;
	++__next_id;

	return new_instruction;
}

void InstructionFactory::send(Client *dest_client, size_t instruction_id, bool should_fulfill)
{
	dest_client->send(__instructions[instruction_id]->toJSON());

	if(should_fulfill == true)
	{
		fulfill(instruction_id);
	}
}

void InstructionFactory::fulfill(size_t instruction_id)
{
	__instructions.erase(instruction_id);
}

std::shared_ptr<Instruction> InstructionFactory::getInstruction(size_t instruction_id)
{
	return __instructions[instruction_id];
}
