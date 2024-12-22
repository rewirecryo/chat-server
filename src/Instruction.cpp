#include "../include/Instruction.hpp"

Instruction::Instruction()
{
}

int Instruction::getType()const
{
	return __type;
}

void Instruction::__setType(InstructionType new_type)
{
	__type = new_type;
}

void Instruction::setInstructionID(int new_id)
{
	__instruction_id = new_id;
}

int Instruction::getInstructionID()const
{
	return __instruction_id;
}

int Instruction::getRespondee()const
{
	return __respondee;
}

void Instruction::setRespondee(int respondee_id)
{
	__respondee = respondee_id;
}

nlohmann::json Instruction::__jsonTemplate()const
{
	nlohmann::json j_ins;

	if(__respondee != -1)
	{
		j_ins["respondee"] = getRespondee();
	}
	j_ins["id"] = getInstructionID();
	j_ins["instruction_type"] = getType();
	j_ins["response_to"] = getRespondee();
	return j_ins;
}
