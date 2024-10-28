#include "../include/InstructionHandler.hpp"

InstructionHandler::InstructionHandler(Context *ctx)
{
	__context = ctx;
}

void InstructionHandler::setContext(Context *ctx)
{
	__context = ctx;
}

Context *InstructionHandler::getContext()const
{
	return __context;
}

void InstructionHandler::handle(std::vector<std::shared_ptr<Instruction>> instructions)
{
	for(auto &i : instructions)
	{
		i->execute();
	}
}
