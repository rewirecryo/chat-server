#ifndef INCLUDED_CHATSERVER_INSTRUCTIONHANDLER_HPP
#define INCLUDED_CHATSERVER_INSTRUCTIONHANDLER_HPP

#include "Context.hpp"
#include "Instruction.hpp"

class InstructionHandler
{
public:
	InstructionHandler(Context *ctx);
	void handle(std::vector<std::shared_ptr<Instruction>> instructions);

	void setContext(Context *ctx);
	Context *getContext()const;

private:
	Context *__context = nullptr;
};

#endif
