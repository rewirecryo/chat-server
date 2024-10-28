#include "../include/Instruction.hpp"

Instruction::Instruction(Client *src_cli)
{
	source_client = src_cli;
}

int Instruction::getType()const
{
	return __type;
}
